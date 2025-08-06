#include <stdio.h>

char e[256];
int res;

int op1;
int op2;
int op3;
int op4;
int op5;
int op6;
int op7;
int op8;

char da1;
char da2;

char va1;
char va2;
char va3;
char va4;

int pt;
int opv;
int dav;
int vav;
int res;
int a01;
int fres;

int tav1;
int tav2;
int tav3;
int tav4;

#include "readAndPrintLine.h"
#include "write2temp.h"
#include "opFunc.h"
#include "daFunc.h"
#include "vaFunc.h"
#include "fvFunc.h"
#include "opvrFunc.h"
#include "write2out.h"
#include "addval.h"

//#include "testFunc.h"

int main() 
{
    int x = 1; 		// Specify the line number to read
    int z = 7;		// Specify amount of lines					//this will need to be set properly
    
    z++;			// Add one to include last line
    
    
    
goto1:
    
    a01 = 0;		// Set above f8 or not to 0
    
    readAndPrintLine(x);
    //printf("%s", e);
    x++;
    
    if(x == z)
    {
    	goto goto2;
    }
    
    write2temp();
    
    opFunc();
    daFunc();
    vaFunc();
    fvFunc();
    opvrFunc();
    
    
    
    // add DAV to RES
	res = res + dav;
    
    printf(" \n");
    printf("%d", pt);
    
    printf(" \n");
    printf("%d", opv);
    
    printf(" \n");
    printf("%d", dav);
    
    //printf(" \n");			
    //printf("%d", vav);		//not used. using tav1-tav4
    
    printf(" \n");
    printf("%x", res);
    


    addval();
    
    // print if above tax or not
    printf(" \n");
    printf("%d", a01);
	
    // write result in out.txt
    write2out();
    
    
    
    goto goto1;
    
    //testFunc();					
    //goto goto1;

goto2:
    
    //exit(0);
    return 2;
}
