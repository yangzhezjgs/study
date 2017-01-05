	.file	"3_16.c"
	.text
	.globl	cond
	.type	cond, @function
cond:
.LFB0:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	8(%esp), %eax
	testl	%eax, %eax
	je	.L1
	testl	%edx, %edx
	jle	.L1
	addl	%edx, (%eax)
.L1:
	rep ret
	.cfi_endproc
.LFE0:
	.size	cond, .-cond
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
