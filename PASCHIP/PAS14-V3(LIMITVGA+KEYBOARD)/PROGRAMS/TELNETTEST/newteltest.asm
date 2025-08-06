PRINT "READY: "
INTERUPT
WAIT FOR USER INPUT
RECV CH FROM TELNET
(check if CH is certain value?)


//STORE CH FROM TELNET
(use $40 as a pointer)
use ZADDR to store CH

SEND CH TO TELNET

adjust $40 accordingly






//

:initialize
SET $20 to 0x30
SET $21 to 0x00


:start
PRINT "READY: "


:interupt
INTERUPT
(wait for user input)
STORE $20 ON Z
RECIEVE TELNET CHAR
SEND TELNET CHAR
TGLZADDR
STORE X ON $Z
TGLZADDR


:check_1
(check if $20 is 0x36)
STORE $Z ON A
STORE 0x36 ON B
COMPARE A AND B

IF EQUAL, BRANCH TO ????




//




is the key that was last pressed an "EXIT_KEY"?
get the data off of where $20 is currently pointing to
compare the recieved data with "EXIT_KEY"
if equal branch to ????














----------------------------------------------
//START
NOP $  0x00

//INIT
(Initialize all registers with 0x00)
LDA $# 0x00
LDB $# 0x00
LDX $# 0x00
LDY $# 0x00

//STORE 30 ON $20
NOP $  0x00
LDA $  0x30
STA $# 0x20

//BRANCH BACK
NOP $  0x00

//STORE $20 ON Z
NOP $  0x00
LDX $# 0x00
LDY $  0x20
STZ $# 0x00

//SPACING
(Adds spacing for MC readability)
NOP $  0x00
NOP $  0x00
NOP $  0x00

//PRINT "READY: " ON TELNET
(Sends characters to telnet)
NOP $  0x00
LDX $# 0x52
TELSEND $  0x00
NOP $  0x00
LDX $# 0x45
TELSEND $  0x00
NOP $  0x00
LDX $# 0x41
TELSEND $  0x00
NOP $  0x00
LDX $# 0x44
TELSEND $  0x00
NOP $  0x00
LDX $# 0x59
TELSEND $  0x00
NOP $  0x00
LDX $# 0x3A
TELSEND $  0x00
NOP $  0x00
LDX $# 0x20
TELSEND $  0x00

//SPACING
(Adds spacing for MC readability)
NOP $  0x00
NOP $  0x00
NOP $  0x00

//INTERUPT
(Interupts the execution to let the user type)
NOP $  0x00
LDX $# 0x00
INT $  0x00

//SPACING
(Adds spacing for MC readability)
NOP $  0x00
NOP $  0x00
NOP $  0x00

//UN-INTERUPT
(Once the user sends a key, we get the
key and send back the key)
NOP $  0x00
TELRECV $  0x00
TELSEND $  0x00

//STORE KEY ON $Z
(Store recived key on $Z)
TGLZADDR $  0x00
STX $  0x00
TGLZADDR $ 0x00












//ADD 1 TO $20 (so $20 = 30 + 1)
(Adds 0x01 to $20)
NOP $  0x00
LDA $  0x20
LDB $# 0x01
ADD $  0x00
STA $  0x20

//ADD 1 TO $20 (so $20 = 30 + 1)
NOP $  0x00
LDA $  0x20
LDB $# 0x01
ADD $  0x00
STA $# 0x20

//NEWLINE
NOP $  0x00
LDX $# 0x0A
TELSEND $  0x00

//BACKSPACE x11
NOP $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00
LDX $# 0x08
TELSEND $  0x00

//LOOP BACK 
NOP $  0x00 
LDX $# 0x09
LDY $# 0x00
SBRK $  0x00
BR $  0x00












//CHECK_1
(Checks is $20 is equal to 0x38)
NOP $  0x00

get $20 on A
put 0x38 on B
compare A and B

set branch to :SET_$20=0_AND_REPEAT
branch if equal

-IGNORE CHECK_2 UNTIL MORE REASERCH 
(SO BRANCH TO LOOPBACK INSTEAD)



//CHECK_2
(Checks is $20 points to "ENTER")
NOP $  0x00

get $20 on A
put 0x'ENTER' on B
check if A is equal to B
    if so, branch to :RUNMRAM
    else continue

//CHECK_FAIL
(If the checks fail, add 1 to $20 and loop back)
NOP $  0x00

get $20 on A
put 0x01 on B
add A + B
put A on $20

set branch to loopback
branch








//SEVERAL CHECKS
check if $20 is on 0x28
(if so, we store the command and loop back)
(also set $20 back to 0x30)

check if where $20 points to is "ENTER"
(if so, we exit the loop)

if all checks fail, we add 0x01 to $20
and loop back (plus newline)











--

check if $20 = 0x38
    if equal goto :DONE_LOOPBACK
    else continue

check if keypress (where $20 points to) is 'ENTER'
    if equal goto :DONE_RUNMRAM
    else continue

:RETURN

(add 1 to $20 and loop back?)
--

:DONE_LOOPBACK
send $30 to $37 to MRAM where $18(X) points to
and go back to :RETURN


:DONE_RUNMRAM
switch to MRAM





keypress, + 1 *unless at 0x28
    then set $20 to 0x30
    and branch off to send $30 to $37 to MRAM
    then loop back

    also check if keypress was 'ENTER'
        then branch off to run MRAM




























store ?? on Z

first we print the word "READY: " on the 
telnet console

then we interupt and wait for the user
to input a key

once the user has typed a key, the program
will return in action, we first

    put the recived key on X
    send X to telnet

    store X in RAM according to Z

    check if the key is the exit key
        if = branch 
        else = loop back

    


once the exit key is pressed, we must take
ram values in order.

$21 is A
$22, $23, $24, $25 are C
$26, $27 is B

once the values are stored in the correct
registers, we store those registers on MRAM.


