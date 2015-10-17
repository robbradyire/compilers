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
	push	{r4, r5, r6, r7}
	movw	r6, #:lower16:.LANCHOR0
	movt	r6, #:upper16:.LANCHOR0
	sub	sp, sp, #24
	movs	r5, #0
	adds	r5, r5, #1
	ldmia	r6!, {r0, r1, r2, r3}
	add	r7, sp, #4
	cmp	r5, #5
	add	r4, sp, #8
	ldr	r6, [r6]
	stmia	r7!, {r0, r1, r2, r3}
	str	r6, [r7]
	beq	.L2
.L11:
	add	r0, sp, #24
	mov	r3, r4
.L6:
	ldr	r1, [r3], #4
	ldr	r2, [r4, #-4]
	cmp	r1, r2
	itt	lt
	strlt	r1, [r4, #-4]
	strlt	r2, [r3, #-4]
	cmp	r3, r0
	bne	.L6
	adds	r5, r5, #1
	adds	r4, r4, #4
	cmp	r5, #5
	bne	.L11
.L2:
	ldr	r0, [sp, #4]
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7}
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
