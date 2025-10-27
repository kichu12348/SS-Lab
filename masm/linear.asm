; linear search in assembly language

.model small
.stack 100h

.data 
    arr dw 10,20,30,40

    index dw ?

    read_num_msg db "enter number: $"
    found_msg db " found at: $"
    not_found_msg db "item not found!$"

.code 

start:
    mov ax,@data
    mov ds,ax

    call read_number
    
    mov bx,0
    mov cx,4
    

    lea si,arr ; loads the starting address of arr(array) into si(source index)

find_loop:
    cmp [si], ax
    je found

    add si,2 ; add 2 bytes to point to next word i.e 10->20 or 20->30 and so on
    inc bx ;increment bx by 1 i.e bx=bx+1

    loop find_loop

not_found:
    lea dx,not_found_msg
    mov ah,09h
    int 21h
    jmp exit

found:
    mov index,bx
    call print_num
    lea dx, found_msg
    mov ah,09h
    int 21h
    mov ax,index
    call print_num

exit:
    mov ah,4ch
    int 21h

read_number proc
    lea dx, read_num_msg
    mov ah,09h
    int 21h

    mov bx,0
    mov cx,10
read_num_loop:
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
    jmp read_num_loop
done_input:
    mov ax,bx
    ret
read_number endp

print_num proc
    mov cx,0
    mov bx,10

push_loop:
    xor dx,dx
    div bx
    add dl,30h
    push dx
    inc cx
    cmp ax,0 
    jne push_loop
print_loop:
    pop dx
    mov ah,02h
    int 21h
    dec cx
    jnz print_loop
    ret
print_num endp


end start