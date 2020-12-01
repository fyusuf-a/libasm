			global ft_strdup
			extern malloc
			extern ft_strlen

			section .text
ft_strdup:  						; char *strdup(const char* str)
			push rbp 				; new stack frame
			mov rbp, rsp
			push rdi 				; saving the source string on the stack
			call ft_strlen			; rax = ft_strlen(str) (str being in rdi)
			inc rax 				; to include the null character in the result 
			push rax 				; saving the source's size on the stack
			mov rdi, rax 			; rdi = ft_strlen(str) + 1
			call malloc 			; rax = malloc(rdi)
			pop rcx  	 			; rcx = ft_strlen(str) + 1: will be used for rep movs
			mov rdi, rax 			; rdi is now the destination string
			pop rsi 				; rsi is now the source string
			cld 					; clearing the directional flag
			rep movsb 				; copying source string into destination string
			leave
			ret
