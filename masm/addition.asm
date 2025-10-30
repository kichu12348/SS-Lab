; addition of two 16 bit numbers in assembly language

.model small
.stack 100h

.data 
    msg db "enter number: $"
    num1 dw ?
    num2 dw ?
.code
start:
    mov ax, @data
    mov ds, ax

    call display_message
    call read_number
    mov num1, ax

    call display_message
    call read_number
    mov num2, ax

    mov ax, num1
    add ax, num2
    call print_number

    mov ah, 4Ch
    int 21h

display_message proc
    lea dx, msg
    mov ah, 09h
    int 21h
    ret
display_message endp

read_number proc
    mov bx,0
    mov cx,10

read_loop:
    mov ah,01h
    int 21h
    cmp al,13
    je done_input
    sub al,30h
    mov ah,0
    push ax
    mov ax,bx
    mul cx
    mov bx,ax
    pop ax
    add bx,ax
    jmp read_loop

done_input:
    mov ax,bx
    ret
read_number endp

print_number proc
    mov cx,0
    mov bx,10

convert_loop:
    xor dx,dx ; clear dx before division
    div bx ; result in ax, remainder in dx
    add dl,30h ; dl holds the value of the last digit dh is 0
    push dx
    inc cx
    cmp ax,0
    jne convert_loop
print_loop:
    pop dx
    mov ah,02h ; 02h is the DOS function to print a character which is in dl
    int 21h
    dec cx
    jnz print_loop
    ret
print_number endp

end start