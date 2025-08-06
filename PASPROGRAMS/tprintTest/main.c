#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

int main() {
    FILE *inputFile = fopen("tprinttest.txt", "r");
    FILE *outputFile = fopen("functions.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(inputFile, "%99s", word) == 1) {
        if (strchr(word, '_') != NULL) {
            fprintf(outputFile, "%s\n", word);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
