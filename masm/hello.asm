; Hello World program in assembly language

.model small
.stack 100h

.data 
    msg db "Hellow world!$"
.code
start:
    mov ax, @data
    mov ds, ax

    lea dx, msg
    mov ah, 09h
    int 21h

    mov ah, 4Ch
    int 21h
end start