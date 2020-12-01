	global ft_list_push_front		;void ft_list_push_front(t_list **begin_list, void *data);
	extern ft_create_elem

ft_list_push_front:
	push rbp
	mov rbp, rsp
	cmp rdi, 0
	je quit
	push rsi
	push rdi
	mov rdi, rsi
	call ft_create_elem
	pop rdi
	mov rbx, qword [rdi]
	mov qword [rax + 8], rbx
	mov qword [rdi], rax
quit:
	leave
	ret
