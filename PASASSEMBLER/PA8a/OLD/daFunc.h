#include <stdio.h>
#include <stdlib.h>

void daFunc()
{
	int v = 0;
	int p = pt;
	char c;
	
	da1 = ' ';
	da2 = ' ';
	
	FILE *file = fopen("temp.txt", "r");
    
daFuncLoop:
    
    // Move the file pointer to last location
    fseek(file, p, SEEK_SET);
    
    // Get current character
    c = fgetc(file);

	// Main function
	if(c == ' ' || v == 2)
	{
		p++; goto daFuncEnd;
	}
	else
	{
		if(v == 0)
		{
			da1 = c;
			p++;
			v++;
			goto daFuncLoop;
		}
		else
		{
			if(v == 1)
			{
				da2 = c;
				p++;
				v++;
				goto daFuncLoop;
			}
		}
	}
	
daFuncEnd:
	
	// Move p to pt
	pt = p;

	// Print a/da title
	printf("$/$#: \n");

	// Print da1 - da2
	printf("%c", da1);
	printf("%c", da2);
	printf(" \n");

	// Print spacing
	printf("------------------------------------ \n");
    
    // Close the file (file)
    fclose(file);
}
