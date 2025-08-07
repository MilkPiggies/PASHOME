#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100





// Func to remove zeros on op data
void removeZeros(char *data) {
  int j = 0;
  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] != '0') {
      data[j++] = data[i];
    }
  }
  data[j] = '\0';
}



// Func to translate data to hex and add according 0's
//void decimal_to_hex(int decimal) {
//    sprintf(hex_value, "%04x", decimal);
//}










int main() {
    FILE *source_file, *output_file;
    char line [100];
    char reg, hex [5];
    char reg1, hex1 [5];
    char reg2 [5];
    char label [100];

    // Open the input and output files
    source_file = fopen("SOURCE.TXT", "r");
    output_file = fopen("SOURCE.P", "w");

    if (source_file == NULL || output_file == NULL) {
        printf("Error opening file(s).\n");
        return 1;
    }

	int decimal = 10;

	int a = 1;
	int b = 1;
	int w = 0;
	
	int d = 1; 
	char g[][20] = { "shit1", "shit2", "shit3", "shit4" };
	int o[20] = { 0 };
	int h = 1;
	
	char u;
	char hex_value;

	int line_number = 1;
    char c;
    
    int gtc = 0;
	

	//while ((c = fgetc(source_file)) != EOF) {
	//        if (c == '\n') {
	//            printf(" = Line %d: ", line_number);
	//            line_number++;
	//       }
	//        fputc(c, stdout);
	//    }



    // Read each line from the input file and translate it
    while (fgets(line, sizeof(line), source_file)) {
        // Remove the newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

		
		
		// put
        if (strncmp(line, "put", 3) == 0) {
            sscanf(line, "put(@%c, #%4s)", &reg, hex);
            fprintf(output_file, "LD%c $# %s\n", reg, hex);
         
		 
		 
		// mov     
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
			removeZeros(data);
			
            // Determine the assembly instruction
            fprintf(output_file, "T%c%s $# 0000\n", toupper(reg1), data);
            
            
            
        // get
        } else if (strncmp(line, "get", 3) == 0) {
            sscanf(line, "get(@%c, #%4s)", &reg, hex);
            fprintf(output_file, "LD%c $ %s\n", reg, hex);
        
		
		
		
		// nop
		} else if (strncmp(line, "nop", 3) == 0) {
			sscanf(line, "nop");
			fprintf(output_file, "NULL $# 0000\n");
		     


            
		// label            
		} else if (strncmp(line, ":", 1) == 0) {
			sscanf(line, ":%5s", &label);
			//printf("label%d: %s on line %d\n", b, label, a);
			fprintf(output_file, "NULL $# 0000\n");
			strcpy(g[b], label);
			o[b] = a;
			o[b] = o[b] + gtc;
			printf("label %s found at: %d\n", g[b], o[b]);
			b++;
			//NOT WORKING-UNUSED
				//u[b] = *label;		//see above, correct uses strcpy.
				//fprintf(output_file, "%s", g[b]);
			



		// goto
		} else if (strstr(line, "goto")) {
			
			// goto if
			if (strstr(line, "if")) {
				printf("testgotoif ");
				w = 1;
				
gotoloop0:
	
				sscanf(line, "goto if %5s", &label);
				if (strcmp(g[w], label) == 0) {
					printf("goto if found at %d: %s\n",	o[w], g[w]);
					// what kind of branch? 
					// where branch to?
					fprintf(output_file, "testgotoif0\n");
					fprintf(output_file, "testgotoif1\n");
					gtc++;
					gtc++;
					goto gotoexit;
				}
				w++;
				goto gotoloop0;
			
			
			
			
			
			// goto only
			} else {
				printf("testgoto ");
				w = 1;
				
				
gotoloop1:
	
			
				sscanf(line, "goto %5s", &label);
				if (strcmp(g[w], label) == 0) {
					printf("goto found at %d: %s\n", o[w], g[w]);
					// whehre branch to?
					fprintf(output_file, "testgoto0\n");
					fprintf(output_file, "testgoto1\n");
					gtc++;
					gtc++;
					goto gotoexit;
				}
				w++;
				goto gotoloop1;
				
				
			}
			
				
				


gotoexit:			
	continue;			
				
		} // else if {
		
		// depending on what the label is, compare it to g[b] until they
		// match, then get b and get the matching o[b] for the offset

		
		
		
		
		
		
		
		
		
		

			
        // heres where we put other commands.
        // } else if {
    	//
		// }
        
        
        a++;	// tracks output file location
        		// need to change this to hex
    }



    fclose(source_file);
    fclose(output_file);

	printf("\n\n");
    printf("Translation complete. Output written to SOURCE.P.\n");
    //printf("test %d", o[1]);
    return 0;
}
