	global ft_list_size		; int	ft_list_size(t_list *begin_list)
	
ft_list_size:
	cmp rdi, 0
	je return_0
	mov rdi, qword [rdi + 8]
	call ft_list_size
	inc rax
	ret
return_0:
	mov rax, 0
	ret
