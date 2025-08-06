#include <stdio.h>
#include <stdlib.h>

void vaFunc()
{
	int v = 0;
	int p = pt;
	int c;
	
	FILE *file = fopen("temp.txt", "r");
	
	vaFuncLoop:
    
    // Move the file pointer to last location
    fseek(file, p, SEEK_SET);
    
    // Get current character
    c = fgetc(file);

	// Main function
	if(c == ' ' || v == 4)
	{
		goto vaFuncEnd;
	}
	else
	{
		if(v == 0)
		{
			va1 = c;
			p++;
			v++;
			goto vaFuncLoop;
		}
		else
		{
			if(v == 1)
			{
				va2 = c;
				p++;
				v++;
				goto vaFuncLoop;
			}
			else
			{
				if(v == 2)
				{
					va3 = c;
					p++;
					v++;
					goto vaFuncLoop;
				}
				else
				{
					if(v == 3)
					{
						va4 = c;
						p++;
						v++;
						goto vaFuncLoop;
					}
				}
			}
		}
	}
	
vaFuncEnd:

	pt = p;

	// Print addr/val title
	printf("Addr/Val: \n");

	// Print da1 - da2
	printf("%c", va1);
	printf("%c", va2);
	printf("%c", va3);
	printf("%c", va4);
	printf(" \n");

	// Print spacing
	printf("------------------------------------ \n");
    
    // Close the file (file)
    fclose(file);
}
