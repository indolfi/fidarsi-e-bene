	.intel_syntax noprefix
calcola_media:
	test	esi, esi
	jle	.L7
	movsx	rsi, esi
	xor	eax, eax
	pxor	xmm0, xmm0
	lea	rdx, [rdi+rsi*4]
.L5:
	movss	xmm1, DWORD PTR [rdi]
	ucomiss	xmm1, DWORD PTR .LC1[rip]
	jp	.L8
	je	.L3
.L8:
	addss	xmm0, xmm1
	add	eax, 1
.L3:
	add	rdi, 4
	cmp	rdi, rdx
	jne	.L5
	test	eax, eax
	je	.L7
	pxor	xmm1, xmm1
	cvtsi2ss	xmm1, eax
	divss	xmm0, xmm1
	ret
.L7:
	movss	xmm0, DWORD PTR .LC1[rip]
	ret
	.align 4
.LC1:
	.long	-998653952
