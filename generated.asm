section .text
	global _start
_start:
	mov rax, 1
	mov rbx, 1
	add rax, rbx
	mov rdi, rax
	add rdi, 1
	mov rax , 60
	syscall