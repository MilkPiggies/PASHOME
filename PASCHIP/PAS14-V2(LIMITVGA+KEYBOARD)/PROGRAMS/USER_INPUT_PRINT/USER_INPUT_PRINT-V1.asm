### USER INPUT PRINT - V1 ###



####################
#  !LOCEND = 0x0F  #
#  !LOCRET = 0x11  #
#				   #
#  !LINEND = 0x13  #
#  !LINRET = 0x15  #
####################


0x2D = '-'


#################################################################



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
			LDA $# 0x3E (!LOCENDX) [3E]
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
			LDA $# 0x1B (!LOCRETX) [1B]
			PHA $  0x00 (should be on 0x0D on stack)
	
	
	
	//DRAW_LINE
	NOP $  0x00
	
		//WRITE !LINEND
		NOP $  0x00

			//POINT STACK TO A
			NOP $  0x00
			LDY $# 0x0A
			SSP $  0x00
	
			//SEND !LINENDY TO STACK
			NOP $  0x00
			LDA $# 0x00 (!LINENDY) [0]
			PHA $  0x00 (should be on 0x0A on stack)

			//SEND !LINENDX TO STACK
			NOP $  0x00
			LDA $# 0x3E (!LINENDX) [3E]
			PHA $  0x00 (should be on 0x0B on stack)

		//WRITE !LINRET
		NOP $  0x00

			//POINT STACK TO C (stack already pointed to C)
			NOP $  0x00
			LDY $# 0x0C
			SSP $  0x00

			//SEND !LINRETY TO STACK
			NOP $  0x00
			LDA $# 0x00 (!LINRETY) [00]
			PHA $  0x00 (should be on 0x0C on stack)

			//SEND !LINRETX TO STACK
			NOP $  0x00
			LDA $# 0x1B (!LINRETX) [1B]
			PHA $  0x00 (should be on 0x0D on stack)



#################################################################
-----------------------------------------------------------------


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
	


//EXIT (IF ERROR)
NOP $  0x00
LDX $# 0x00
INT $  0x00



-----------------------------------------------------------------



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

		//LOAD 0x0A TO A
		LDA $# 0x0A
		
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
		LDY $# 0x0C 
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



//EXIT
NOP $  0x00
LDX $# 0x00
INT $  0x00



-----------------------------------------------------------------










