!******************************************************
!           File: p2new.m
!	    Date: September 30, 2016
!	    Author: Bryce Andress
!	    Computer Harry
!           Purpose: Get the first digit and length 
!           of number from user and create a number
!           that is that long and has all sequential
!	    digits.
!*****************************************************









	.data
	.align 4
promptNumber:
	.asciz	"Give the first digit: "
promptLength:
	.asciz 	"How many digits in the number? "
errorMsg:
	.asciz	"Error: Bad starting digit"
finalMsg:
	.asciz  "The number, with %d digits, starting from %d is %d"
	.align 4
inFormat:
	.asciz  "%d"
	.align 4
start:
	.word 0
digits:
	.word 0

	.global main
main:
	save %sp, -96, %sp
	
	! Prompt user for number
	set	promptNumber, %o0
	call	printf, 0
	nop

	! Get number
	set	inFormat, %o0
	set	start, %o1
	call	scanf, 0
	nop

	ba	done	
done:
	call 	exit,0
	mov	0, %o0
