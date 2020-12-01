	global ft_atoi_base
	extern ft_check_base
	extern ft_strlen
	extern ft_elem

	section .text

first_index: 					; int first_index(char c, char *str) // Returns the first index at which c appears in str, or -1 if it is not found // only rax and r8 are modified
	mov r8, 0
loop_first_index:
	cmp byte [rsi + r8], 0
	je not_found
	cmp dil, byte [rsi + r8]
	je found
	inc r8
	jmp loop_first_index
not_found:
	mov rax, -1
	ret
found:
	mov rax, r8
	ret

eat_signs: 					; advances rdi until a normal character is met (no copy is made), returns -1 if the sign is negative, 1 otherwise // only rax and rdi is affected
	mov rax, 1
loop_eat_signs:
	cmp byte [rdi], '-'
	je continue_eat_signs
	cmp byte [rdi], '+'
	je continue_eat_signs
	jmp end_eat_signs
continue_eat_signs:
	cmp byte [rdi], '-'
	je negate
	inc rdi
	jmp loop_eat_signs
negate:
	neg rax
	inc rdi
	jmp loop_eat_signs
end_eat_signs:
	ret


ft_atoi_base: 				; int	ft_atoi_base(char *str, char *base)
	push rbp
	mov rbp, rsp
	push rdi 				; stack + str
	push rsi 				; stack + str + base
	mov rdi, rsi 			; base is the argument to ft_check_base and ft_strlen
	call ft_check_base
	cmp rax, 0
	je return_zero
	mov rdi, qword [rbp - 16] 	; rdi = base
	call ft_strlen 
	push rax 				 ; stack + str + base + strlen(base)
	mov rcx, qword [rbp - 8] ; rcx = str
loop1:
	xor rdi, rdi
	mov dil, byte [rcx]
	mov rsi, spaces
	call ft_elem
	cmp rax, 0
	je continue_1
	inc rcx 				; rcx++
	jmp loop1
continue_1:
	mov rdi, rcx
	call eat_signs
	push rax 				; stack + str + base + strlen(base) + sign
	mov qword [rbp - 8], rdi
	mov r9, 0 				; the return value
loop_2:
	mov rdi, qword [rbp - 8]
	mov dil, byte [rdi]
	mov rsi, qword [rbp - 16]
	call first_index
	cmp rax, -1
	je return_
	imul r9, qword [rbp - 24]
	add r9, rax
	inc qword [rbp - 8]
	jmp loop_2
return_:
	mov rax, r9
	cmp qword [rbp - 32], -1
	je negate_
	leave
	ret
negate_:
	neg rax
	leave
	ret
return_zero:
	mov rax, 0
	leave
	ret

	section .data
spaces:
	db 		' ', 9, 10, 11, 12, 13, 0 ; " +-\t\n\v\f\r"
;spaces-len: equ 	$-spaces

