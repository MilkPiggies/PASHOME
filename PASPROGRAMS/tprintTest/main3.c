#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1024
#define MAX_WORD_LENGTH 256

int main() {
    // Open the input file
    FILE *input_file = fopen("tprinttest.txt", "r");
    if (input_file == NULL) {
        printf("Could not open input file\n");
        return 1;
    }

    // Open the output file
    FILE *output_file = fopen("functions.txt", "w");
    if (output_file == NULL) {
        printf("Could not open output file\n");
        fclose(input_file);
        return 1;
    }

    char buffer[MAX_FILE_SIZE];
    char word[MAX_WORD_LENGTH];

    while (fgets(buffer, MAX_FILE_SIZE, input_file) != NULL) {
        char *token = strtok(buffer, " \t\n");
        if (token != NULL && token[0] == '_') {
            // Open a new file for the current function
            FILE *func_file = fopen(token, "w");
            if (func_file == NULL) {
                printf("Could not open output file for %s\n", token);
                continue;
            }

            // Read the rest of the input file to find the code for the current function
            while (fgets(buffer, MAX_FILE_SIZE, input_file) != NULL) {
                // Check if we've reached the end of the current function
                if (strstr(buffer, "}") != NULL) {
                    break;
                }
                // Write the line to the output file for the current function
                fprintf(func_file, "%s", buffer);
            }

            // Close the output file for the current function
            fclose(func_file);
        } else {
            // Write the line to the output file
            char *token = strtok(buffer, " \t\n");
            while (token != NULL) {
                if (token[0] == '_') {
                    break;
                }
                fprintf(output_file, "%s\n", token);
                token = strtok(NULL, " \t\n");
            }
        }
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
