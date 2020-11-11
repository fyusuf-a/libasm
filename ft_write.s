; https://en.wikipedia.org/wiki/Red_zone_(computing)
			global ft_write			;
			extern __errno_location  ; ___error variant for Linux

			section .text
ft_write:   mov rax, 1
			syscall					; ret_write = write(
			cmp rax, 0				; if 
			jl errno
			ret

errno:
			neg	 rax			; negate value of error stored in rax
			mov rbx, rax		; save value of error in rbx
			call __errno_location
			mov dword [rax], ebx
			mov rax, -1
			ret
