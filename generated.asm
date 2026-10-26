section .text
	global _start
_start:
	mov rax, 60
	mov rdi, 6
	add rdi, 2
	syscall