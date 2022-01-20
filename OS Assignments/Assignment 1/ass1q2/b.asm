 
 section .bss
    strStorage resb 64
    strPosStorage resb 8

 section .data
    text db "Printing in function B",10
    text2 db " ",10
    text3 db "Printing ASCII first in Little Endian: "
    text4 db "Printing the integer: "
 
section .text
    global b
    extern c
    
 
b:  
    pop r10
    push c

    and r9,0
    mov r9,rdi

    mov rax,1
    mov rdi,1
    mov rsi,text
    mov rdx,25
    syscall

    mov rax,1
    mov rdi,1
    mov rsi,text3
    mov rdx,39
    syscall


    mov [strPosStorage],r9

    mov rax,1
    mov rdi,1
    mov rsi,strPosStorage
    mov rdx,8
    syscall

    mov rax,1
    mov rdi,1
    mov rsi,text2
    mov rdx,2
    syscall

    mov rax,1
    mov rdi,1
    mov rsi,text4
    mov rdx,22
    syscall

    mov rax, r9
    call printASCII
    syscall

    ret

printASCII:
    mov rcx,strStorage
    mov rbx,10
    mov[rcx],rbx
    inc rcx
    mov [strPosStorage], rcx

asciiLoopDigit:
    mov rdx,0
    mov rbx,10
    div rbx
    push rax
    add rdx,48

    mov rcx,[strPosStorage]
    mov[rcx],dl
    inc rcx
    mov [strPosStorage],rcx

    pop rax
    cmp rax,0
    jne asciiLoopDigit

arrayReversalASCII:
    mov rcx, [strPosStorage]

    mov rax,1
    mov rdi,1
    mov rsi,rcx
    mov rdx,1
    syscall

    mov rcx,[strPosStorage]
    dec rcx
    mov[strPosStorage],rcx

    cmp rcx,strStorage
    jge arrayReversalASCII
    ret
    
