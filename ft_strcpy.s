		global ft_strcpy
		section .text
ft_strcpy:						; char *ft_strcpy(char *dest, const char *src);
		mov rax, rdi			; return dest;
loop:
		cmp byte [rsi], 0		; if (src = 0) goto end;
		je end
		mov rcx, [rsi]			; char c = *src;
		mov [rdi], rcx			; *dest = c;
		inc rdi					; dest++;
		inc rsi					; src++;
		jmp loop				; goto loop;
end:
		mov byte [rdi], 0		; *dest = '\0';
		ret
