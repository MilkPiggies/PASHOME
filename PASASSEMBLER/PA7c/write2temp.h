#include <stdio.h>

void write2temp()
{
	FILE *f2w = fopen("temp.txt", "w");
	
	if(f2w == NULL)
	{
		printf("Error opening temp.txt");
		return(3);
		exit(3);
	}
	
	fprintf(f2w, "%s", e);
	fclose(f2w);
	
	return 0;
}
