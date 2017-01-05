	.file	"3_12.c"
	.text
	.globl	store_prod
	.type	store_prod, @function
store_prod:
.LFB0:
	.cfi_startproc
	movl	8(%esp), %eax
	movl	%eax, %ecx
	imull	16(%esp), %ecx
	mull	12(%esp)
	addl	%ecx, %edx
	movl	4(%esp), %ecx
	movl	%eax, (%ecx)
	movl	%edx, 4(%ecx)
	ret
	.cfi_endproc
.LFE0:
	.size	store_prod, .-store_prod
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
