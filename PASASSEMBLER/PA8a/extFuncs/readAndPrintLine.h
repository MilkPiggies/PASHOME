#include <stdio.h>

void readAndPrintLine(int x) 
{
    FILE *file = fopen("SOURCE.PA", "r");
    if (file == NULL) 
	{
        printf("Error opening file.\n");
        return;
    }

    int lineCount = 0;
    while (fgets(e, sizeof(e), file) != NULL) 
	{
        lineCount++;
        if (lineCount == x) 
		{
            break;
        }
    }

    fclose(file);
}
