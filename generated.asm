section .text
	global _start
_start:
	mov rax, 60
	mov rdi, 8
	imul rdi, 2
	add rdi, 10
	syscall