	.syntax unified
	.arch armv7-a
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"sorter.c"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5}
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	sub	sp, sp, #24
	add	r5, sp, #4
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	ldr	r2, [sp, #8]
	ldr	r3, [sp, #12]
	cmp	r0, r2
	ldr	r4, [r4]
	it	ge
	movge	r0, r2
	ldr	r2, [sp, #16]
	cmp	r0, r3
	str	r4, [r5]
	it	ge
	movge	r0, r3
	ldr	r3, [sp, #20]
	cmp	r0, r2
	it	ge
	movge	r0, r2
	cmp	r0, r3
	it	ge
	movge	r0, r3
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5}
	bx	lr
	.size	main, .-main
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
.LC0:
	.word	1
	.word	4
	.word	3
	.word	6
	.word	2
	.ident	"GCC: (Ubuntu/Linaro 4.8.2-16ubuntu4) 4.8.2"
	.section	.note.GNU-stack,"",%progbits
