			global ft_read
			extern __errno_location ; ___error variant for Linux

			section .text
ft_read: 						    ; ssize_t	ft_read(int fd, void *s, size_t n);
			mov rax, 0  			; syscall code for read 
			syscall					; rax = read(rdi, rsi, rdx)
			cmp rax, 0				; if (rax < 0) goto errno
			jl errno
			ret

errno:
			neg	 rax				; negate value of error stored in rax
			mov rbx, rax			; save value of error in rbx
			call __errno_location	; rax = &errno
			mov dword [rax], ebx	; errno is a 4-byte int
			mov rax, -1
			ret
