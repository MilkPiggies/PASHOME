#include <stdio.h>
#include <string.h>
#include <ctype.h>







void removeZeros(char *data) {
  int j = 0;
  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] != '0') {
      data[j++] = data[i];
    }
  }
  data[j] = '\0';
}









int main() {
    FILE *source_file, *output_file;
    char line [100];
    char reg, hex [5];
    char reg1, hex1 [5];
    char reg2 [5];

    // Open the input and output files
    source_file = fopen("SOURCE.TXT", "r");
    output_file = fopen("SOURCE.P", "w");

    if (source_file == NULL || output_file == NULL) {
        printf("Error opening file(s).\n");
        return 1;
    }

    // Read each line from the input file and translate it
    while (fgets(line, sizeof(line), source_file)) {
        // Remove the newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        if (strncmp(line, "put", 3) == 0) {
            sscanf(line, "put(@%c, #%4s)", &reg, hex);
            fprintf(output_file, "LD%c $# %s\n", reg, hex);
            
        } else if (strncmp(line, "mov", 3) == 0) {
            sscanf(line, "mov(@%c, #%4s)", &reg1, hex1);
            // Remove the leading zeros
            char data [5];
            for (int i = 0; i < 4; i++) {
                if (isalpha(hex1[i])) {
                    data[i] = hex1[i];
                    break;
                } else {
                    data[i] = hex1[i];
                }
            }
            data [4] = '\0';


			printf("%s\n", data);
			

			// Really remove 0's from string.
			removeZeros(data);
			


            // Determine the assembly instruction
            fprintf(output_file, "T%c%s $# 0000\n", toupper(reg1), data);
            
        } else if (strncmp(line, "get", 3) == 0) {
            sscanf(line, "get(@%c, #%4s)", &reg, hex);
            fprintf(output_file, "LD%c $ %s\n", reg, hex);
		}
		
		
		  // heres where we put other commands.
          // else if is get
        
    }



    fclose(source_file);
    fclose(output_file);

    printf("Translation complete. Output written to SOURCE.P.\n");
    return 0;
}
