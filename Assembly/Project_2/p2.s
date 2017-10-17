!********************************************************************************
!                   File: p2.m
!		    Date: September 30, 2016
! 		    Author: Bryce Andress
! 		    Computer: Harry
!		    Purpose: Get a first digit from the user, and then calculate
!		    a number with all the numbers after 1 greater.
!********************************************************************************









	.data
	.align 4
promptNumber:
	.asciz 	"Give the first digit: "
promptLength:
	.asciz  "How many digits in the number? "
errorMsg:
	.asciz  "Error: Bad Starting digit \n"
finalMsg:
	.asciz  "The number, with %d digits, starting from %d is %d \n"
	.align 	4
informat:
	.asciz  "%d"
	.align 4
number:	
	.word 0
length:
	.word 0

	.global main
main:
	save 	%sp, -96, %sp

	! Prompt user for number
	set	promptNumber, %o0
	call	printf, 0
	nop 	! No pipelining

	! Get number
	set	informat, %o0
	set	number, %o1
	call	scanf, 0 
	nop 	! No pipelining
	
	! Load number into %l0 and %l6
	set	number, %l1
	ld	[%l1], %l0

	! Make sure the number is greater than 0
	cmp	%l0, 0
	bg	check10
	nop	! No pipelining
	
	! If it is not print the error message and exit	
	set	errorMsg, %o0
	call	printf, 0
	nop     ! No pipelining
	
	ba	done	
	nop	! No Pipelining

check10:
	! Check to see if the number is less than 10
	cmp	%l0, 10
	bl	loopSetup	
	nop	! No pipelining
	
	! If it is not print error msg	
	set	errorMsg, %o0
	call	printf, 0
	nop	! No pipelining

	ba	done	
	nop	! No pipelining

loopSetup:
	! Prompt user for number of digits 
	set	promptLength, %o0
	call	printf, 0
	nop	! No pipelining
	
	! Get number from user	
	set	informat, %o0
	set	length,	%o1
	call	scanf, 0
	nop	! No pipelining

	! Load length into registers	
	set	length, %l3
	ld	[%l3], %l2
	
	! %l6 = %l0; number=start
	mov	%l0, %l6
	mov	%l0, %l5
 
	! start = (start+1)%10		
	add	%l0, 1, %l0
	mov	%l0, %o0
	call	.rem
	mov	10, %o1 ! Fill pipeline
	
	mov	%o0, %l0
	
	! Initialize the iterator
	mov	1, %l4
loop:
	add	%l4, 1, %l4
	! number = (number * 10) + start
	mov	%l5, %o0
	call	.mul
	! Fill pipline	
	mov	10, %o1
	mov	%o0, %l5 
	add	%l5, %l0, %l5

	! start = (start+1)%10
	add	%l0, 1, %l0
	mov	%l0, %o0
	call	.rem
	mov	10, %o1 ! Fill pipeline

	mov	%o0, %l0

	! Check to see if for loop should continue
	cmp	%l4, %l2
	bne	loop
	nop	! No pipeline fill

print:
	set	finalMsg, %o0
	mov	%l2, %o1
	mov	%l6, %o2
	call	printf, 0
	mov	%l5, %o3 ! Fill Pipeline
	nop	

done:
	call	exit, 0
	mov	0, %o0	
