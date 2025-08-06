### USER_INPUT_PRINT-V2.asm ###

# This Version improves upon reading user input aswell 
# As printing the user input.

# 0x2D = '-'

####################
#  !LOCEND = 0x0A  #
#  !LOCRET = 0x0C  #
#				   #
#  !LINEND = 0x0F  #
#  !LINRET = 0x11  #
####################



-----------------------------------------------------------------



# THIS INITIALIZES ALL THE BRANCH ADDRESSES NEEDED 
# FOR THE PROGRAM IN STACK ($0100 - $01FF)

//SET_GLOBAL_BRANCHES
NOP $  0x00

	//DRAW_LOC
	NOP $  0x00
	
		//WRITE !LOCEND
		NOP $  0x00

			//POINT STACK TO A
			NOP $  0x00
			LDY $# 0x0A
			SSP $  0x00

			//SEND !LOCENDY TO STACK
			NOP $  0x00
			LDA $# 0x00 (!LOCENDY) [0]
			PHA $  0x00 (should be on 0x0A on stack)

			//SEND !LOCENDX TO STACK
			NOP $  0x00
			LDA $# 0xFE (!LOCENDX) [FE]
			PHA $  0x00 (should be on 0x0B on stack)

		//WRITE !LOCRET
		NOP $  0x00

			//POINT STACK TO C (stack already pointed to C)
			NOP $  0x00
			LDY $# 0x0C
			SSP $  0x00
	
			//SEND !LOCRETY TO STACK
			NOP $  0x00
			LDA $# 0x00 (!LOCRETY) [00]
			PHA $  0x00 (should be on 0x0C on stack)

			//SEND !LOCRETX TO STACK
			NOP $  0x00
			LDA $# 0xDA (!LOCRETX) [DA]
			PHA $  0x00 (should be on 0x0D on stack)
	
	
	
	//DRAW_LINE
	NOP $  0x00
	
		//WRITE !LINEND
		NOP $  0x00

			//POINT STACK TO A
			NOP $  0x00
			LDY $# 0x0F
			SSP $  0x00
	
			//SEND !LINENDY TO STACK
			NOP $  0x00
			LDA $# 0x01 (!LINENDY) [1]
			PHA $  0x00 (should be on 0x0F on stack)

			//SEND !LINENDX TO STACK
			NOP $  0x00
			LDA $# 0x2F (!LINENDX) [2F]
			PHA $  0x00 (should be on 0x10 on stack)

		//WRITE !LINRET
		NOP $  0x00

			//POINT STACK TO C (stack already pointed to C)
			NOP $  0x00
			LDY $# 0x11
			SSP $  0x00

			//SEND !LINRETY TO STACK
			NOP $  0x00
			LDA $# 0x01 (!LINRETY) [01]
			PHA $  0x00 (should be on 0x11 on stack)

			//SEND !LINRETX TO STACK
			NOP $  0x00
			LDA $# 0x08 (!LINRETX) [08]
			PHA $  0x00 (should be on 0x12 on stack)



	//STORE_INPUT
	NOP $  0x00
	
		//WRITE !STOEND
		NOP $  0x00

			//POINT STACK TO A
			NOP $  0x00
			LDY $# 0x14
			SSP $  0x00
	
			//SEND !STOENDY TO STACK
			NOP $  0x00
			LDA $# 0x03 (!STOENDY) [02]
			PHA $  0x00 (should be on 0x14 on stack)

			//SEND !STOENDX TO STACK
			NOP $  0x00
			LDA $# 0x25 (!STOENDX) [23]
			PHA $  0x00 (should be on 0x15 on stack)

		//WRITE !STORET
		NOP $  0x00

			//POINT STACK TO C (stack already pointed to 16)
			NOP $  0x00
			LDY $# 0x16
			SSP $  0x00

			//SEND !STORETY TO STACK
			NOP $  0x00
			LDA $# 0x01 (!STORETY) [01]
			PHA $  0x00 (should be on 0x16 on stack)

			//SEND !STORETX TO STACK
			NOP $  0x00
			LDA $# 0xCD (!STORETX) [CD]
			PHA $  0x00 (should be on 0x17 on stack)



-----------------------------------------------------------------

162*0

-----------------------------------------------------------------



# THIS SETS THE FOREGROUND TO WHITE AND BACKGROUND TO
# BLUE.

//DRAW_COL_CODE
NOP $  0x00
		
	//INITIALIZE
	NOP $  0x00

		//SET A TO 0
		LDA $# 0x00
	
		//SET B TO 0
		LDB $# 0x00
	
		//SET X TO 0
		LDX $# 0x00
	
		//SET Y TO 0
		LDY $# 0x00
		
	
	
	//MAIN
	NOP $  0x00
		
		//FORGROUND_COLOR
		LDB $# 0x01		(01 = WHITE)    
		SEFGCOL $ 0x00 		

		//BACKGROUND_COLOR
		LDB $# 0x06 	(06 = BLUE) 	
		SEFGCOL $ 0x00		
		
	

-----------------------------------------------------------------



# THIS SETS SEGLOC 0x00 TO 0x09 TO 0x40 TO 0x49 FOR
# LINE POSITIONING.

//DRAW_LOC_CODE
NOP $  0x00

	//INITIALIZE
	NOP $  0x00

		//SET A TO 0
		LDA $# 0x00
	
		//SET B TO 0
		LDB $# 0x00
	
		//SET X TO 0
		LDX $# 0x00
	
		//SET Y TO 0
		LDY $# 0x00



	//CHECK
	NOP $  0x00

		//SET STACK POSITION TO !LOCENDY
		LDY $# 0x0A 
		SSP $  0x00		

		//pull @Y from stack (!LOCENDY)	
		PLA $  0x00

		//transfer A to Y
		TAY $  0x00

		//SET STACK POSITION WITH ADDS TO !LOCENDX
		SPP $  0x00
		SPP $  0x00

		//pull @X from stack (!LOCENDX)
		PLA $  0x00

		//transfer A to X
		TAX $  0x00

		//SET KBRANCH
		SBRK $  0x00

		//LOAD A TO A
		LDA $# 0x0A
		
		//COMPARE A AND B
		CMP $  0x00

		//BRANCH IF EQUAL FLAG IS SET
		BEQ $  0x00 (branch if @A is equal to @B)



	//CONTINUE
	NOP $  0x00
	
	
	
	//SYNC
	NOP $  0x00
	TBX $  0x00
	
	
	
	//PUT_LOCATION
	NOP $  0x00
	LDY $# 0x01 ?(for first line)
	SESEGLOC $  0x00
	
	
	
	//ADDITION
	NOP $  0x00
	
		//LOAD 01 TO A
		LDA $# 0x01
	
		//ADD B TO A
		ADD $  0x00
		
		//TRANSFER A TO B
		TAB $  0x00



	//RETURN
	NOP $  0x00

		//SET STACK POSITION TO !LOCRETY
		LDY $# 0x0C 
		SSP $  0x00		

		//pull @Y from stack (!LOCRETY)	
		PLA $  0x00

		//transfer A to Y
		TAY $  0x00

		//SET STACK POSITION WITH ADDS TO !LOCRETX
		SPP $  0x00
		SPP $  0x00

		//pull @X from stack (!LOCRETX)
		PLA $  0x00

		//transfer A to X
		TAX $  0x00

		//SET KBRANCH
		SBRK $  0x00
		
		
		
	//BRANCH
	NOP $  0x00
	BR $  0x00
	


-----------------------------------------------------------------

3*0
-----------------------------------------------------------------



# THIS PUTS THE CHARACTERS FOR THE LINE IN SEGDATA

//DRAW_LIN_CODE
NOP $  0x00

	//INITIALIZE
	NOP $  0x00

		//SET A TO 0
		LDA $# 0x00
	
		//SET B TO 0
		LDB $# 0x00
	
		//SET X TO 0
		LDX $# 0x00
	
		//SET Y TO 0
		LDY $# 0x00

	//START
	NOP $  0x00
	
	//clear (< / = / >) ?
	
	
	
	//WRITE
	NOP $  0x00
	
		//SET Y TO '-'
		LDY $# 0x2D (-)
	
		//X SHOULD ALREADY BE CORRECT VALUE
	
		//WRITE TO SEGDAT
		SECHLOC $  0x00



	//SET_CHECK
	NOP $  0x00

		//SET STACK POSITION TO !ENDY
		LDY $# 0x0A 
		SSP $  0x00		

		//PULL @Y FROM STACK (!ENDY)	
		PLA $  0x00

		//TRANSFER A TO Y
		TAY $  0x00

		//SET STACK POSITION WITH ADDS TO !ENDX
		SPP $  0x00
		SPP $  0x00

		//PULL @X FROM STACK (!ENDX)
		PLA $  0x00

		//TRANSFER A TO X
		TAX $  0x00
		
		//SET BRANCH
		SBRK $  0x00



	//CHECK
	NOP $  0x00

		//LOAD 0x27 TO A
		LDA $# 0x27
		
		//COMPARE A AND B
		CMP $  0x00	



	//BRANCH IF EQUAL SPACING
	NOP $  0x00

		//BRANCH IF EQUAL
		BEQ $  0x00

	
	
	//X++
	NOP $  0x00

		//SET A TO 1
		LDA $# 0x01
		
		//ADD A + B
		ADD $  0x00
		
		//TRANSFER A TO B
		TAB $  0x00
		
		//TRANSFER B TO X
		TBX $  0x00
	
	

	//SET_RET
	NOP $  0x00

		//SET STACK POSITION TO !RETY
		LDY $# 0x11 
		SSP $  0x00		

		//PULL @Y FROM STACK (!RETY)	
		PLA $  0x00

		//TRANSFER A TO Y
		TAY $  0x00

		//SET STACK POSITION WITH ADDS TO !RETX
		SPP $  0x00
		SPP $  0x00

		//PULL @X FROM STACK (!RETX)
		PLA $  0x00

		//TRANSFER A TO X
		TAX $  0x00
		
		//SET BRANCH
		SBRK $  0x00
	


	//GOTO_RET
	NOP $  0x00
		
		//TRANSFER B TO X
		TBX $  0x00
		
		//BRANCH
		BR $  0x00



-----------------------------------------------------------------

3*0

-----------------------------------------------------------------



# THIS PRINTS "INPUT: " BELOW THE LINE

//PRINT "INPUT: "
NOP $  0x00

    //LOAD "I" TO SEGDAT $28
    NOP $  0x00

        //LOAD 0x28 TO X
        LDX $# 0x28

        //LOAD "I" TO Y
        LDY $# 0x49

        //SEND X + Y TO SEGDAT  
        SESCHLOC $  0x00

    //LOAD "N" TO SEGDAT $29
    NOP $  0x00

        //LOAD 0x29 TO X
        LDX $# 0x29

        //LOAD "N" TO Y
        LDY $# 0x4E

        //SEND X + Y TO SEGDAT
        SESCHLOC $  0x00

    //LOAD "P" TO SEGDAT $2A 
    NOP $  0x00

        //LOAD 0x2A TO X
        LDX $# 0x2A

        //LOAD "P" TO Y
        LDY $# 0x50 

        //SEND X + Y TO SEGDAT
        SECHLOC $  0x00

    //LOAD "U" TO SEGDAT $2B
    NOP $  0x00

        //LOAD 0x2B TO X
        LDX $# 0x2B

        //LOAD "U" TO Y
        LDY $# 0x55 

        //SEND X + Y TO SEGDAT
        SECHLOC $  0x00

    //LOAD "T" TO SEGDAT $2C
    NOP $  0x00

        //LOAD 0x2C TO X
        LDX $# 0x2C

        //LOAD "T" TO Y
        LDY $# 0x54

        //SEND X + T TO SEGDAT
        SECHLOC $  0x00

    //LOAD ":" TO SEGDAT $2D
    NOP $  0x00

        //LOAD 0x2D TO X
        LDX $# 0x2D

        //LOAD ":" TO Y
        LDY $# 0x3A

        //SEND  X + Y TO SEGDAT
        SECHLOC $  0x00

    //LOAD " " TO SEGDAT $2E
    NOP $  0x00

        //LOAD 0x2E TO X
        LDX $# 0x2E

        //LOAD  " " TO Y
        LDY $# 0x20

        //SEND X + Y TO SEGDAT
        SECHLOC $  0x00 



-----------------------------------------------------------------



# THIS SETS EXTRA SEGLOC'S FOR THE TEXT
# USER_INPUT_SEGLOC = 0x0A-0x13 = 0x80-0x89
# USER_PRINT_SEGLOC = 0x14-0x1D = 0x100-0x109

//SET USER_INPUT AND INPUT_PRINT SEGLOC ADDRESSES
NOP $  0x00

    //SET USER_INPUT SEGLOC ADDRESSES
    NOP $  0x00

        //LOAD 0x02 ON Y
        LDY $# 0x02

            //LOAD 0x00 ON X
            LDX $# 0x00

                //LOAD 0x0A ON B
                LDB $# 0x0A 

                    //SEND B + X + Y TO SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x01 ON X
            LDX $# 0x01

                //LOAD 0x0B ON B
                LDB $# 0x0B

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x02 ON X 
            LDX $# 0x02

                //LOAD 0x0C ON B
                LDB $# 0x0C

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x03 ON X
            LDX $# 0x03

                //LOAD 0x0D ON B
                LDB $# 0x0D

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x04 ON X
            LDX $# 0x04

                //LOAD 0x0E ON B
                LDB $# 0x0E

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x05 ON X
            LDX $# 0x05

                //LOAD 0x0F ON B
                LDB $# 0x0F

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x06 ON X
            LDX $# 0x06

                //LOAD 0x10 ON B
                LDB $# 0x10 

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x07 ON X
            LDX $# 0x07

                //LOAD 0x11 ON B
                LDB $# 0x11 

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x08 ON X
            LDX $# 0x08

                //LOAD 0x12 ON B
                LDB $# 0x12

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x09 ON X
            LDX $# 0x09

                //LOAD 0x13 ON B
                LDB $# 0x13

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

    

    //SET USER_PRINT SEGLOC ADDRESSES
    NOP $  0x00

        //LOAD 0x04 ON Y
        LDY $# 0x04

            //LOAD 0x00 ON X
            LDX $# 0x00

                //LOAD 0x14 ON B
                LDB $# 0x14

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x01 ON X
            LDX $# 0x01 

                //LOAD 0x15 ON B
                LDB $# 0x15

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x02 ON X
            LDX $# 0x02

                //LOAD 0x16 ON B
                LDB $# 0x16

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x03 ON X
            LDX $# 0x03

                //LOAD 0x17 ON B 
                LDB $# 0x17

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x04 ON X
            LDX $# 0x04

                //LOAD 0x18 ON B
                LDB $# 0x18

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x05 ON X
            LDX $# 0x05

                //LOAD 0x19 ON B
                LDB $# 0x19

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x06 ON X
            LDX $# 0x06

                //LOAD 0x1A ON B
                LDB $# 0x1A

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x07 ON X
            LDX $# 0x07

                //LOAD 0x1B ON B
                LDB $# 0x1B

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x08 ON X
            LDX $# 0x08

                //LOAD 0x1C ON B
                LDB $# 0x1C

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00

            //LOAD 0x09 ON X
            LDX $# 0x09

                //LOAD 0x1D ON B
                LDB $# 0x1D 

                    //SEND B + X + Y ON SEGLOC
                    SESEGLOC $  0x00
            
    

-----------------------------------------------------------------


we point the keyboard to the correct location in vram
we store the keyboard pointed location in ram ($15)
we interupt until the user presses enter








we get the new keyboard location and store in ram ($16)
we set a pointer to the start position of store input ($20)

we check if $15 is equal to $16
	if so, goto end
	else, continue

we get $15 from vram 
	we store $20 in Z
	we store in ($Z) (so first is $25, second is $26...)
			[Z is for address to ram]

we add 1 to $15
we add 1 to $20

goto start









put 0x25 on A
store A on $20


get keyboard location 
^ store on $16


:RET


put $15 on A
put $16 on B
compare A and B

(SET :END)

branch if equal


(get $15 from vram)
move to A

put $20 on X
put X+Y on Z

toggle zaddr
put A on $Z
toggle zaddr

load $15 on A
load 0x01 on B
add A + B
put on $15

load $20 on A
add A + B
put A on $20

(SET :RET)
branch to :RET





























set end branch
compare
branch if equal



add 1 to $15
add 1 to $20








//POINT KEYBOARD TO 0x2F
NOP $  0x00

	//LOAD 0x2F ON B
	LDB $# 0x2F

	//SET KEYBOARD LOCATION
	SEKBLOC $  0x00



//STORE KEYBOARD LOCATION IN RAM
NOP $  0x00

	//STORE B ON $15
	NOP $  0x00
	STB $# 0x15



-----------------------------------------------------------------



//INTERUPT AND WAIT FOR USER "UN-INTERUPT"
NOP $  0x00

	//LOAD 0x00 TO X
	LDX $# 0x00

	//INTERUPT
	INT $  0x00



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



//PREPARE $20
NOP $  0x00

	//LOAD 0x25 ON A
	LDA $# 0x25

	//STORE A ON $20
	STA $#  0x20



//GET KEYBOARD LOCATION - 2F TO $16
NOP $  0x00

	//GET KEYBOARD LOCATION
	GETKBLOC $  0x00

	//LOAD 2 TO A
	LDA $# 0x02

	//TRANSFER B TO X
	TBX $  0x00

	//TRANSFER A TO B
	TAB $  0x00

	//TRANSFER X TO A
	TXA $  0x00

	//SUBTRACT B FROM A
	SUB $  0x00

	//STORE A ON $16
	NOP $  0x00
	STA $# 0x16



//SET COMPARE VALUE ON $17
NOP $  0x00

	//PUT $16 ON A
	LDA $  0x16

	//PUT 0x01 ON B
	LDB $# 0x01

	//ADD A AND B
	ADD $  0x00

	//STORE A ON $17
	STA $# 0x17



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



//SET BRANCH IF EQUAL
NOP $  0x00

	//SET STACK POSITION TO !STOENDY
	LDY $# 0x14
	SSP $  0x00		

	//PULL @Y FROM STACK (!STOENDY)	
	PLA $  0x00

	//TRANSFER A TO Y
	TAY $  0x00

	//SET STACK POSITION WITH ADDS TO !STOENDX
	SPP $  0x00
	SPP $  0x00

	//PULL @X FROM STACK (!STOENDX)
	PLA $  0x00

	//TRANSFER A TO X
	TAX $  0x00
				
	//SET BRANCH
	SBRK $  0x00




//COMPARE $15 AND $17
NOP $  0x00

	//LOAD $15 ON A
	LDA $  0x15
		 
	//LOAD $17 ON B
	LDB $  0x16

	//COMPARE A AND B
	CMP $  0x00



//BRANCH IF EQUAL
NOP $  0x00
BEQ $  0x00



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



//STORE $20 ON Z
NOP $  0x00

	//CLEAR X
	NOP $  0x00
	LDX $# 0x00

	//STORE $20 ON Y
	NOP $  0x00
	LDY $  0x20

	//LOAD X+Y ON Z
	NOP $  0x00
	LDZ $  0x00 



//GET $15 FROM VRAM
NOP $  0x00

	//LOAD $15 ON X
	NOP $  0x00
	LDX $  0x15

	//GET CH WITH LOC
	NOP $  0x00
	GETCHLOC $  0x00



//STORE VRAM_OUT TO $Z
NOP $  0x00

	//TOGGLE Z-ADDRESS
	NOP $  0x00
	TGLZADDR $  0x00

	//STORE VRAM_OUT(Y) TO $Z
	NOP $  0x00
	STY $  0x00

	//TOGGLE Z-ADDRESS
	NOP $  0x00
	TGLZADDR $  0x00



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



//ADD 1 TO $15
NOP $  0x00

	//STORE $15 ON A
	NOP $  0x00
	LDA $  0x15

	//STORE 1 ON B
	NOP $  0x00
	LDB $# 0x01

	//ADD A AND B
	NOP $  0x00
	ADD $  0x00



//STORE ADDED_NUMBER ON $15
NOP $  0x00

	//STORE A ON $15
	NOP $  0x00
	STA $#  0x15



//ADD 1 TO $20
NOP $  0x00

	//STORE $20 ON A
	NOP $  0x00
    LDA $  0x20

	//STORE 1 ON B
	NOP $  0x00
	LDB $# 0x01

	//ADD A AND B 
	NOP $  0x00
	ADD $  0x00



//STORE ADDED_NUMBER ON $20
NOP $  0x00

	//STORE A ON $20
	NOP $  0x00
	STA $#  0x20



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



//SET BRANCH IF EQUAL
NOP $  0x00

	//SET STACK POSITION TO !STORETY
	LDY $# 0x16
	SSP $  0x00		

	//PULL @Y FROM STACK (!STORETY)	
	PLA $  0x00

	//TRANSFER A TO Y
	TAY $  0x00

	//SET STACK POSITION WITH ADDS TO !STORETX
	SPP $  0x00
	SPP $  0x00

	//PULL @X FROM STACK (!STORETX)
	PLA $  0x00

	//TRANSFER A TO X
	TAX $  0x00
				
	//SET BRANCH
	SBRK $  0x00



//BRANCH
NOP $  0x00
BR $  0x00



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



//INTERUPT
NOP $  0x00
LDX $# 0x00
INT $  0x00



-----------------------------------------------------------------

5*0

-----------------------------------------------------------------



-

init 0












































