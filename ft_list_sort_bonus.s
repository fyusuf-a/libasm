	global ft_list_sort
	extern print_char_list

ft_list_sort_acc:
	push rbp
	mov rbp, rsp
	;call print_char_list
	mov r8, qword [rdi + 8]		; r8 = begin_list->next
	cmp qword [rdi + 8], 0
	je return_third_arg
	push rdx 					; stack + isSorted
	push rsi 					; stack + isSorted + cmp
	push rdi 					; stack + isSorted + cmp + begin_list
	push r8 					; stack + isSorted + cmp + begin_list + begin_list->next
	mov rdi, qword [rdi] 		; rdi = begin_list->data
	mov rsi, qword [r8]			; rsi = begin_list->next->data
	call qword [rbp - 16] 		; call cmp
	cmp eax, 0					; return of cmp is an int (4 bytes)
	jl return_recurse
	mov r8, qword [rbp - 32]	; r8 = begin_list->next
	mov rdi, qword [rbp - 24]	; rdi = begin_list
	mov r9, qword [rdi] 		; r9 = begin_list->data
	mov r10, qword [r8] 		; r10 = begin_list->next->data
	mov qword [rdi], r10 		; begin_list->data = r10
	mov qword [r8], r9			; begin_list->next->data = r9
	mov qword [rbp - 8], 0
return_recurse:
	mov rdi, r8
	mov rsi, qword [rbp - 16]	; rsi = cmp
	mov rdx, qword [rbp - 8]	; rdx = isSorted
	call ft_list_sort_acc
	leave
	ret
return_third_arg:
	mov rax, rdx
	leave
	ret

ft_list_sort:
	push rbp
	mov rbp, rsp
	push rdi
	push rsi
	mov rdi, qword [rdi]
	mov rdx, 1
	call ft_list_sort_acc
	cmp rax, 1
	je end
	pop rsi
	pop rdi
	call ft_list_sort
end:
	leave
	ret

