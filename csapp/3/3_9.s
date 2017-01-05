	.file	"3_9.c"
	.text
	.globl	arith
	.type	arith, @function
arith:
.LFB0:
	.cfi_startproc
	movl	8(%esp), %eax
	xorl	4(%esp), %eax
	sarl	$3, %eax
	notl	%eax
	subl	12(%esp), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	arith, .-arith
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
