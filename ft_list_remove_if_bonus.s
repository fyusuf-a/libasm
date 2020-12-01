	global ft_list_remove_if		; t_list* ft_list_remove_if_acc(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void*))

ft_list_remove_if_acc:
	push rbp
	mov rbp, rsp
	cmp rdi, 0
	je return_0
	push rdi						; stack + begin_list
	push rcx						; stack + begin_list + free_fct
	push rsi						; stack + begin_list + free_fct + data_ref
	push rdx 						; stack + begin_list + free_fct + data_ref + cmp
loop:
	mov rdi, qword [rdi] 			; rdi = begin_list->data
	push rdi						; stack + begin_list + free_fct + data_ref + cmp + begin_list->data
	call qword [rbp - 32]			; call cmp
	cmp eax, 0						; cmp returns a 4-byte int
	jne end_loop
	mov rdi, qword [rbp - 40]		; rdi = begin_list->data
	call qword [rbp - 16]			; call free_fct
	mov r8, qword [rbp - 8]			; r8 = begin_list
	mov r9, qword [r8 + 8]			; r9 = begin_list->next
	mov qword [rbp - 8], r9			; begin_list = begin_list->next
	cmp qword [rbp - 8], 0			; if *begin_list == 0
	je return_0						;   return (0);
	mov rdi, qword [rbp - 8]		; rdi = begin_list
	jmp loop
end_loop:
	mov rdx, qword [rbp - 32]		; rdx = cmp
	mov rsi, qword [rbp - 24]		; rsi = data_ref
	mov rcx, qword [rbp - 16]		; rcx = free_fct
	mov r8, qword [rbp - 8]			; r8 = begin_list
	mov rdi, qword [r8 + 8]			; rdi = begin_list->next
	call ft_list_remove_if_acc
	mov rdi, qword [rbp - 8]		; rdi = begin_list
	mov qword [rdi + 8], rax		; begin_list->next = ft_list_remove_if(begin_list->next, data_ref, cmp, free_fct)
	mov rax, rdi					; return (begin_list)
	leave
	ret
return_0:
	mov rax, 0
	leave
	ret

ft_list_remove_if:
	push rbp
	mov rbp, rsp
	push rdi
	mov rdi, qword [rdi]
	call ft_list_remove_if_acc
	pop rdi
	mov [rdi], rax
	leave
	ret
