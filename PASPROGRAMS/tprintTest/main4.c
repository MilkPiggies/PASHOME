#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_LINE_LENGTH 256

void extract_words(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "r");
    FILE *outfile = fopen(output_file, "w");
    char line[MAX_LINE_LENGTH];
    
    if (infile == NULL || outfile == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(line, sizeof(line), infile)) {
        char *token = strtok(line, " \n");
        while (token != NULL) {
            if (token[0] == '_') {
                fprintf(outfile, "%s\n", token);
            }
            token = strtok(NULL, " \n");
        }
    }

    fclose(infile);
    fclose(outfile);
}

void create_files_from_functions(const char *functions_file, const char *input_file) {
    FILE *funcs = fopen(functions_file, "r");
    char line[MAX_WORD_LENGTH];
    
    if (funcs == NULL) {
        perror("Error opening functions file");
        return;
    }

    while (fgets(line, sizeof(line), funcs)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        char output_file[MAX_WORD_LENGTH];
        snprintf(output_file, sizeof(output_file), "%s.txt", line);
        
        FILE *infile = fopen(input_file, "r");
        FILE *outfile = fopen(output_file, "w");
        char file_line[MAX_LINE_LENGTH];
        
        if (infile == NULL || outfile == NULL) {
            perror("Error opening file");
            continue;
        }

        while (fgets(file_line, sizeof(file_line), infile)) {
            char *pos = strstr(file_line, line);
            if (pos) {
                char *start = pos + strlen(line);
                char *end = strchr(start, '}');
                if (end) {
                    *end = '\0';
                    fprintf(outfile, "%s~\n", start);
                }
            }
        }

        fclose(infile);
        fclose(outfile);
    }

    fclose(funcs);
}

int main() {
    extract_words("tprinttest.txt", "functions.txt");
    create_files_from_functions("functions.txt", "tprinttest.txt");
    return 0;
}

