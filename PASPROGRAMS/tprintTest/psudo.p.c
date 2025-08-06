// Psudo code for tprintTest
// MoldyBread 01/06/2025

// This code will print the text inside tprint(...)
// The tprint function will eventually be moved to a library

+text = 'TEST';
+sLen = 0;
+sPos = 0;



_tprint(char argv) {
	sLen = 0;
	sPos = 0;
	
	
//First get the length	
:getLen
	if(argv[sLen] != '\0') {
		sLen++;
	}
	else {
		goto :endLen		//Could replace with while()
	}
	goto :getLen
	
:endLen
	return(0);
	}
	

//Then Send Each Used Char (s0-s3...) according to sLen
:sendTel
	if(sPos != sLen) {
		sendTel(s[sPos]);
		sPos++;
		goto :sendTel
	}
	else {
		goto :endTel
	}

:endTel
return(0);	
}~



_main() {
	tprint(+text);
	return(1);
}~


