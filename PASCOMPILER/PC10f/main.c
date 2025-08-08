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



	char BNN[] = { "!N" };
	char BNG[] = { "N" };
	char BNZ[] = { "!Z" };
	char BZE[] = { "Z" };
	char BNO[] = { "!O" };
	char BOV[] = { "O" };
	char BNC[] = { "!C" };
	char BCA[] = { "C" };
	char BBE[] = { ">=" };
	char BSE[] = { "<=" };
	char BCC[] = { "!>" };
	char BCS[] = { ">" };
	char BNE[] = { "!=" };
	char BEQ[] = { "=" };
	char BPL[] = { "!<" };
	char BMI[] = { "<" };
	






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
	char cond[2];
	char fbr[3];



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
				//printf("%s ", BNN);
				w = 1;
				
gotoloop0:
	
				sscanf(line, "goto if %2s %5s", &cond, &label);
				if (strcmp(g[w], label) == 0) {
					printf("goto if %s found at %d: %s\n", cond, o[w], g[w]);
					
					
							// FUCK THESE REPETITIVE IF STATEMENTS
							// JUST FUCKING LOOP IT . -faggotmold
					
					
				// what kind of branch? 
				
					// not neg
					if (strcmp(cond, BNN) == 0) {
						printf("YAY GOOD BNN MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BNN $# 0000\n");
					}
					
					// neg
					if (strcmp(cond, BNG) == 0) {
						printf("YAY GOOD BNG MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BNG $# 0000\n");
					}
					
					// not zero
					if (strcmp(cond, BNZ) == 0) {
						printf("YAY GOOD BNZ MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BNZ $# 0000\n");
					}
					
					// zero
					if (strcmp(cond, BZE) == 0) {
						printf("YAY GOOD BZE MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BZE $# 0000\n");
					}
					
					// not overflown 
					if (strcmp(cond, BNO) == 0) {
						printf("YAY GOOD BNO MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BNO $# 0000\n");
					}
					
					// overflown
					if (strcmp(cond, BOV) == 0) {
						printf("YAY GOOD BOV MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BOV $# 0000\n");
					}
					
					// not carrying
					if (strcmp(cond, BNC) == 0) {
						printf("YAY GOOD BNC MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BNC $# 0000\n");
					}
					
					// carrying
					if (strcmp(cond, BCA) == 0) {
						printf("YAY GOOD BCA MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BCA $# 0000\n");
					}
					
					// bigger or equal
					if (strcmp(cond, BBE) == 0) {
						printf("YAY GOOD BBE MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BBE $# 0000\n");
					}
					
					// smaller or equal
					if (strcmp(cond, BSE) == 0) {
						printf("YAY GOOD BSE MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BSE $# 0000\n");
					}
					
					// not bigger
					if (strcmp(cond, BCC) == 0) {
						printf("YAY GOOD BCC MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BCC $# 0000\n");
					}
					
					// bigger
					if (strcmp(cond, BCS) == 0) {
						printf("YAY GOOD BCS MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BCS $# 0000\n");
					}
					
					// not equal
					if (strcmp(cond, BNE) == 0) {
						printf("YAY GOOD BNE MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BNE $# 0000\n");
					}
					
					// equal
					if (strcmp(cond, BEQ) == 0) {
						printf("YAY GOOD BEQ MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BEQ $# 0000\n");
					}
					
					// not smaller
					if (strcmp(cond, BPL) == 0) {
						printf("YAY GOOD BPL MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BPL $# 0000\n");
					}
					
					// smaller
					if (strcmp(cond, BMI) == 0) {
						printf("YAY GOOD BMI MATCH\n");
						//fprintf LDX $# (label location)
						fprintf(output_file, "LDX $# %04x\n", o[w]);					
						//fprintf SBRM $# 0000
						fprintf(output_file, "SBRM $# 0000\n");					
						//fprintf SBRK $# 0000
						fprintf(output_file, "SBRK $# 0000\n");					
						//fprintf BR? $# 0000
						fprintf(output_file, "BMI $# 0000\n");
					}
					
					
					
					// where branch to?
						// see above switch statement's					
					
					// print stuff (lines written)
					//fprintf(output_file, "testgoto0\n");
					//fprintf(output_file, "testgoto1\n");
					
					
										
					// add according lines written
					gtc++;
					gtc++;
					gtc++; 
					gtc++;
					// more?
					
					// exit this (if else)
					goto gotoexit;
				}
				
				// if not equal, go back && add 1 to w
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
					// where branch to?
						// defined by ldx below (first fprintf, %04x/o[w])
					
					
					// print stuff (lines written)
					//fprintf(output_file, "testgoto0\n");
					//fprintf(output_file, "testgoto1\n");
					
					//fprintf LDX $# (label location)
					fprintf(output_file, "LDX $# %04x\n", o[w]);
					
					//fprintf SBRM $# 0000
					fprintf(output_file, "SBRM $# 0000\n");
					
					//fprintf SBRK $# 0000
					fprintf(output_file, "SBRK $# 0000\n");
					
					//fprintf BR $# 0000
					fprintf(output_file, "BR $# 0000\n");
					
					
					// add according lines written
					gtc++;
					gtc++;
					gtc++;
					gtc++;
					// more?
					
					// exit this (if else)
					goto gotoexit;
				}
				
				// if not equal, go back && add 1 to w
				w++;
				goto gotoloop1;
				
				
			}
			
gotoexit:			
	continue;	
	
	
	
	
		
	
			
				
		} else if(strstr(line, "penis")) {			
			// Maybe test this with a simple word (penis)?
			printf("penis found on line: %d\n", a);
			// spacing
			printf("\n");

		} // else if {
        
        
        
        
        
        a++;	// tracks output file location
        		// need to change this to hex
    }



    fclose(source_file);
    fclose(output_file);

	printf("\n\n");
    printf("Translation complete. Output written to SOURCE.P.\n");
    //printf("test %d", o[1]);
    return 2;
}
