	%define MAC_SYSCALL(nbr) 0x2000000 | nbr
	%define READ 3

	section	.text
	global	_ft_read
	extern	___error

; rdi = int fd
; rsi = void *buf
; rdx = size_t nbyte
_ft_read:	
	mov		rax, MAC_SYSCALL(READ)	; rax = 0x2000003
	syscall							; ret = ft_read(fd, buf, nbyte)
	jc		.manage_err				; jc: error flag
.return:
	ret

.manage_err:
	push	rax						; save prev_rax
	call	___error				
	pop		qword[rax]				; [rax] = prev_rax
	mov		rax, -1					; rax = -1
	jmp		.return
