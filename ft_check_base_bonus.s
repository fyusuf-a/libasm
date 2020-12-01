	global ft_check_base ; int ft_check_base(char *base) // checks for duplicates, bad characters and if base has at least 2 elements, returns 0 or 1
	extern ft_elem

ft_check_base:
	push rbp
	mov rbp, rsp
	cmp byte [rdi], 0 				; if(!base[0]) 
	je ret_false 					; 	return (0);
	cmp byte [rdi + 1], 0 			; if(!base[1])
	je ret_false 					; 	return (0);
	mov r8, 0 						; i = 0;
loop1:
	cmp byte [rdi + r8], 0 			; if (!base[i])
	je ret_true 					; 	return (1);
	lea r9, [r8 + 1] 				; j = i + 1
loop2:
	cmp byte [rdi + r9], 0 			; if (!base[j])
	je end_loop2 					; 	break;
	mov r10b, byte [rdi + r9] 		; if (base[i] == base[j])
	cmp byte [rdi + r8], r10b 		;
	je ret_false 					; 	return (0);
	inc r9 							; j++;
	jmp loop2 						; goto loop2
end_loop2:
	push rdi 						; saving rdi, using the red zone
	mov dil, byte [rdi + r8] 		; rdi = base[i]
	mov rsi, symbols 		 		; rsi = " \f\n\r\t\v+-"
	call ft_elem 						; if (elem(rdi, rsi)
	cmp rax, 1 						; 	return (0);
	je ret_false
	pop rdi
	cmp byte [rdi + r8], ' ' 		; if (base[i] < ' ')
	jb ret_false 					; 	return(0);
	cmp byte [rdi + r8], '~' 		; if ('~' < base[i])
	ja ret_false 					; 	return(0);
	inc r8 							; i++;
	jmp loop1 						; goto loop1;
ret_true:
	mov rax, 1
	leave
	ret
ret_false:
	mov rax, 0
	leave
	ret

	section .data
symbols:
	db 		' ', '+', '-', 9, 10, 11, 12, 13, 0 ; " +-\t\n\v\f\r"
;spaces-len: equ 	$-spaces
