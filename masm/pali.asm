.model small
.stack 100h

.data
    msg1 db "enter a string: $"
    yesM db 10,13,"is a palindrome$"
    noM db 10,13,"not a palindrome$"

    MAX_LEN db 80
    ACTUAL_LEN db ?
    INPUT_STRING db 80 dup("$")

.code
start:
    mov ax,@data
    mov ds,ax

    lea dx,msg1
    mov ah,09h
    int 21h

    lea dx,MAX_LEN
    mov ah,0ah
    int 21h

    lea di, INPUT_STRING
    lea si, INPUT_STRING

    mov cx,0
    mov cl,ACTUAL_LEN

    add di,cx ; increment di to size of input string
    dec di ; decrement di by 1 to point to the last character

check_loop:
    cmp si,di
    jae is_pali ; jump if above or equal i.e the pointers si and di are at the middle and over each other hence its a palindrome

    mov al,[si] ; put values of si pointer and di pointer
    mov bl,[di]

    cmp al,bl 
    jne is_not_pali ; if not equal then its not same

    dec di
    inc si

    jmp check_loop

is_not_pali:
    lea dx,noM
    mov ah,09h
    int 21h
    jmp exit

is_pali:
    lea dx,yesM
    mov ah,09h
    int 21h
exit:
    mov ah,4ch
    int 21h
end start

