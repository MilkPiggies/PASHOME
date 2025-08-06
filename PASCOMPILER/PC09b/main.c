#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void translateLine(char *line, FILE *outputFile) {
    char command[10];
    char letter;
    char number[5];
    int num;

    if (sscanf(line, "%s @%c #%4s", command, &letter, number) == 3) {
        if (strcmp(command, "put") == 0) {
            fprintf(outputFile, "LD %c $%s\n", letter, number);
        } else if (strcmp(command, "mov") == 0) {
            num = atoi(number);
            int count = 0;
            for (int i = 0; i < 4; i++) {
                if (number[i] != '0') {
                    count++;
                }
            }
            fprintf(outputFile, "T %c %d\n", letter, count);
        }
    }
}

int main() {
    FILE *inputFile = fopen("SOURCE.TXT", "r");
    FILE *outputFile = fopen("SOURCE.P", "w");
    char line[100];

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), inputFile)) {
        translateLine(line, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}

