/*

//Include Other Files
#include _

//Set Global Variables
fp* FILE
int i = 0
char c = 0

//Main Program
void main() {

	//Read source code from file
	
	//Scan and organize all functions
	
	//Number all functions
	
	//Tokenize each function
	
}

*/

/*

#include <string.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file = fopen("tprinttest.txt", "r");
    int lineNumber = 1; // The line number you want to read
    int count = 0;
    char c;
    char line[MAX_LINE_LENGTH]; // Adjust the size according to your needs

    if (file != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            count++;
            if (count == lineNumber) {
                printf("The content of line %d is: %s", lineNumber, line);
                printf("\n");
                fgetc
                break;
            }
        }
        fclose(file);
    } else {
        printf("Error: could not open file");
    }
    return 0;
}

*/


//Primarily, we just want to tokenize 
//Firstly, search and mark each instance of _name


#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Define the position wanted 	
int position = 2;

int main() {
	
//FIRST WE 
	
	// Open file in read mode
	FILE *fptr = fopen("tprinttest.txt", "r");
	if (fptr == NULL) {
		// If file does not exist
		printf("Failed to open file\n");
		return 1;
	}
	

	
 	// Move the file pointer to the specified position
    if (fseek(fptr, position, SEEK_SET) != 0) {
    	// If failed to point to position
        printf("Failed to seek to the specified position\n");
        fclose(fptr);
        return 1;
    }

    // Read the character at the specified position
    int ch = fgetc(fptr);
    if (ch == EOF) {
    	// If failed to read character at position
        printf("Failed to read character at the specified position\n");
    } else {
        printf("Character at position %d is '%c'\n", position, ch);
    }

    // Closing the file
    fclose(fptr);



	//Seek to the first character of each line
	//Detect (_)'s, Copy (position) to a new location




    return 0;
}
