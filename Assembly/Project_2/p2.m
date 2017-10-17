!********************************************************************************
!                   File: p2.m
!		    Date: September 30, 2016
! 		    Author: Bryce Andress
! 		    Computer: Harry
!		    Purpose: Get a first digit from the user, and then calculate
!		    a number with all the numbers after 1 greater.
!********************************************************************************

define(startReg, %l0)
define(startAdrsReg, %l1)
define(lengthReg, %l2)
define(lengthAdrsReg, %l3)
define(iteratorReg, %l4)
define(finalNumber, %l5)
define(startNumber, %l6)

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
	
	! Load number into startReg and startNumber
	set	number, startAdrsReg
	ld	[startAdrsReg], startReg

	! Make sure the number is greater than 0
	cmp	startReg, 0
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
	cmp	startReg, 10
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
	set	length, lengthAdrsReg
	ld	[lengthAdrsReg], lengthReg
	
	! startNumber = startReg; number=start
	mov	startReg, startNumber
	mov	startReg, finalNumber
 
	! start = (start+1)%10		
	add	startReg, 1, startReg
	mov	startReg, %o0
	call	.rem
	mov	10, %o1 ! Fill pipeline
	
	mov	%o0, startReg
	
	! Initialize the iterator
	mov	1, iteratorReg
loop:
	add	iteratorReg, 1, iteratorReg
	! number = (number * 10) + start
	mov	finalNumber, %o0
	call	.mul
	! Fill pipline	
	mov	10, %o1
	mov	%o0, finalNumber 
	add	finalNumber, startReg, finalNumber

	! start = (start+1)%10
	add	startReg, 1, startReg
	mov	startReg, %o0
	call	.rem
	mov	10, %o1 ! Fill pipeline

	mov	%o0, startReg

	! Check to see if for loop should continue
	cmp	iteratorReg, lengthReg
	bne	loop
	nop	! No pipeline fill

print:
	set	finalMsg, %o0
	mov	lengthReg, %o1
	mov	startNumber, %o2
	call	printf, 0
	mov	finalNumber, %o3 ! Fill Pipeline
	nop	

done:
	call	exit, 0
	mov	0, %o0	
