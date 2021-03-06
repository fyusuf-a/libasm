			global ft_write			;
			extern __errno_location ; ___error variant for Linux

			section .text
ft_write:  							; ssize_t write(int fd, const void *buf, size_t count) 
			mov rax, 1				; syscall code for write
			syscall					; rax = write(rdi, rsi, rdx)
			cmp rax, 0				; if(rax < 0) goto errno
			jl errno
			ret

errno:
			neg	 rax				; negate value of error stored in rax
			mov rbx, rax			; save value of error in rbx
			call __errno_location	; rax = &errno
			mov dword [rax], ebx	; errno is a 4-byte int
			mov rax, -1
			ret
