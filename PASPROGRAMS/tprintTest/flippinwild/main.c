#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256



void scan_file_for_underscores(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    char word[100];

    if (input == NULL || output == NULL) {
        return;
    }

    while (fscanf(input, "%s", word) != EOF) {
        if (word[0] == '_') {
            fprintf(output, "%s\n", word);
        }
    }

    fclose(input);
    fclose(output);
}



void extract_code(const char *functions_file, const char *tprinttest_file) {
    FILE *functions_fp = fopen(functions_file, "r");
    FILE *tprinttest_fp = fopen(tprinttest_file, "r");
    char function_name[256];
    char line[1024];
    
    if (!functions_fp || !tprinttest_fp) {
        perror("Error opening file");
        return;
    }

    while (fgets(function_name, sizeof(function_name), functions_fp)) {
        function_name[strcspn(function_name, "\n")] = 0; // Remove newline character
        char output_file[256];
        snprintf(output_file, sizeof(output_file), "%s.txt", function_name);
        FILE *output_fp = fopen(output_file, "w");
        
        int found = 0;
        while (fgets(line, sizeof(line), tprinttest_fp)) {
            if (strstr(line, function_name)) {
                found = 1;
                fprintf(output_fp, "%s", line);
                while (fgets(line, sizeof(line), tprinttest_fp)) {
                    if (strstr(line, "}~")) {
                        fprintf(output_fp, "%s", line);
                        break;
                    }
                    fprintf(output_fp, "%s", line);
                }
                break;
            }
        }
        fclose(output_fp);
        rewind(tprinttest_fp);
    }

    fclose(functions_fp);
    fclose(tprinttest_fp);
}






int main() {
    scan_file_for_underscores("input.txt", "functions.txt");
    extract_code("functions.txt", "input.txt");
    
    // Next have to tokenize each function file. 
    // Maybe make new file with format: _name-tokens.txt?
    
    return 0;
}

