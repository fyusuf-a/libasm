		global ft_strcmp
		section .text
ft_strcmp:						; int ft_strcmp(const char *s1, const char *s2);
		xor rax, rax			; to have higher-order bits to 0
loop:
		mov al, byte [rdi]		; rax = *s1;
		cmp al, 0
		je end					; if (!rax) goto end;
		cmp al, byte [rsi]		; if (rax != *s2)
		jne end					;	goto end;
		inc rdi					; s1++;
		inc rsi					; s2++;
		jmp loop				; goto loop;
end:
		xor rcx, rcx			; to have higher-order bits to 0
		mov cl, byte [rsi]		; sub is acts by default on 32 bits so doing sub al, byte [rsi] is not an option
		sub eax, ecx			; rax -= *s2;
		ret						; return (rax);
