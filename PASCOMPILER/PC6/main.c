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




void scanFiles() {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    int i = 0;
    char *funcNames[100]; // Array to hold the names of the variables

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_name[0] == '_') { // Check if the first character is an underscore
            // Allocate memory for the variable name
            funcNames[i] = malloc(strlen(entry->d_name) + 1);
            if (funcNames[i] == NULL) {
                perror("malloc");
                closedir(dp);
                return;
            }
            strcpy(funcNames[i], entry->d_name); // Copy the file name to the variable
            printf("Func%d = %s\n", i, funcNames[i]); // Print the variable name and value
            i++;
        }
    }

    closedir(dp);

    // Free allocated memory
    for (int j = 0; j < i; j++) {
        free(funcNames[j]);
    }
}






int main() {
    extract_tokens("source.txt", "TOKENS.txt");
    process_tokens("TOKENS.txt", "source.txt");


    scanFiles();
    
    printf("\n");
	printf("\n");
	printf("\n");
	

    
    
    return 0;
}
 
