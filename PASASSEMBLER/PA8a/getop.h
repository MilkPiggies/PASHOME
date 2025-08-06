#include <stdio.h>



void getop() {

getoploop:

if (strcmp(et, opcarr[opp]) == 0) {
	
	op = opp;
	goto getopend;
} else {
	opp++;
	goto getoploop;
}



getopend:

return;
}
