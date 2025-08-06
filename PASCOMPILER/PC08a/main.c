// PAS COMPILER V8b

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



// KEEP THIS NAME
// Translates the rest of the put command to .pa

//void process_extra_put_reg() {
//	printf("Make Manually...");
//	printf("\n");
//	printf("Scan each letter with its own variable.");
//	printf("\n");
//	printf("Translate put(@A, #30) to LDA $# 0030");
//	printf("\n");
//}



//[OPTIONAL]//
// Do this \/ \/ \/ For before lexer pass, when making new files
// That    \/ \/ \/ 	Contain an underscore as the starting character.

// Change so _files wont be detected if the ext is .pa or .temp

// Otherwise _files need to be deleted before next execution.






//[TODO]//
// Get variables from .temp files
// Then parse them into the corresponding .pa files.

// If _file.temp-line1=put(@A, #10)
// Then _file.pa-line1=LDA $# 0010 




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





// BOTH BELOW ARE NOT USED.

void updateArrayWithOffsets(const char *filename, int *v, int *lineCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int offset = 0;
    *lineCount = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Store the current offset in the array
        v[*lineCount] = offset;
        (*lineCount)++;

        // Update the offset for the next line
        offset += strlen(line);
    }

    fclose(file);
}



int get_newline_offsets(const char* filename, int v[]) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0; // Failed to open file
    }

    int num_lines = 0;
    int offset = 0;
    char c;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            v[num_lines++] = offset;
            if (num_lines >= MAX_LINES) {
                break; // Reached maximum number of lines
            }
        }
        offset++;
    }

    fclose(fp);
    return num_lines;
}

// BOTH ABOVE ARE NOT USED.











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





    // Process the extra information for propper compilation
	// Automatically find .temp files in the current directory
    struct dirent *ent;
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".temp")) {
                process_extra_put_reg(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return EXIT_FAILURE;
    }

    // Print the generated variables
    for (int i = 0; i < line_count; i++) {
        printf("REG%d: %c\n, DAT%d: %s\n\n\n", i, REG[i][0], i, DAT[i]);
    }



	// Finish writing the rest of LD in .pa file
	process_extra_temp();	// Empty function
	
	

	
	
	
	find_put("."); // Scan current directory
    // Print line numbers stored in FL
    printf("Line numbers containing 'LD':\n");
    
    // Subtracting 1 from each FL[i] where i is from 0 to line_count_fl - 1
    for (int i = 0; i < line_count_fl; i++) {
        FL[i] -= 1; // Subtract 1 from each FL[i]
    }
    
    for (int i = 0; i < line_count_fl; i++) {
        printf("FL%d: %d\n", i, FL[i]);
    }



	printf("\n");
	printf("lclf: %d\n", line_count_fl);
	printf("\n");


	// Subtracting 1 from each FL[i] where i is from 0 to line_count_fl - 1
    for (int i = 0; i < line_count_fl; i++) {
        FL[i] -= 1; // Subtract 1 from each FL[i]
    }

    // Output the modified values for verification
    for (int i = 0; i < line_count_fl; i++) {
        printf("FL[%d] = %d\n", i, FL[i]);
    }



	//printf("FL[1]: %d\n", FL[1]);
	printf("\n");



	int i = 4;
	int g = 1;
	printf("REG0: %c\n", REG[i][0]);
	printf("FL[%d]: %d\n", g, FL[g]);











	printf("\n");

	//int g = 0;

    //int v = count_reg_variables();
    //printf("Number of variables starting with 'REG': %d\n", v);


	//countValidVariables("_func.pa");








// Penis Food
g = 0;		// Move somewhere else eventually.
FILE *fpfl = fopen("_func.pa", "r+");



// Penis Music
long *line_fl = malloc(256 * sizeof(long));

    createLineArray(line_count_fl, FL, line_fl);
	
    // Print the byte offsets for verification
    for (int i = 0; i < line_count_fl; i++) {
        printf("Line %d starts at byte offset: %ld\n", FL[i], line_fl[i]);
    }

    //free(line_fl);



for (int i = 0; i < 256; i++) {
	line_fl[i] = line_fl[i] + 2;
}



// Print the byte offsets for verification
    for (int i = 0; i < line_count_fl; i++) {
        printf("NEW Line %d starts at byte offset: %ld\n", FL[i], line_fl[i]);
    }

fclose(fpfl);














// v must be defined by each line each pass.
// else the offset is broken.

int lineCount = 0;
int arsz = 10;
int v[arsz];


// Penis House
for (int i = 0; i < line_count_fl; i++) {
    g = FL[i];  // Assign FL[i] to g
	//line_fl[i] = line_fl[i] + 2;  
	//v[i] = v[i] + 2;	    
    //printf("FL[%d] = %d, REG[%d] = %c\n", i, FL[i], g, REG[g][0]);    
    //fseek(fpfl, line_fl[i] + v[i], SEEK_SET);
    //fprintf(fpfl, "%c", REG[g][0]);       
    //updateArrayWithOffsets("_func.pa", v, &lineCount);
}


// Print the offsets
    printf("Offsets of the first position of each line:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("Line %d: Offset %d\n", i, v[i]);
    }

	
	i = 0;
	v[i] = 0;
	
	i = 1;
	v[i] = 1;
	
	i = 2;
	v[i] = 2;
	
	i = 3;
	v[i] = 3;


	
	
	

	
	FILE *tcfp;
	FILE *fpfl2;
	
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

	printf("tcfp: %ld\n", tcfp);
	
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
	
	

//  now print v[] to file. may need to (offset - 2) and print \n
// not sure how CR and LF will respond.

ji = 0;

while (ji < line_count_fl) {
	
	//if (FL[ji] == )
	
	h = FL[ji];
	printf("v[%d]: %d\n", FL[ji], v[h]);
	ji++;
}









// TEST  FL[JI]




// OTHER TEST FGETS




// TEST FULL LINE COUNT
    char ch;
    int l = 0; // Variable to store the number of lines

    // Open the file in read mode
    fpfl2 = fopen("_func.pa", "r");
    if (fpfl2 == NULL) {
        printf("Error opening file.\n");
        return 1; // Exit if the file cannot be opened
    }

    // Read characters from the file until EOF
    while ((ch = fgetc(fpfl2)) != EOF) {
        // Increment line count when a newline character is found
        if (ch == '\n') {
            l++;
        }
    }

    // Close the file
    fclose(fpfl2);



    // If the file is not empty, increment l for the last line
    //if (l > 0 || (l == 0 && ch == '\n')) {
    //    l++;
    //}

    
printf("lcfl=line_count_fl (Line_Count_FL), lc=l (LineCount)\n", line_count_fl, l);
    

line_count_fl = line_count_fl - 1;
l = l - 1;




int tji = 0;
int efl = 1;
int eefl;
int tcv = 0;
int vr = 1;

// Print lcfl and l
printf("lc: %d\n", l);
printf("lcfl: %d\n\n\n\n", line_count_fl);






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
v[FL[ji]] = v[FL[ji]] + efl + eefl;

fpfl2 = fopen("_func.pa", "r+");

	fseek(fpfl2, v[FL[ji]], SEEK_SET);
	jq = FL[ji];
	fprintf(fpfl2, "%c\r", REG[jq][0]);

fclose(fpfl2);
}

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










endilp:
goto2:
goto3:










	// Remove the .temp files.









    printf("\n");
    printf("\n");
	printf("\n");

    return EXIT_SUCCESS;
}
