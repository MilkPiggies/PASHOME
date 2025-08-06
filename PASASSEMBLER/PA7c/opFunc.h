#include <stdio.h>
#include <stdlib.h>

void opFunc()
{
	int p = 0;
	int v = 0;
	char c;
	
	pt = p;
	
	FILE *file = fopen("temp.txt", "r");
	
	opFuncLoop:
    
    // Move the file pointer to the beginning of the file
    fseek(file, p, SEEK_SET);
    
    // Get current character
    c = fgetc(file);

	// Main function
	if(c == ' ' || v == 8)
	{ 
	p++; goto opFuncEnd;
	}
	else
	{
		if(v == 0)
		{
			op1 = c; 
			p++;
			v++;
			goto opFuncLoop;
		}
		else
		{
			if(v == 1)
			{
				op2 = c; 
				p++;
				v++;
				goto opFuncLoop;
			}
			else
			{
				if(v == 2)
				{
					op3 = c; 
					p++;
					v++;
					goto opFuncLoop;
				}
				else
				{
					if(v == 3)
					{
						op4 = c;
						p++;
						v++; 
						goto opFuncLoop;
					}
					else
					{
						if(v == 4)
						{
							op5 = c;
							p++;
							v++; 
							goto opFuncLoop;
						}
						else
						{
							if(v == 5)
							{
								op6 = c;
								p++;
								v++; 
								goto opFuncLoop;
							}
							else
							{
								if(v == 6)
								{
									op7 = c;
									p++;
									v++; 
									goto opFuncLoop;
								}
								else
								{
									if(v == 7)
									{
										op8 = c;
										p++;
										v++; 
										goto opFuncLoop;
									}
								}
							}
						}
					}
				}
			}
		}		
	}
	
opFuncEnd:	

	// Move p to pt
	pt = p;

	// Print op title
	printf("OP: \n");

	// Print op1 - op8
	printf("%c", op1);
	printf("%c", op2);
	printf("%c", op3);
	printf("%c", op4);
	printf("%c", op5);
	printf("%c", op6);
	printf("%c", op7);
	printf("%c", op8);
	printf(" \n");

	// Print spacing
	printf("-------------------------------- \n");
    
    // Close the file (file)
    fclose(file);
}
