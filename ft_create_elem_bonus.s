	global ft_create_elem			; t_list	*ft_create_elem(void *data);
	extern malloc

	section .text

ft_create_elem:
	push rbp
	mov rbp, rsp
	push rdi
	mov rdi, 16 				; rdi = sizeof(t_list)
	call malloc
	pop rdi
	mov qword [rax], rdi
	mov qword [rax + 8], 0
	leave
	ret
