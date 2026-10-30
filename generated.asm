section .text
	global _start
_start:
	push 5
	push 7
	push 8
	mov rax, 60
	pop rdi
	syscall
