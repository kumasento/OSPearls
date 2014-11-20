	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	callq	_puts
	movl	$0, %ecx
	leaq	_main.illegalOpcode(%rip), %rsi
	movq	%rsi, -24(%rbp)
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movl	%ecx, -32(%rbp)         ## 4-byte Spill
	callq	*-24(%rbp)
	movl	-32(%rbp), %eax         ## 4-byte Reload
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Undefined Instructions ..."

	.section	__DATA,__data
	.align	3                       ## @main.illegalOpcode
_main.illegalOpcode:
	.quad	4                  ## 0x40000


.subsections_via_symbols
