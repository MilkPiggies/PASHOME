#include <stdio.h>
#include <string.h>
#include <ctype.h>



//Check what command was read in string
//Get string from file, starting on first line.



FILE *file;
FILE *f2w;

int op;
int opp;
int fop;

char e[16];
char et[16];
char eo[8];		//Not used for now.

int da;
char *da0;
char *da1;

char vali[4];
char vala[4];





// include a file that find how many lines there are

#include "extFuncs/oplist.h"				//Holds list of true commands
#include "extFuncs/readAndPrintLine.h"	//Gets the current line, puts on e
#include "extFuncs/getop.h"				//Gets the pos of each true command





void truncate_at_space(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            str[i] = '\0'; // Terminate the string at the space
            break;
        }
    }
}

void keep_last_four(char *str) {
    int len = strlen(str);
    if (len > 5) {
        memmove(str, str + len - 5, 5);
        str[5] = '\0';
    }
}

void remove_leading_zeros(char *word) {
    int i = 0;
    while (word[i] == '0') {
        i++;
    }
    if (i > 0) {
        memmove(word, word + i, strlen(word) - i + 1);
    }
}

void remove_newline(char *str) {
    char *pos = strchr(str, '\n');
    while (pos != NULL) {
        *pos = ' ';
        pos = strchr(pos, '\n');
    }
}

void remove_leading_spaces(char* word) {
    int i = 0;
    while (isspace(word[i])) {
        i++;
    }
    memmove(word, word + i, strlen(word) - i);
}

void remove_spaces(const char* input_file, const char* output_file) {
    FILE* in_file = fopen(input_file, "r");
    FILE* out_file = fopen(output_file, "w");

    if (in_file == NULL || out_file == NULL) {
        printf("Error opening files.\n");
        return;
    }

    int c;
    while ((c = fgetc(in_file)) != EOF) {
        if (!isspace(c)) {
            fputc(c, out_file);
        }
    }

    fclose(in_file);
    fclose(out_file);
    printf("Spaces removed successfully.\n");
}

void remove_trailing_space(char *str) {
    int len = strlen(str);
    
    // Check if the last character is a space
    if (len > 0 && str[len - 1] == ' ') {
        // Overwrite the space with a null terminator
        str[len - 1] = '\0';
    }
}

void removeChar(char *str, char c) {
    char *src = str, *dst = str;
    while (*src) {
        *dst = *src;
        if (*dst != c) {
            dst++;
        }
        src++;
    }
    *dst = '\0';
}



//



int main() 
{
	
	FILE *f2w = fopen("OUTPUT.PAS", "w");
	
	op = 2;			// Test op value
	
	int x = 1; 		// Specify the line number to read
    int z = 8;		// Specify amount of lines					//this will need to be set properly
    
    //z++;			// Add one to include last line
	
	
	
    // Open the file for reading
    //file = fopen("text.txt", "r");
    //if (file == NULL) {
    //     printf("Error opening the file.\n");
    //    return 1;
    //}
	
	
	
goto1:
	
	// Puts the current line on e
	readAndPrintLine(x);
	printf("%s", e);	// Prints e (debugging)
	
	// Disect e and create op/da/va
	// op -----------------------------------------
			// Move e to et
			strcpy(et, e);
			
			// Remove everything after the first space on et
			truncate_at_space(et);	
			
			// Check et and get a value for op
			opp = 0;
			getop();		
			printf("op: %d\n", op);
			
			
			
	// da -----------------------------------------
			// check if either $ or $# is 
			// contained in e
			
			// Move e to et
			strcpy(et, e);
			
			
			// Check if '$ ' or '$#'
			da0 = strstr(et, "$ ");
			da1 = strstr(et, "$#");
			
			if (da0 != NULL) {
				da = 0;
				goto daend;
			}
			
			if (da1 != NULL) {
				da = 1;
			}	
			
daend:
	
			//Print da output
			printf("da: %d\n", da);

	
	
	// va -----------------------------------------
			// make va by removing everything but 
			// the last four characters
			
			// Move e to et
			strcpy(et, e);
			fop = op;
			//printf("op test hex: %d\n", fop);		// Test op hex output
			
			
			
			// Get 4 last characters
			remove_newline(et);
			keep_last_four(et);
			strcpy(vala, et);
			printf("vala: %s\n", vala);
			strcpy(vali, vala);
			remove_leading_zeros(vali);
			printf("vali: %s\n", vali);
			//printf("\btest\n");		// Test backspace 
			printf("\n\n");		// Spacing
			//printf("op test hex: %02x\n", fop);		// Test op hex output
	
			
			
			
			
	//Write to output file ------------------------------------------------		
			
			// if da = 0, we start with a '1', then put vala, then put op.
			// if da = 1, we put vali, then put op.
			
			if(f2w == NULL)
			{
				printf("Error opening out.txt");
				return(3);
				//exit(3);
			}
		
			
			//remove_leading_spaces(fop);		// Didn't work. Fix or leave.
			//remove_trailing_space(vali);
			//remove_trailing_space(vala);	
			removeChar(vali, ' ');
			removeChar(vala, ' ');
			
			
			// Below should fprintf eop, as in da/vali-vala/op
			if (da == 0) {
				printf("out: %s%02x\n", vali, fop);
				fprintf(f2w, "%s%02x\n", vali, fop);
			}
			
			if (da == 1) {
				printf("out: 1%s%02x\n", vala, fop);				
				fprintf(f2w, "1%s%02x\n", vala, fop);
			}
			
					
					
					
					
			// Remove spaces to correct file.
			// Make eop to be correct.
	
	
	//Loop back to start and x++  if x != to z
	//Else if x == z, we stop.
	
	if (x == z) {
		goto goto2;
	} else {
		printf("\n\n");
		printf("-----------------------------------\n");		
		x++;
		goto goto1;
	}
	
	
	
	//remove_spaces("out.txt", "outfinal.txt");
	
	
	
goto2:	
	
	fclose(f2w);
	
   	//RETURN_SUCCESS
    return 2;
}
