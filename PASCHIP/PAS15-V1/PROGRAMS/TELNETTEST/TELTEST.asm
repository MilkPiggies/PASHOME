//PRINT "READY: "
NOP $  0x00

    //SEND 'R' TO TELNET
    NOP $  0x00

        //LOAD 'R' ON X
        LDX $# 0x52

        //TELSEND
        TELSEND $  0x00

    //SEND 'E' TO TELNET
    NOP $  0x00

        //LOAD 'E' ON X
        LDX $# 0x45

        //TELSEND
        TELSEND $  0x00

    //SEND 'A' TO TELNET
    NOP $  0x00

        //LOAD 'A' ON X
        LDX $# 0x41

        //TELSEND 
        TELSEND $  0x00

    //SEND 'D' ON TELNET
    NOP $  0x00

        //LOAD 'D' ON X
        LDX $# 0x44

        //TELSEND
        TELSEND $  0x00

    //SEND 'Y' TO TELNET
    NOP $  0x00

        //LOAD 'Y' ON X
        LDX $# 0x59

        //TELSEND 
        TELSEND $  0x00

    //SEND ':' TO TELNET
    NOP $  0x00

        //LOAD ':' ON X
        LDX $# 0x3A

        //TELSEND
        TELSEND $  0x00

    //SEND ' ' TO TELNET
    NOP $  0x00

        //LOAD ' ' ON X
        LDX $# 0x20

        //TELSEND 
        TELSEND $  0x00

 -

//INTERUPT
NOP $  0x00
LDX $# 0x00
INT $  0x00



//SPACE
NOP $  0x00



//TELRECV
TELRECV $  0x00

//STORE X ON $40
STX $# 0x40

//TELSEND
TELSEND $  0x00

