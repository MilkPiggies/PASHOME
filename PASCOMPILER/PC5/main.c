// PAS COMPILER V4

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>

#define MAX_FILES 100
#define MAX_LINE_LENGTH 256
#define MAX_FILENAME_LENGTH 256

void extract_tokens(const char *source_file, const char *token_file) {
    FILE *src = fopen(source_file, "r");
    FILE *tok = fopen(token_file, "w");
    char line[MAX_LINE_LENGTH];

    if (src == NULL || tok == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(line, sizeof(line), src)) {
        if (line[0] == '_') {
            fprintf(tok, "%s", line);
        }
    }

    fclose(src);
    fclose(tok);
}



void process_tokens(const char *token_file, const char *source_file) {
    FILE *tok = fopen(token_file, "r");
    FILE *src = fopen(source_file, "r");
    char token_line[MAX_LINE_LENGTH];
    char src_line[MAX_LINE_LENGTH];

    if (tok == NULL || src == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(token_line, sizeof(token_line), tok)) {
        // Remove newline character from token_line
        token_line[strcspn(token_line, "\n")] = 0;

        // Reset source file pointer to the beginning
        rewind(src);
        int found = 0;

        while (fgets(src_line, sizeof(src_line), src)) {
            if (strstr(src_line, token_line) != NULL) {
                found = 1;
                // Create a new file with the name of the token line
                FILE *new_file = fopen(token_line, "w");
                if (new_file == NULL) {
                    perror("Error creating new file");
                    break;
                }
                fprintf(new_file, "%s", src_line);

                // Continue writing until we find "/}"
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



// Function to scan the current directory for files starting with an underscore
void scan_for_underscore_files() {
    struct dirent *entry;
    DIR *dp = opendir(".");
    char *variables[MAX_FILES];
    int count = 0;

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    // Scan through the directory entries
    while ((entry = readdir(dp)) != NULL) {
        // Check if the file name starts with an underscore
        if (entry->d_name[0] == '_' && count < MAX_FILES) {
            // Allocate memory for the variable name (excluding the underscore)
            variables[count] = malloc(MAX_FILENAME_LENGTH);
            if (variables[count] == NULL) {
                perror("malloc");
                closedir(dp);
                return;
            }
            // Copy the file name without the underscore
            strcpy(variables[count], entry->d_name + 1);
            count++;
        }
    }
    closedir(dp);

    // Print the number of variables created
    printf("Number of variables created: %d\n", count);
    
    // Print each variable name
    for (int i = 0; i < count; i++) {
        printf("Variable %d: %s\n", i + 1, variables[i]);
        free(variables[i]); // Free allocated memory
    }
}







int main() {
    extract_tokens("source.txt", "TOKENS.txt");
    process_tokens("TOKENS.txt", "source.txt");

	scan_for_underscore_files();
    
    
    
    return 0;
}
 
