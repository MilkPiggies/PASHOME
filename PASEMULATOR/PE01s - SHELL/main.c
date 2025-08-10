// PAS-EMULATOR
// MADE FOR SIMULATING THE PAS-CHIP, CPU.
//
// MADE BY MOLDYBREAD, 09/07/25



// BIOS INFO
	char biosinittest[] = "9550";
	
	char biosname[] = "RockerBIOS";			// Name of BIOS
	char biosversion[] = "1.0";				// 1.0 - 99.9				
	char biosrevision[] = "A0";				// A0 - Z9
	
	char biosbuilddate[] = "08/10/2025";	// (month)(day)(year)
	char biosbuildtime[] = "06:25:00";		// (hour)(minute)(second)
	
	char biossystemid[] = "00251500";		// (space)(year)(cpurev)(extra)
	char bioscpuid[] = "MKP(R) ver. 15 / PAS Processor 10 MHz";		// Name of CPU
	
// MEMORY INFO
	char kromdatabits[] = "25";				//
	char kromaddrbits[] = "16";				//
	char kromsizekb[] = "64KB";				//
	
	char mramdatabits[] = "25";				//
	char mramaddrbits[] = "8";				//
	char mramsizekb[] = "1KB";				//
	
	
		//NOW MAKE EXTERNAL DRIVES
		//AND BASEMEMORY
				
									
// Init Bios
	// Name / Revision
	// Version / Date
	// CPU Info
	// Memory Info
	// SPACING
	// Other

// Init Shell
	// Welcome Text
	// > Shell


// Memory Banks
	// EXT 0-3

void initbios() {
	
	printf("%s   Revision %s\n", biosname, biosrevision);
	printf("Copyright 2016 - 2025 MKP technologies\n");
	printf("\n");
	printf("BIOS version %s\n", biosversion);
	printf("This is test %s\n", biosinittest);
	printf("System ID = %s\n", biossystemid);
	printf("\n");
	printf("Build Time: %s %s\n", biosbuilddate, biosbuildtime);
	printf("CPU = %s\n", bioscpuid);
	
}

void bios() {
	
}

void initshell() {
	
}

void shell() {
	
}










void main() {
	
	initbios();
	
	return 2;
}
