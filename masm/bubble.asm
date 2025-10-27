.model small
.stack 100h

.data 
    msg1 db "enter no of elems: $"
    msg2 db "enter elem: $"
    com db ", $"
    count dw ?
    arr dw 20 dup(?)

.code 
start:
    mov ax,@data
    mov ds,ax

    lea dx,msg1
    mov ah,09h
    int 21h

    call input_num
    mov count,ax
    mov cx,ax
    
    lea di,arr

input_arr_num:
    lea dx,msg2
    mov ah,09h
    int 21h

    call input_num
    mov [di],ax
    add di,2
    loop input_arr_num


mov cx, count ; cx = n
dec cx ; cx = n-1

outer_loop:
    mov dx,cx ; dx will go from n-1 to n-2 so on
    lea si, arr ; load starting address of array arr into si (source index)

inner_loop:
    mov ax,[si] ; ax = arr[si]
    cmp ax,[si+2] ; compare ax and arr[si+2] si+2 because next word is after 2 bytes 
    jle no_swap ; if ax ie arr[si] <= arr[si+2] then dont swap

    ; this is the swaping part
    mov bx,[si+2] ; bx = arr[si+2]
    mov [si+2],ax ; arr[si+2] = ax
    mov [si],bx ; arr[si] = bx

no_swap:
    add si,2 ; increment si by 2 bytes to point to next word
    dec dx ; dx = dx-1
    jnz inner_loop

    loop outer_loop
    

    lea si, arr
    mov cx, count
print_arr_loop:
    mov ax,[si]
    call print_num

    lea dx,com
    mov ah,09h
    int 21h

    add si,2
    loop print_arr_loop

end_prog:
    mov ah,4ch
    int 21h

input_num proc
    push cx
    mov bx,0
    mov cx,10
read_loop:
    mov ah, 01h
    int 21h

    cmp al,13
    je done_inp

    sub al,"0"
    mov ah,0
    push ax
    mov ax,bx
    mul cx
    mov bx,ax
    pop ax
    add bx,ax
    jmp read_loop
done_inp:
    mov ax,bx
    pop cx
    ret
input_num endp

print_num proc
    push cx
    mov bx,10
    mov cx,0

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
    pop cx
    ret
print_num endp

end start