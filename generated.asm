section .text
	global _start
_start:
	mov rax, 60
	pop rdi
	syscall
	push 5
	mov rax, 60
	pop rdi
	syscall
