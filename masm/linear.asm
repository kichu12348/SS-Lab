.model small
.stack 100h

.data 
    msg1 db "enter number to be searched: $"
    arr dw 20 dup(?)
    msg2 db 13,10,"number found at position: $"
    msg3 db 13,10,"number not found $"
    msg4 db "enter number of elements: $"
    msg5 db "enter element: $"
    count dw ?

.code 
start:
    mov ax,@data
    mov ds,ax


    lea dx,msg4
    mov ah,09h
    int 21h

    call read_num
    mov count,ax
    mov cx,ax
    lea di,arr

input_arr_loop:
    lea dx,msg5
    mov ah,09h
    int 21h
    call read_num
    mov [di],ax
    add di,2
    loop input_arr_loop

    lea dx,msg1
    mov ah,09h
    int 21h
    call read_num

    lea si,arr
    mov bx,0
    mov cx,count

find_loop:
    cmp ax,[si]
    je found
    inc bx
    add si,2
    loop find_loop
not_found:
    lea dx,msg3
    mov ah,09h
    int 21h
    jmp exit

found:
    lea dx,msg2
    mov ah,09h
    int 21h
    mov ax,bx
    call print_num

exit:
    mov ah,4ch
    int 21h

read_num proc
    push cx
    mov bx,0
    mov cx,10

read_loop:
    mov ah,01h
    int 21h

    cmp al,13
    je done_input
    sub al,"0"
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
    pop cx
    ret
read_num endp

print_num proc
    mov bx,10
    mov cx,0

convert_loop:
    xor dx,dx
    div bx
    add dl,"0"
    push dx
    inc cx
    cmp ax,0
    je print_loop
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
    ret
print_num endp

end start