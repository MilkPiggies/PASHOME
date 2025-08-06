#include <stdio.h>
#include <stdlib.h>

void opvrFunc()
{
	// if OP = 0
	// if not any possible op -------------
	if( opv == 0)
	{
		printf("NO OP \n");
		res = 0x999;
		goto funcend;
	}
	
	
	
	
	
	
//237 1
	
	// if OP = NOP [NP]
	if( opv == 237 && op1 == 78 && op3 == 80)
	{
		printf("NOP \n");
		res = 0x00;
		goto funcend;
	}
	
	// if OP = SMM [SM]
	if( opv == 237 && op1 == 83 && op3 == 77)
	{
		printf("SMM \n");
		res = 0x20;
		goto funcend;
	}
	
	// if OP = TAX [TX]
	if( opv == 237 && op1 == 84 && op3 == 88)
	{
		printf("TAX \n");
		res = 0xF0;
		goto funcend;
	}
	
	// if OP = TXA [TA]
	if( opv == 237 && op1 == 84 && op3 == 65)
	{
		printf("TXA \n");
		res = 0x110;
		goto funcend;
	}
	
	
	
	
	
	
//209 2
	
	// if OP = LDA [LA]
	if( opv == 209 && op1 == 76 && op3 == 65)
	{
		printf("LDA \n");
		res = 0x30;
		goto funcend;
	}
	
	// if OP = CLB [CB]
	if( opv == 209 && op1 == 67 && op3 == 66)
	{
		printf("CLB \n");
		res = 0x1A0;
		goto funcend;
	}
	
	
	
	
	
	
//232 3

	// if OP = LDX [LX]
	if( opv == 232 && op1 == 76 && op3 == 88)
	{
		printf("LDX \n");
		res = 0x40;
		goto funcend;
	}
	
	// if OP = STA [SA]
	if( opv == 232 && op1 == 83 && op3 == 65)
	{
		printf("STA \n");
		res = 0x60;
		goto funcend;
	}
	
	// if OP = PHP [PP]
	if( opv == 232 && op1 == 80 && op3 == 80)
	{
		printf("PHP \n");
		res = 0xC0;
		goto funcend;
	}
	
	
	
	
	
	
//233 4

	// if OP = LDY [LY]
	if( opv == 233 && op1 == 76 && op3 == 89)
	{
		printf("LDY \n");
		res = 0x50;
		goto funcend;
	}
	
	// if OP = CLZ [CZ]
	if( opv == 233 && op1 == 67 && op3 == 90)
	{
		printf("CLZ \n");
		res = 0x1E0;
		goto funcend;
	}
	
	
	
	
	
	
//255 5

	// if OP = STX [SX]
	if( opv == 255 && op1 == 83 && op3 == 88)
	{
		printf("STX \n");
		res = 0x70;
		goto funcend;
	}
	
	// if OP = TSX [TX]
	if( opv == 255 && op1 == 84 && op3 == 88)
	{
		printf("TSX \n");
		res = 0x90;
		goto funcend;
	}
	
	// if OP = TXS [TS]
	if( opv == 255 && op1 == 84 && op3 == 83)
	{
		printf("TXS \n");
		res = 0xA0;
		goto funcend;
	}
	
	
	
	
	
	
//221 6
	
	// if OP = PLA [PA]
	if( opv == 221 && op1 == 80 && op3 == 65)
	{
		printf("PLA \n");
		res = 0xD0;
		goto funcend;
	}
	
	// if OP = CLN [CN]
	if( opv == 221 && op1 == 67 && op3 == 78)
	{
		printf("CLN \n");
		res = 0x1D0;
		goto funcend;
	}
	
	
	
	
	
	
//236 7
	
	// if OP = PLP [PLP]
	if( opv == 236 && op1 == 80 && op2 == 76 && op3 == 80)
	{
		printf("PLP \n");
		res = 0xE0;
		goto funcend;
	}
	
	// if OP = CPY [CY]
	if( opv == 236 && op1 == 67 && op2 == 89)
	{
		printf("CPY \n");
		res = 0x2C0;
		goto funcend;
	}
	
	
	
	
	
	
//238 8

	// if OP = TAY [TY]
	if( opv == 238 && op1 == 84 && op3 == 89)
	{
		printf("TAY \n");
		res = 0x100;
		goto funcend;
	}
	
	// if OP = TYA [TA]
	if( opv == 238 && op1 == 84 && op3 == 65)
	{
		printf("TYA \n");
		res = 0x120;
		goto funcend;
	}
	
	// if OP = MUL [ML]
	if( opv == 238 && op1 == 77 && op3 == 76)
	{
		printf("MUL \n");
		res = 0x280;
		goto funcend;
	}
	
	
	
	
	
	
//211 9

	// if OP = CLD [CD]
	if( opv == 211 && op1 == 67 && op3 == 68)
	{
		printf("CLD \n");
		res = 0x140;
		goto funcend;
	}
	
	// if OP = AND [AD]
	if( opv == 211 && op1 == 65 && op3 == 68)
	{
		printf("AND \n");
		res = 0x1F0;
		goto funcend;
	}
	
	
	
	
	
	
//216 10

	// if OP = CLI [CI]
	if( opv == 216 && op1 == 67 && op3 == 73)
	{
		printf("CLI \n");
		res = 0x150;
		goto funcend;
	}
	
	// if OP = CLS [CS]
	if( opv == 216 && op1 == 67 && op3 == 83)
	{
		printf("CLS \n");
		res = 0x1C0;
		goto funcend;
	}
	
	// if OP = SBC [SC]
	if( opv == 216 && op1 == 83 && op3 == 67)
	{
		printf("SBC \n");
		res = 0x270;
		goto funcend;
	}
	
	// if OP = BCS [BS]
	if( opv == 216 && op1 == 66 && op3 == 83)
	{
		printf("BCS \n");
		res = 0x2E0;
		goto funcend;
	}
	
	// if OP = BEQ [BQ]
	if( opv == 216 && op1 == 66 && op3 == 81)
	{
		printf("BEQ \n");
		res = 0x2F0;
		goto funcend;
	}
	
	// if OP = BMI [BI]
	if( opv == 216 && op1 == 66 && op3 == 73)
	{
		printf("BMI \n");
		res = 0x300;
		goto funcend;
	}
	
	
	
//219 11

	// if OP = SEC [SC]
	if( opv == 219 && op1 == 83 && op3 == 67)
	{
		printf("SEC \n");
		res = 0x170;
		goto funcend;
	}
	
	// if OP = BVC [BC]
	if( opv == 219 && op1 == 66 && op3 == 67)
	{
		printf("BVC \n");
		res = 0x330;
		goto funcend;
	}
	
	
	
//200 12

	// if OP = ADC [AC]
	if( opv == 200 && op1 == 65 && op3 == 67)
	{
		printf("ADC \n");
		res = 0x260;
		goto funcend;
	}
	
	// if OP = BCC [BC]
	if( opv == 200 && op1 == 66 && op3 == 67)
	{
		printf("BCC \n");
		res = 0x2D0;
		goto funcend;
	}
	
	
	
//235 13

	// if OP = CPX [CX]
	if( opv == 235 && op1 == 67 && op3 == 88)
	{
		printf("CPX \n");
		res = 0x2B0;
		goto funcend;
	}
	
	// if OP = BVS [BS]
	if( opv == 235 && op1 == 66 && op3 == 83)
	{
		printf("BVS \n");
		res = 0x340;
		goto funcend;
	}
	
	// if OP = INT [IT]
	if( opv == 235 && op1 == 73 && op3 == 84)
	{
		printf("INT \n");
		res = 0x3E0;
		goto funcend;
	}
	
	
	
//502 14

	// if OP = WR2ADDR [WR]
	if( opv == 502 && op1 == 87 && op3 == 82)
	{
		printf("WR2ADDR \n");
		res = 0x3D0;
		goto funcend;
	}
	
	// if OP = WRrcx [Wx]
	if( opv == 502 && op1 == 87 && op5 == 120)
	{
		printf("WRrcx \n");
		res = 0x530;
		goto funcend;
	}
	
	
	
//389 15

	// if OP = WRdx [Wx]
	if( opv == 389 && op1 == 87 && op4 == 120)
	{
		printf("WRdx \n");
		res = 0x4A0;
		goto funcend;
	}
	
	// if OP = WRax [Wax]
	if( opv == 389 && op1 == 87 && op3 == 97 && op4 == 120)
	{
		printf("WRax \n");
		res = 0x4D0;
		goto funcend;
	}
	
		
	
	
	
	
//REST

	// if OP = SPP 
	if( opv == 243)
	{
		printf("SPP \n");
		res = 0x10;
		goto funcend;
	}
	
	// if OP = STY
	if( opv == 256)
	{
		printf("STY \n");
		res = 0x80;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = PHA
	if( opv == 217)
	{
		printf("PHA \n");
		res = 0xB0;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = CLC
	if( opv == 210)
	{
		printf("CLC \n");
		res = 0x130;
		goto funcend;
	}

	// if OP = CLV
	if( opv == 229)
	{
		printf("CLV \n");
		res = 0x160;
		goto funcend;
	}
	
	// if OP = SED
	if( opv == 220)
	{
		printf("SED \n");
		res = 0x180;
		goto funcend;
	}

	// if OP = SEI
	if( opv == 225)
	{
		printf("SEI \n");
		res = 0x190;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = CLE
	if( opv == 212)
	{
		printf("CLE \n");
		res = 0x1B0;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = NAND
	if( opv == 289)
	{
		printf("NAND \n");
		res = 0x200;
		goto funcend;
	}
	
	// if OP = OR
	if( opv == 161)
	{
		printf("OR \n");
		res = 0x210;
		goto funcend;
	}
	
	// if OP = XOR
	if( opv == 249)
	{
		printf("XOR \n");
		res = 0x220;
		goto funcend;
	}
	
	// if OP = NOR
	if( opv == 239)
	{
		printf("NOR \n");
		res = 0x230;
		goto funcend;
	}
	
	// if OP = XNOR
	if( opv == 327)
	{
		printf("XNOR \n");
		res = 0x240;
		goto funcend;
	}
	
	// if OP = BIT
	if( opv == 223)
	{
		printf("BIT \n");
		res = 0x250;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = DIV
	if( opv == 227)
	{
		printf("DIV \n");
		res = 0x290;
		goto funcend;
	}
	
	// if OP = CMP
	if( opv == 224)
	{
		printf("CMP \n");
		res = 0x2A0;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = BNE
	if( opv == 213)
	{
		printf("BNE \n");
		res = 0x310;
		goto funcend;
	}
	
	// if OP = BPL
	if( opv == 222)
	{
		printf("BPL \n");
		res = 0x320;
		goto funcend;
	}
	
	// if OP = BSE
	if( opv == 218)
	{
		printf("BSE \n");
		res = 0x350;
		goto funcend;
	}
	
	// if OP = BBE
	if( opv == 201)
	{
		printf("BBE \n");
		res = 0x360;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = WR2OP
	if( opv == 378)
	{
		printf("WR2OP \n");
		res = 0x370;
		goto funcend;
	}
	
	// if OP = SKR
	if( opv == 240)
	{
		printf("SKR \n");
		res = 0x380;
		goto funcend;
	}

	// if OP = BRMwr
	if( opv == 458)
	{
		printf("BRMwr \n");
		res = 0x390;
		goto funcend;
	}
	
	// if OP = BRKwr
	if( opv == 456)
	{
		printf("BRKwr \n");
		res = 0x3A0;
		goto funcend;
	}
	
	// if OP = SSP
	if( opv == 246)
	{
		printf("SSP \n");
		res = 0x3F0;
		goto funcend;
	}
	
	// if OP = TLGxymad
	if( opv == 778)
	{
		printf("TLGxymad \n");
		res = 0x410;
		goto funcend;
	}
	
	// if OP = RNDse
	if( opv == 444)
	{
		printf("RNDse \n");
		res = 0x430;
		goto funcend;
	}
	
	// if OP = RNDne
	if( opv == 439)
	{
		printf("RNDne \n");
		res = 0x440;
		goto funcend;
	}
	
	// if OP = RNDwr
	if( opv == 461)
	{
		printf("RNDwr \n");
		res = 0x450;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = WRdl+dh
	if( opv == 624)
	{
		printf("WRdl+dh \n");
		res = 0x460;
		goto funcend;
	}
	
	// if OP = WRcl+ch
	if( opv == 622)
	{
		printf("WRcl+ch \n");
		res = 0x470;
		goto funcend;
	}
	
	// if OP = WRbl+bh
	if( opv == 620)
	{
		printf("WRbl+bh \n");
		res = 0x480;
		goto funcend;
	}
	
	// if OP = WRal+ah
	if( opv == 618)
	{
		printf("WRal+ah \n");
		res = 0x490;
		goto funcend;
	}
	
	// if OP = WRcx
	if( opv == 388)
	{
		printf("WRcx \n");
		res = 0x4B0;
		goto funcend;
	}
	
	// if OP = WRbx
	if( opv == 387)
	{
		printf("WRbx \n");
		res = 0x4C0;
		goto funcend;
	}
	
	// if OP = WRedx
	if( opv == 490)
	{
		printf("WRedx \n");
		res = 0x4E0;
		goto funcend;
	}
	
	// if OP = WRecx
	if( opv == 489)
	{
		printf("WRecx \n");
		res = 0x4F0;
		goto funcend;
	}
	
	// if OP = WRebx
	if( opv == 488)
	{
		printf("WRebx \n");
		res = 0x500;
		goto funcend;
	}
	
	// if OP = WReax
	if( opv == 487)
	{
		printf("WReax \n");
		res = 0x510;
		goto funcend;
	}
	
	// if OP = WRrdx
	if( opv == 503)
	{
		printf("WRrdx \n");
		res = 0x520;
		goto funcend;
	}
	
	// if OP = WRrbx
	if( opv == 501)
	{
		printf("WRrbx \n");
		res = 0x540;
		goto funcend;
	}
	
	//if OP = WRrax
	if( opv == 500)
	{
		printf("WRrax \n");
		res = 0x550;
		goto funcend;
	}
	
	
	
	
	
	
	// if OP = CHNGmode
	if( opv == 709)
	{
		printf("CHNGmode \n");
		res = 0x620;
		goto funcend;
	}
	
	// if OP = CHNGrtc
	if( opv == 617)
	{
		printf("CHNGrtc \n");
		res = 0x630;
		goto funcend;
	}
	
	// if OP = PESwrval
	if( opv == 788)
	{
		printf("PESwrval \n");
		res = 0x640;
		goto funcend;
	}
	
	// if OP = PESwrkey
	if( opv == 794)
	{
		printf("PESwrkey \n");
		res = 0x650;
		goto funcend;
	}
	
	// if OP = PESwrres
	if( opv == 795)
	{ 
		printf("PESwrres \n");
		res = 0x660;
		goto funcend;
	}
	
	// if OP = PESmdtgl
	if( opv == 768)
	{
		printf("PESmdtgl \n");
		res = 0x670;
		goto funcend;
	}
	
	// if OP = INTdis
	if( opv == 555)
	{
		printf("INTdis \n");
		res = 0x680;
		goto funcend;
	}
	
	// if OP = SmORkADR
	if( opv == 675)
	{
		printf("SmORkADR \n");
		res = 0x690;
		goto funcend;
	}
	
	// if OP = TGLkmode
	if( opv == 759)
	{
		printf("TGLkmode \n");
		res = 0x6A0;
		goto funcend;
	}
	
	// if OP = CLRkmode
	if( opv == 753)
	{
		printf("CLRkmode \n");
		res = 0x6B0;
		goto funcend;
	} 
	
	// if OP = JMP
	if( opv == 231)
	{
		printf("JMP \n");
		res = 0x6C0;
		goto funcend;
	}
	
	// if OP = WRkeyop
	if( opv == 721)
	{
		printf("WRkeyop \n");
		res = 0x6D0;
		goto funcend;
	}
	
	// if OP = WR2key
	if( opv == 548)
	{
		printf("WR2key \n");
		res = 0x6E0;
		goto funcend;
	}
	
	// if OP = KTGLovfl
	if( opv == 745)
	{
		printf("KTGLovfl \n");
		res = 0x6F0;
		goto funcend;
	}
	
	// if OP = WRledset
	if( opv == 810)
	{
		printf("WRledset \n");
		res = 0x700;
		goto funcend;
	}
	
	// if OP = WR2rled
	if( opv == 642)
	{
		printf("WR2rled \n");
		res = 0x710;
		goto funcend;
	}
	
	// if OP = CLRscrn
	if( opv == 663)
	{
		printf("CLRscrn \n");
		res = 0x720;
		goto funcend;
	}
	
	// if OP = STOREy
	if( opv == 518)
	{
		printf("STOREy \n");
		res = 0x730;
		goto funcend;
	}
	
	// if OP = Yset
	if( opv == 421)
	{
		printf("Yset \n");
		res = 0x740;
		goto funcend;
	}
	
	
	



funcend:
	
printf(" \n");

}
