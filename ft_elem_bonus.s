	global ft_elem 				; rsi is changed, no change to the stack

	section .text
ft_elem:                  		; int elem(char c, char *str) // checks if a character is part of a string // only rax and rsi are modified
	cmp byte [rsi], 0
	je false_elem
	cmp dil, byte [rsi]
	je true_elem
	inc rsi
	jmp ft_elem
false_elem:
	mov rax, 0
	ret
true_elem:
	mov rax, 1
	ret
