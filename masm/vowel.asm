.model small

.stack 100h

.data 
    msg1 db "enter string: $"
    msg2 db 10,13,"no of vovels: $"

    MAX_LEN db 80
    ACTUAL_LEN db ?
    INPUT_STRING db 80 dup("$")

.code 
start:
    mov ax,@data
    mov ds,ax

    lea dx, msg1
    mov ah,09h
    int 21h

    lea dx,MAX_LEN
    mov ah,0ah ; read string from user
    int 21h

    lea si,INPUT_STRING
    mov bx,0
    mov ch,0
    mov cl,ACTUAL_LEN

check_char:
    mov al,[si]

    cmp cx,0
    je display_result

    cmp al,"A"
    je vovel_found
    cmp al,"E"
    je vovel_found
    cmp al,"I"
    je vovel_found
    cmp al,"O"
    je vovel_found
    cmp al,"U"
    je vovel_found
    cmp al,"a"
    je vovel_found
    cmp al,"e"
    je vovel_found
    cmp al,"i"
    je vovel_found
    cmp al,"o"
    je vovel_found
    cmp al,"u"
    je vovel_found

    jmp next_char
vovel_found:
    inc bx
next_char:
    inc si 
    dec cx
    jmp check_char

display_result:
    lea dx,msg2
    mov ah,09h
    int 21h

    mov ax,bx
    mov cx,0
    mov bx,10

convert_loop:
    xor dx,dx
    cmp ax,0
    je print_loop

    div bx
    add dl,"0"
    push dx
    inc cx
    jmp convert_loop

print_loop:
    cmp cx,0
    je done_print
    pop dx
    mov ah,02h
    int 21h
    dec cx
    jmp print_loop
done_print:
    mov ah,4ch
    int 21h
end start
