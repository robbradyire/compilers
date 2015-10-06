; sorter.c compiled with no optimisation

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
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"sorter.c"
	.section	.rodata
	.align	2
.LC0:
	.word	1
	.word	4
	.word	3
	.word	6
	.word	2
	.text
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5, r7}
	sub	sp, sp, #36                 ; move stack pointer forward 9 words
	add	r7, sp, #0                  ; r7 = frame pointer
	movw	r3, #:lower16:.LC0      ; r3 = array address
	movt	r3, #:upper16:.LC0
	add	r4, r7, #12                 ; r4 = frame pointer back 3 words
	mov	r5, r3                      ; r5 = array address
	ldmia	r5!, {r0, r1, r2, r3}   ; load first 4 array elements into r0-r3 and update pointer
	stmia	r4!, {r0, r1, r2, r3}   ; store first 4 elements on stack and increase pointer with them
	ldr	r3, [r5]                    ; r3 = 5th element
	str	r3, [r4]                    ; put 5th element on the stack
	movs	r3, #0                  ; r3 = 0 (counter i)
	str	r3, [r7]                    ; push i onto the stack
	b	.L2                         ; branch to L2
.L6:
	ldr	r3, [r7]                    ; load i
	adds	r3, r3, #1              ; i++
	str	r3, [r7, #4]                ; store i on stack
	b	.L3                         ; branch to L3
.L5:
	ldr	r3, [r7, #4]
	lsls	r3, r3, #2
	add	r1, r7, #32
	add	r3, r3, r1
	ldr	r2, [r3, #-20]
	ldr	r3, [r7]
	lsls	r3, r3, #2
	add	r1, r7, #32
	add	r3, r3, r1
	ldr	r3, [r3, #-20]
	cmp	r2, r3
	bge	.L4
	ldr	r3, [r7]
	lsls	r3, r3, #2
	add	r2, r7, #32
	add	r3, r3, r2
	ldr	r3, [r3, #-20]
	str	r3, [r7, #8]
	ldr	r3, [r7, #4]
	lsls	r3, r3, #2
	add	r1, r7, #32
	add	r3, r3, r1
	ldr	r2, [r3, #-20]
	ldr	r3, [r7]
	lsls	r3, r3, #2
	add	r1, r7, #32
	add	r3, r3, r1
	str	r2, [r3, #-20]
	ldr	r3, [r7, #4]
	lsls	r3, r3, #2
	add	r2, r7, #32
	add	r3, r3, r2
	ldr	r2, [r7, #8]
	str	r2, [r3, #-20]
.L4:
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L3:
	ldr	r3, [r7, #4]
	cmp	r3, #4
	ble	.L5
	ldr	r3, [r7]
	adds	r3, r3, #1
	str	r3, [r7]
.L2:
	ldr	r3, [r7]            ; load i
	cmp	r3, #4              ; if (i < 5) {branch to L6}
	ble	.L6                 ; else {
	ldr	r3, [r7, #12]       ;   get first element of array
	mov	r0, r3              ;   move to r0
	adds	r7, r7, #36     ;   restore sp
	mov	sp, r7
	@ sp needed
	pop	{r4, r5, r7}        ;   pop off stack
	bx	lr                  ;   return
	.size	main, .-main    ; }
	.ident	"GCC: (Ubuntu/Linaro 4.8.2-16ubuntu4) 4.8.2"
	.section	.note.GNU-stack,"",%progbits
