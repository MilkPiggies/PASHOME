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
#define MAX_LINES 100
#define MAX_LENGTH 256
#define LINE_LENGTH 256
#define MAX_VARS 100
#define MAX_FL 10
#define MAX_REGISTERS 100

int FL[MAX_LINES];
int line_count_fl = 0;

//
// Redo Variables, Give them meaningful names.
//



//=--------------------------------------------------------------------------=//
//|					     	   Garbage Tokenizer							 |//
//=--------------------------------------------------------------------------=//


//		   _ExtractTokens_
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



//		   _ProcessTokens_
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



//		   _CopyAndModifyFiles_
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
    } else if (strcmp(command, "get") == 0) {
        return "G";
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
                    fprintf(output_file, "%s---------\n", translation);
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


// Global variables to store REG and DAT values
char REG[MAX_LINES][2]; // Array to hold REG values
char DAT[MAX_LINES][MAX_LENGTH]; // Array to hold DAT values
int line_count = 0; // To keep track of the number of lines processed


void process_extra_put_reg(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file) && line_count < MAX_LINES) {
        char *at_ptr = strchr(line, '@');
        char *hash_ptr = strchr(line, '#');

        if (at_ptr) {
            REG[line_count][0] = *(at_ptr + 1); // Get character after @
        } else {
            REG[line_count][0] = '\0'; // No @ found
        }

        if (hash_ptr) {
            char *end_ptr = strpbrk(hash_ptr + 1, " \n");
            if (end_ptr) {
                size_t length = end_ptr - (hash_ptr + 1);
                strncpy(DAT[line_count], hash_ptr + 1, length);
                DAT[line_count][length] = '\0'; // Null-terminate the string
            } else {
                strcpy(DAT[line_count], hash_ptr + 1); // Copy until end of line
            }
        } else {
            DAT[line_count][0] = '\0'; // No # found
        }

        line_count++;
    }

    fclose(file);
}


// Unused Function, Do what you want with it. Can 
void process_extra_temp() {
   //put something here.
}


// Declare variables to hold line numbers
void find_put() {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        // Check for .pa file extension
        if (strstr(entry->d_name, ".pa") != NULL) {
            FILE *file = fopen(entry->d_name, "r");
            if (file == NULL) {
                perror("fopen");
                continue;
            }

            char line[256];
            int line_number = 0;
            printf("Scanning file: %s\n", entry->d_name);

            while (fgets(line, sizeof(line), file)) {
                line_number++;
                if (strstr(line, "LD") != NULL) {
                    printf("Found 'LD' in %s at line %d\n", entry->d_name, line_number);
                    if (line_count_fl < MAX_LINES) {
                        FL[line_count_fl] = line_number;
                        line_count_fl++;
                    }
                }
            }
            fclose(file);
        }
    }
    closedir(dp);
}


// Not sure if this is used...
void createLineArray(int line_count_fl, int *FL, long *line_fl) {
    FILE *file = fopen("_func.pa", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < line_count_fl; i++) {
        // Initialize the line_fl array with the byte offset for each line
        long offset = 0;
        for (int j = 0; j < FL[i]; j++) {
            // Move to the start of the next line
            offset = ftell(file);
            while (fgetc(file) != '\n' && !feof(file));
        }
        line_fl[i] = offset; // Store the byte offset in line_fl
    }

    fclose(file);
}





void find_t_offsets(int* t, int* t_count) {
    FILE* file = fopen("_func.pa", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line [1024];
    int offset = 0;
    *t_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strchr(line, 'T') != NULL) {
            t[*t_count] = offset;
            (*t_count)++;
        }
        offset += strlen(line);
    }

    fclose(file);
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
	
	
	printf("\n\n");


	// Process the extra information for propper compilation
	// Automatically find .temp files in the current directory
    if ((dir = opendir(".")) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (strstr(entry->d_name, ".temp")) {
                process_extra_put_reg(entry->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return EXIT_FAILURE;
    }
    
    
    // Print the generated variables
    for (int i = 0; i < line_count; i++) {
        printf("REG%d: %c, DAT%d: %s\n", i, REG[i][0], i, DAT[i]);
    }
    
    
    // Finish writing the rest of LD in .pa file
	process_extra_temp();	// Empty function
    
    
    find_put("."); // Scan current directory
    
    
    // Print line numbers stored in FL
    printf("Line numbers containing 'LD': %d\n", line_count_fl);
    
    
    // Subtracting 1 from each FL[i] where i is from 0 to line_count_fl - 1
    // And print each value of FL[i]
    for (int i = 0; i < line_count_fl; i++) {
        FL[i] -= 1; // Subtract 1 from each FL[i]
    }
    for (int i = 0; i < line_count_fl; i++) {
        printf("FL[%d]: %d\n", i, FL[i]);
    }
    

    
    int lineCount = 0;		// ?
    
    // NOT USED?
	int arsz = 10;		// Max lines to read?
	int v[arsz];		// Array that will store offsets (with a max of arsz)
    
    FILE *tcfp;
    
    int jq = 0;
	int ji = 0;
	int h = 0;

	int pe = 1;
	int tc = 0;
	int ti = 0;
	int tm = 0;
    
    
    
goto1:
	
	tc = 0;
	ti = 0;
	tm = 0;
    
    tcfp = fopen("_func.pa", "r");
	if (tcfp == NULL) {
		return 69;
	}

	// For debugging memory
	//printf("tcfp: %ld\n", tcfp);
	
	fseek(tcfp, 0, SEEK_SET);
	
	while ((tc = fgetc(tcfp)) != EOF) {
		printf("%c", tc);
		
		if (tc != '\n') {
			tm++;
		}
		
		if (tc == '\n' || tc == '\r') {
			tm++;
			
			v[ti] = tm;
			ti++;
			
		}
	}

	fclose(tcfp);
    
    
	
    // Print the byte offsets for verification
    for (int i = 0; i < line_count_fl; i++) {
        printf("Line %d starts at byte offset: %ld\n", FL[i], v[FL[i]]);
    }

    //free(line_fl);

	
	printf("\n\n");
	

	ji = 0;

	while (ji < line_count_fl) {
	
	//if (FL[ji] == )
	
	h = FL[ji];
	printf("v[%d]: %d\n", FL[ji], v[h]);
	ji++;
	}
    
    
    
    char ch;
    int l = 0; // Variable to store the number of lines

    // Open the file in read mode
    tcfp = fopen("_func.pa", "r");
    if (tcfp == NULL) {
        printf("Error opening file.\n");
        return 1; // Exit if the file cannot be opened
    }

    // Read characters from the file until EOF
    while ((ch = fgetc(tcfp)) != EOF) {
        // Increment line count when a newline character is found
        if (ch == '\n') {
            l++;
        }
    }

    // Close the file
    fclose(tcfp);
    
    
    
    
    
    //lcfl & l should be negated by one.
    line_count_fl = line_count_fl - 1;
	l = l - 1;
    
    
    printf("lcfl=line_count_fl (Line_Count_FL), lc=l (LineCount)\n", line_count_fl, l);
    printf("lcfl=%d, lc=%d \n\n\n", line_count_fl, l);
    
    
    int tji = 0;
	int efl = 1;
	int eefl;
	int tcv = 0;
	
	int vr = 0;
	int vre = 0;
	int t [100];
	int t_count = 0;
	

    
    
    
    
	// How many lines DONT start with LD.
	tji = l;
	ji = line_count_fl;
	
	eefl = l - line_count_fl;
	eefl = eefl * 3;
	
	
	// Main LD loop
	strtlp:
	
	
	// For debugging use.	
	printf("tji: %d\n", tji);
	printf("ji: %d\n", ji);
	printf("efl: %d\n", efl);	
	printf("eefl: %d\n", eefl);	
	printf("FL[ji]: %d\n\n", FL[ji]);	
		
	
	// Is the current line an LD
	if (tji == FL[ji]) {
	v[FL[ji]] = v[FL[ji]] + efl + eefl - 9;
	
	tcfp = fopen("_func.pa", "r+");
	
		fseek(tcfp, v[FL[ji]], SEEK_SET);
		jq = FL[ji];
		fprintf(tcfp, "%c", REG[jq][0]);
		fprintf(tcfp, " ");
		fprintf(tcfp, "$#");
		fprintf(tcfp, " ");
		fprintf(tcfp, "%s", DAT[jq]);
		
		
		// Must also add 4 bit data segment
		//
		// vr = log10(DAT[jq])
		//
		// THIS IS UNUSED, NO NEED FOR THI
		
		
	fclose(tcfp);
	}
	
	
	
	
	
	// The offset for every other command must then be processed, 
	// Do this at the end of main-this. 
	//
	//
	
	
	// Decrement accordingly
	if (tji != FL[ji]) {
		efl = 1;
		eefl--;
		eefl--;
		eefl--;
	}
	
	if (tji == FL[ji]) {
		efl--;
		ji--;
	} 
	
	tji--;
	
	
	// Check if ji is below 0, if so: stop loop.
	if (tji >= 0) {
		goto strtlp;
	} else {
		goto endilp;
	}


// Add $# to each LD line

// Also add the DAT value
// But make sure the added value is 4 long, eg 0020.



// Then do the same for all other commands (sto, mov, get)

    int olp = 0;

endilp:
goto2:
goto3:	
    
    
	if (olp == 1) {
		return 2;
	}



	find_t_offsets(t, &t_count);

    printf("Found %d occurrences of 'T':\n", t_count);
    for (int i = 0; i < t_count; i++) {
        printf("T_Offset %d: %d\n", i + 1, t[i]);
    }









	tcfp = fopen("_func.pa", "r+");
		
		
	vr = 0;
	vre = 0;
	//while(vr < t_count) {
//		fseek(tcfp, t[vr] + vre, SEEK_SET);
//		fprintf(tcfp, "i");
//		vr++;
	//}
	

	
	
	
	
	fclose(tcfp);
	










    printf("\n\n\n");

//=--------------------------------------------------------------------------=//
//|					     	  	Garbage Exit								 |//
//=--------------------------------------------------------------------------=//
    
    //char k = 'k';
    //int tcll = 0;
    //while (tcll < line_count_fl + 1) {
    //	printf("this: %d\n\n", v[tcll]);
    //	tcll++;
    //}
    
    
    

    
    
    
    
    
    printf("\n\n\n");
    
    
    // Delete Unused Files (all _ files except for files with the ext of .pa)
    int files_deleted = 0; 
	char exitYN;
    printf("Would you like to delete temp files? Y/N\n");
    scanf("%c", &exitYN);
    printf("Typed Key: %c\n\n", exitYN);
    
	if (exitYN == 'Y' || exitYN == 'y') {
	    if ((dir = opendir(".")) != NULL) {
	    	while ((entry = readdir(dir)) != NULL) {
	    		if (entry->d_name [0] == '_' && !strstr(entry->d_name, ".pa")) {
	    			files_deleted++;
					printf("%s\n", entry->d_name);
	    			remove(entry->d_name);
	    		}
	    	}
	    	printf("Files Deleted: %d", files_deleted);
	    	closedir(dir);
	    } else {
	    	printf("Error Opening Directory\n");
	    	return EXIT_FAILURE;
	    }
	} else {
		printf("No Files were Deleted");
		files_deleted = 0; 
	}
	
	
    
    
    
    // File with counter of how many passes
    
    // Or just delete .pa file on start of main.
    
    
    
    
    
    printf("\n\n\n\n\n");
	printf("Exit Success!");
    
    
    
	return EXIT_SUCCESS;	
}


