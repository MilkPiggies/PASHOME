// PAS COMPILER V4

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_FILES 100
#define MAX_LINE_LENGTH 256
#define MAX_FILENAME_LENGTH 256



//		   _extract_tokens_
// Extract function name(s) and create 
// token file including function name(s).
void extract_tokens(const char *source_file, const char *token_file) {
    FILE *src = fopen(source_file, "r");
    FILE *tok = fopen(token_file, "w");
    char line[MAX_LINE_LENGTH];

    if (src == NULL || tok == NULL) {
        perror("Error opening file");
        return;
    }

	
	// Fuck fprintf && fgets
    while (fgets(line, sizeof(line), src)) {
        if (line[0] == '_') {
            fprintf(tok, "%s", line);
        }
    }

    fclose(src);
    fclose(tok);
}



//		   _process_tokens_
// For each token, find in source, copy  
// complete function into its own file.
void process_tokens(const char *token_file, const char *source_file) {
    FILE *tok = fopen(token_file, "r");
    FILE *src = fopen(source_file, "r");
    char token_line[MAX_LINE_LENGTH];
    char src_line[MAX_LINE_LENGTH];

    if (tok == NULL || src == NULL) {
        perror("Error opening file");
        return;
    }
	
	// This hurts my head
    while (fgets(token_line, sizeof(token_line), tok)) {
        token_line[strcspn(token_line, "\n")] = 0;
        rewind(src);
        int found = 0;
		
		// Make the new file
        while (fgets(src_line, sizeof(src_line), src)) {
            if (strstr(src_line, token_line) != NULL) {
                found = 1;
                FILE *new_file = fopen(token_line, "w");
                if (new_file == NULL) {
                    perror("Error creating new file");
                    break;
                }
                fprintf(new_file, "%s", src_line);

                while (fgets(src_line, sizeof(src_line), src)) {
                    fprintf(new_file, "%s", src_line);
                    if (strstr(src_line, "/}") != NULL) {
                        break;
                    }
                }
                fclose(new_file);
                break;
            }
        }
    }

    fclose(tok);
    fclose(src);
}



//		   _scanFiles_
// ...
// Print each token/function
void scanFiles(int *fileCount, char *funcNames[]) {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    int i = 0;

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_name[0] == '_') {
            funcNames[i] = malloc(strlen(entry->d_name) + 1);
            if (funcNames[i] == NULL) {
                perror("malloc");
                closedir(dp);
                return;
            }
            strcpy(funcNames[i], entry->d_name);
            printf("Func%d = %s\n", i, funcNames[i]);
            i++;
        }
    }

    *fileCount = i; // Store the count of files found
    closedir(dp);
}



//		   _copy_and_modify_file_
// Copy all contents from each private token file, 
// Move that to a temp file (for each private token file),
void copy_and_modify_file(const char *filename) {
    FILE *source_file = fopen(filename, "r");
    if (!source_file) {
        perror("Failed to open source file");
        return;
    }

    // Create new filename with .temp extension
    char temp_filename[256];
    snprintf(temp_filename, sizeof(temp_filename), "%s.temp", filename);

    FILE *temp_file = fopen(temp_filename, "w");
    if (!temp_file) {
        perror("Failed to create temp file");
        fclose(source_file);
        return;
    }

    char line[256];
    int line_count = 0;

    // Read lines from the source file and write to temp file
    while (fgets(line, sizeof(line), source_file)) {
        fprintf(temp_file, "%s", line);
        line_count++;
    }

    fclose(source_file);
    fclose(temp_file);

    // Now modify the temp file to remove the first and last lines
    source_file = fopen(temp_filename, "r");
    if (!source_file) {
        perror("Failed to open temp file");
        return;
    }

    // Create a new temporary file to store modified content
    FILE *modified_file = fopen("modified.temp", "w");
    if (!modified_file) {
        perror("Failed to create modified file");
        fclose(source_file);
        return;
    }

    int current_line = 0;
    while (fgets(line, sizeof(line), source_file)) {
        if (current_line > 0 && current_line < line_count - 1) {
            fprintf(modified_file, "%s", line);
        }
        current_line++;
    }

    fclose(source_file);
    fclose(modified_file);

    // Optionally, rename modified.temp to the original temp filename
    remove(temp_filename); // Remove the original temp file
    rename("modified.temp", temp_filename); // Rename modified file
}






//=--------------------------------------------------------------------------=//
//|					     	  	Garbage Lexer 								 |//
//=--------------------------------------------------------------------------=//

// Function to translate commands
const char* translate_command(const char* command) {
    if (strcmp(command, "put") == 0) {
        return "LD";
    } else if (strcmp(command, "mov") == 0) {
        return "T";
    } else if (strcmp(command, "sto") == 0) {
        return "ST";
    }
    return NULL; // Return NULL for unrecognized commands
}




// Function to process .temp files
void process_temp_files(const char* directory) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        // Check for .temp files
        if (strstr(entry->d_name, ".temp")) {
            char input_file_path[MAX_LINE_LENGTH];
            snprintf(input_file_path, sizeof(input_file_path), "%s/%s", directory, entry->d_name);
            FILE *input_file = fopen(input_file_path, "r");
            if (input_file == NULL) {
                perror("fopen");
                continue;
            }

            // Create output file with .pa extension
            char output_file_path[MAX_LINE_LENGTH];
            snprintf(output_file_path, sizeof(output_file_path), "%s/%s.pa", directory, entry->d_name);
            FILE *output_file = fopen(output_file_path, "w");
            if (output_file == NULL) {
                perror("fopen");
                fclose(input_file);
                continue;
            }

            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), input_file)) {
                char command[MAX_LINE_LENGTH];
                int i = 0;

                // Extract leading letters
                while (isalpha(line[i])) {
                    command[i] = line[i];
                    i++;
                }
                command[i] = '\0'; // Null-terminate the command string

                // Translate command and write to output file
                const char* translation = translate_command(command);
                if (translation) {
                    fprintf(output_file, "%s\n", translation);
                }
            }

            fclose(input_file);
            fclose(output_file);
        }
    }

    closedir(dp);
}




void rename_temp_files(const char *directory) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        // Check if the file ends with .temp.pa
        if (strstr(entry->d_name, ".temp.pa") != NULL) {
            // Create new filename by removing .temp
            char new_name[256];
            snprintf(new_name, sizeof(new_name), "%.*s.pa", 
                     (int)(strlen(entry->d_name) - strlen(".temp.pa")), 
                     entry->d_name);

            // Construct full paths for renaming
            char old_path[512], new_path[512];
            snprintf(old_path, sizeof(old_path), "%s/%s", directory, entry->d_name);
            snprintf(new_path, sizeof(new_path), "%s/%s", directory, new_name);

            // Rename the file
            if (rename(old_path, new_path) == 0) {
                printf("Renamed: %s to %s\n", old_path, new_path);
            } else {
                perror("rename");
            }
        }
    }

    closedir(dp);
}








//=--------------------------------------------------------------------------=//
//|					     	  	Garbage Main								 |//
//=--------------------------------------------------------------------------=//

int main() {
    extract_tokens("source.txt", "TOKENS.txt");
    process_tokens("TOKENS.txt", "source.txt");

    int fileCount = 0;
    char *funcNames[MAX_FILES]; // Array to hold the names of the variables
    scanFiles(&fileCount, funcNames);



	DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir) {
        perror("Failed to open directory");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if the file starts with an underscore
        if (entry->d_name[0] == '_') {
            copy_and_modify_file(entry->d_name);
        }
    }

    closedir(dir);



 	const char* directory = "."; // Current directory
    process_temp_files(directory);
    
    // Rename the .temp.pa files to .pa
	rename_temp_files(directory);



	// Remove the .temp files.


    printf("\n");
    printf("\n");
	printf("\n");
    //printf("Func1 = %s\n", funcNames[1]);
    
    //free(funcNames[1]); // Free allocated memory
    int j = 2;
    //printf("Func%d = %s\n", j, funcNames[j]);

    return EXIT_SUCCESS;
}
