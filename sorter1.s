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
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"sorter.c"
	.text
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5, r6}
	sub	sp, sp, #28
	add	r5, sp, #4
	movw	r4, #:lower16:.LANCHOR0
	movt	r4, #:upper16:.LANCHOR0
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	ldr	r3, [r4]
	str	r3, [r5]
	movs	r0, #0
	movs	r5, #1
	mov	r3, r5
	b	.L2
.L7:
	adds	r3, r5, #1
	cmp	r3, #4
	bgt	.L3
	mov	r0, r5
	mov	r5, r3
.L2:
	add	r1, sp, #24
	add	r2, r1, r3, lsl #2
	ldr	r1, [r2, #-20]
	add	r4, sp, #24
	add	r2, r4, r0, lsl #2
	ldr	r2, [r2, #-20]
	cmp	r1, r2
	itttt	lt
	addlt	r4, r4, r0, lsl #2
	strlt	r1, [r4, #-20]
	addlt	r6, sp, #24
	addlt	r1, r6, r3, lsl #2
	it	lt
	strlt	r2, [r1, #-20]
	adds	r3, r3, #1
	cmp	r3, #4
	ble	.L2
	b	.L7
.L3:
	ldr	r0, [sp, #4]
	add	sp, sp, #28
	@ sp needed
	pop	{r4, r5, r6}
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
