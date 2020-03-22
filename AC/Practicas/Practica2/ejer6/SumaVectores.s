	.file	"SumaVectores.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\302\272 componentes del vector"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Tama\303\261o Vectores:%u (%u B)\n"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC4:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC6:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%u\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L21
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	movl	$33554432, %ebp
	call	strtol@PLT
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rbx
	movl	%eax, %edx
	movl	$4, %ecx
	xorl	%eax, %eax
	movl	$1, %edi
	call	__printf_chk@PLT
	cmpl	$33554432, %ebx
	cmovbe	%ebx, %ebp
	testl	%ebx, %ebx
	je	.L3
	pxor	%xmm1, %xmm1
	leaq	v1(%rip), %r12
	leaq	v2(%rip), %r13
	movsd	.LC2(%rip), %xmm3
	xorl	%eax, %eax
	cvtsi2sd	%ebp, %xmm1
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L4:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	movapd	%xmm1, %xmm7
	cvtsi2sd	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	subsd	%xmm0, %xmm7
	movsd	%xmm2, (%r12,%rax,8)
	movsd	%xmm7, 0(%r13,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %ebp
	ja	.L4
	movq	%rsp, %rsi
	xorl	%edi, %edi
	leaq	v3(%rip), %r14
	call	clock_gettime@PLT
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L5:
	movsd	(%r12,%rax,8), %xmm0
	addsd	0(%r13,%rax,8), %xmm0
	movsd	%xmm0, (%r14,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %ebp
	ja	.L5
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cmpl	$9, %ebx
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	jbe	.L22
	leal	-1(%rbp), %eax
	movsd	(%r14), %xmm3
	movsd	0(%r13), %xmm2
	leaq	.LC4(%rip), %rsi
	movsd	(%r14,%rax,8), %xmm6
	movq	%rax, %rcx
	movsd	0(%r13,%rax,8), %xmm5
	movl	%eax, %r9d
	movsd	(%r12,%rax,8), %xmm4
	movl	%eax, %r8d
	movsd	(%r12), %xmm1
	movl	%ebp, %edx
	movl	$1, %edi
	movl	$7, %eax
	call	__printf_chk@PLT
.L7:
	xorl	%eax, %eax
	movq	40(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L23
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L22:
	.cfi_restore_state
	leaq	.LC6(%rip), %rsi
	leaq	.LC3(%rip), %r15
	movl	%ebp, %edx
	movl	$1, %edi
	movl	$1, %eax
	xorl	%ebx, %ebx
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L8:
	movsd	(%r14,%rbx,8), %xmm2
	movl	%ebx, %r8d
	movsd	0(%r13,%rbx,8), %xmm1
	movl	%ebx, %ecx
	movsd	(%r12,%rbx,8), %xmm0
	movl	%ebx, %edx
	movq	%r15, %rsi
	movl	$1, %edi
	movl	$3, %eax
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpl	%ebx, %ebp
	ja	.L8
	jmp	.L7
.L3:
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	leaq	.LC6(%rip), %rsi
	pxor	%xmm0, %xmm0
	movl	%ebp, %edx
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L7
.L23:
	call	__stack_chk_fail@PLT
.L21:
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	orl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.comm	v3,268435456,32
	.comm	v2,268435456,32
	.comm	v1,268435456,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	2576980378
	.long	1069128089
	.align 8
.LC5:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
