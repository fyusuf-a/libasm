		global ft_strlen
		section .text
ft_strlen:
		xor rax, rax			; len = 0;
loop:							; size_t	ft_strlen(const char* s);
		cmp byte [rdi+rax], 0	; if (str[len] == 0) goto end; 
		je end
		inc rax					; len++;
		jmp loop				; goto loop;
end:
		ret						; return(len);
