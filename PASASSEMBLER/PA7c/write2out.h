#include <stdio.h>
#include <stdlib.h>

int o = "0";

void write2out()
{	
	if(a01 == 0)
	{
		FILE *fp;
		fp = fopen("out.txt", "a");
		
		if(tav1 > 0)
		{
			fprintf(fp, "%x", tav1);
		}


		if(tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%x", tav2);
		}


		if(tav3 > 0 || tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%x", tav3);
		}


		if(tav4 > 0 || tav3 > 0 || tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%x", tav4);
		}
		
		fprintf(fp, "%x", res);
		fprintf(fp, " \n");
		fclose(fp);
	}
	
	if(a01 == 1)
	{
		FILE *fp;
		fp = fopen("out.txt", "a");
		
		if(tav1 > 0)
		{
			fprintf(fp, "%x", tav1);
		}


		if(tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%x", tav2);
		}


		if(tav3 > 0 || tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%x", tav3);
		}


		if(tav4 > 0 || tav3 > 0 || tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%x", tav4);
		}
		
		if(tav4 > 0 || tav3 > 0 || tav2 > 0 || tav1 > 0)
		{
			fprintf(fp, "%s", o);
		}
		
		fprintf(fp, "%x", res);
		fprintf(fp, " \n");
		fclose(fp);
	}
	
	return 1;

}


// check where first char is that doesnt = 0
// remove 0's before first char above 0





