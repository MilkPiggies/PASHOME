#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_FILE_NAME_LENGTH 100

int main() {
    FILE *inputFile = fopen("functions.txt", "r");
    FILE *tprinttestFile = fopen("tprinttest.txt", "r");
    FILE *outputFile;

    if (inputFile == NULL || tprinttestFile == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    char line[MAX_WORD_LENGTH];
    char searchWord[MAX_WORD_LENGTH];
    char temp[MAX_WORD_LENGTH];

    while (fgets(line, MAX_WORD_LENGTH, inputFile) != NULL) {
        sscanf(line, "%99s", word);

        // Find the word in the tprinttest file
        rewind(tprinttestFile);
        while (fgets(line, MAX_WORD_LENGTH, tprinttestFile) != NULL) {
            if (strstr(line, word) != NULL) {
                // Copy everything after the word to a new file
                outputFile = fopen(word, "w");
                if (outputFile == NULL) {
                    printf("Error opening file\n");
                    return 1;
                }

                char *ptr = strstr(line, word);
                ptr += strlen(word);
                while (ptr != NULL && ptr[0] != '\0' && ptr[0] != '}') {
                    fprintf(outputFile, "%s", ptr);
                    ptr = strstr(ptr, "\n");
                    if (ptr != NULL) {
                        ptr += 1;
                    }
                }

                fclose(outputFile);
                break;
            }
        }

        if (feof(tprinttestFile)) {
            printf("Word '%s' not found in tprinttest.txt\n", word);
        }
    }

    fclose(inputFile);
    fclose(tprinttestFile);

    return 0;
}

