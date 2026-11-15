	.intel_syntax noprefix
calcola_media:
	push	rbp
	mov	rbp, rsp
	mov	QWORD PTR -24[rbp], rdi
	mov	DWORD PTR -28[rbp], esi
	pxor	xmm0, xmm0
	movss	DWORD PTR -12[rbp], xmm0
	mov	DWORD PTR -8[rbp], 0
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L5:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	mov	rax, QWORD PTR -24[rbp]
	add	rax, rdx
	movss	xmm0, DWORD PTR [rax]
	ucomiss	xmm0, DWORD PTR .LC1[rip]
	jp	.L8
	ucomiss	xmm0, DWORD PTR .LC1[rip]
	je	.L3
.L8:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	mov	rax, QWORD PTR -24[rbp]
	add	rax, rdx
	movss	xmm0, DWORD PTR [rax]
	movss	xmm1, DWORD PTR -12[rbp]
	addss	xmm0, xmm1
	movss	DWORD PTR -12[rbp], xmm0
	add	DWORD PTR -8[rbp], 1
.L3:
	add	DWORD PTR -4[rbp], 1
.L2:
	mov	eax, DWORD PTR -4[rbp]
	cmp	eax, DWORD PTR -28[rbp]
	jl	.L5
	cmp	DWORD PTR -8[rbp], 0
	jne	.L6
	movss	xmm0, DWORD PTR .LC1[rip]
	jmp	.L7
.L6:
	pxor	xmm1, xmm1
	cvtsi2ss	xmm1, DWORD PTR -8[rbp]
	movss	xmm0, DWORD PTR -12[rbp]
	divss	xmm0, xmm1
.L7:
	pop	rbp
	ret
	.align 4
.LC1:
	.long	-998653952
