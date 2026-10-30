section .text
	global _start
_start:
	push 5
	push 7
	push 8
	mov rax, x
	mov rbx, 7
	add rbx
	mov rdi,rax
	mov rax , 60
	syscall
