section .text
    global _start

_start:
    mov rax, 60
    mov rdi, 5
    add rdi , 12
    syscall

