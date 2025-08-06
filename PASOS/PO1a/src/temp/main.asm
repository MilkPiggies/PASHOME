org 0x7C00
bits 16

;%define ENDL 0x0D, 0x0A 
;above is old



start:
    jmp main

    

main:

    ;Print a character
    mov ah, 0x0e
    mov al, 'L'
    int 0x10

    hlt



.halt:
    jmp .halt



msg_hello: db 'Hello world!', ENDL, 0



times 510-($-$$) db 0
dw 0AA55h



