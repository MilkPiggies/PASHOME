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
        while (token != NULL) {
            // Check if the word starts with an underscore
            if (token[0] == '_') {
                // Write the word to the output file
                fprintf(output_file, "%s\n", token);
            }
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
