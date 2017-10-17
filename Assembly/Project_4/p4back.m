/*******************************************************
* File: p4.m
* Date: 12/3/16
* Author: Bryce Andress
* Purpose: Read up to 5 variant records of employees. 
* Allow users to search employees, print
*******************************************************/

!	MACROS
	define(iReg, %l0)
	define(employeeAdrs, %l2)
	define(eltOffset, %l3)
	define(eltsInArray, %l4)
	define(eltAdrs, %l5)
	define(arrayAdrs, %i1)
	define(employeeList, 76) !%sp + 76 Puts you at the offset of the first variant record
	define(name, 0)
	define(wage, 4)
	define(salary, 4)
	define(hours, 8)
	define(level, 8)
	define(tag, 12)
	define(dummy, 12)

	.data
	.align 8

hello:	.asciz	"Enter Employees and their info:	Ctrl-D to Stop\n"
	.align 8
namePrompt:
	.asciz	"Enter Name of Employee >"
	.align 4
wagePrompt:
	.asciz	"Enter Wage >"
salaryPrompt:
	.asciz	"Enter Salary >"
hourPrompt:
	.asciz 	"Enter Hours worked >"
levelPrompt:
	.asciz	"Enter employee Level >"
tagPrompt:
	.asciz	"Select H for hourly or S for salaried >"
searchPrompt:
	.asciz	"Enter Name of employee you would like to search for >"
numIn:	.asciz	"%d"
shortIn:
	.asciz	"%hi"
eatCR:
	.asciz "%c"
charIn:	.asciz "%c%c"
hourEmployeeOut:
	.asciz "Name: %s	Wage: %3d	Hours: %3d\n"
testPrint:
	.asciz	"Name: %s \n"
salariedEmployeeOut:
	.asciz "Name: %s	Level %3d	Salary: %3d\n"
	.align 4
fail:
	.asciz	"Employee not found. "
temp:
	.word 	0
	.align	8
	.text
	.global main

main:
	save	%sp, (-108 -60) & -8, %sp

	! Print Hello
	sethi	%hi(hello), %o0
	call	printf, 0
	or	%o0, %lo(hello), %o0

	! Start reading in employees
	call	readEmployees
	nop

	! Print all the employees
	! call	printEmployee
	! nop	

	! Search for an employee
	call	searchEmployee
	nop
	
	! Exit	
	call	done
	nop

readEmployees:
	save	%sp, (-108) & -8, %sp

	! Set up loop
	mov	0, iReg
	mov	0,eltsInArray
	add	%fp, employeeList, employeeAdrs
loop:
	! Get the employees and increment the array
	call	readEmployee
	mov	employeeAdrs, %o1
	
	add	employeeAdrs, 12,  employeeAdrs

	inc	iReg
	inc	eltsInArray

	! Read in up to 5 employees
	! THIS NEEDS TO BE CHANGED TO 5
	cmp	iReg, 2
	bl	loop

	ret
	restore

readEmployee:
	! Get a single employee
	save	%sp, (-108) & -8, %sp

	! Get the employee name	pass the location of what record in the array we are in
	call	readName
	mov	arrayAdrs, %o1

	! Get the tag
	call	readTag
	mov	arrayAdrs, %o1 

	 ! Make sure it is stored in upper case
	 add	employeeAdrs, tag, %l2
	 call	toupper
	 mov	%l2, %o0
	
	mov	%o0, employeeAdrs

	! user inputted S?	
	 cmp	employeeAdrs, 0x53
	 be	salaried
	 nop

	! user inputted H?
	! cmp	employeeAdrs, 0x48
	! be	hour
	! nop

	! If user did not input a H or S  exit
	 call	done
	 nop

hour:	
	! If employee is hourly get hours worked
	! call	readHour
	! mov	arrayAdrs, %o1

	! Get the employees wage
	! call	readWage
	! mov	arrayAdrs, %o1
	
	! ret
	! restore

salaried:
	! If employee is salaried get level
	call	readLevel
	mov	arrayAdrs, %o1

	! Also get salary
	call	readSalary
	mov	arrayAdrs, %o1

	ret
	restore

readName:
	! Read the employees name
	save	%sp, (-108 -6) & -8, %sp

	sethi	%hi(namePrompt), %o0
	call	printf, 0
	or	%o0, %lo(namePrompt), %o0

	! Get space on the heap put that address in [arrayAdrs+name]
	call	malloc
	mov	20, %o0

	st	%o0, [arrayAdrs] 
	call	gets
	nop

	! Check to see if user entered CTRL-D
	cmp	%o0, 0
	be	done
	nop

	ret
	restore

readTag:
	save	%sp, (108 -6) & -8, %sp 

	! Get info regarding salaried or hourly
	set	tagPrompt, %o0
	call	printf
	nop

	call	getchar	
	nop

	! Put it in arrayAdrs+tag	
	add	arrayAdrs, tag, arrayAdrs 
	st	%o0, [arrayAdrs] 

	call	getchar
	nop

	ret
	restore

readLevel:
	save	%sp, (108 -6) & -8, %sp

	! Get info on employees level
	set	levelPrompt, %o0
	call	printf
	nop

	call	getchar
	nop

	! Put it in arrayAdrs+level
	add	arrayAdrs, level, arrayAdrs 
	mov	%o0, arrayAdrs 

	ret
	restore

readSalary:
	save	%sp, (108 -6) & -8, %sp

	! Get an employees salary
	set	salaryPrompt, %o0
	call	printf
	nop

	! Put it in arrayAdrs + salary
	set	numIn, %o0
	call	scanf
	add	arrayAdrs, salary, arrayAdrs 

	ret
	restore

readWage:
	save	%sp, (-108 -6) & -8, %sp

	! Get the employees wage
	! set	eatCR, %o0
	! call	scanf
	! add	arrayAdrs, dummy, arrayAdrs 

	sethi	%hi(wagePrompt), %o0
	call	printf, 0
	or	%o0, %lo(wagePrompt), %o0

	! Put it in arrayAdrs + wage
	set	numIn, %o0
	call	scanf
	add	arrayAdrs, wage, arrayAdrs 

	! set	eatCR, %o0
	! call	scanf
	! add	arrayAdrs, dummy, arrayAdrs 

	ret
	restore 

readHour:
	save	%sp, (108 -6) & -8, %sp

	! Get the hours worked from employee
	set	hourPrompt, %o0
	call	printf
	nop

	! Put it in arrayAdrs + hours	
	set	shortIn, %o0
	call	scanf
	add	arrayAdrs, hours, arrayAdrs
	ret
	restore

print:
	save	%sp, (108) & -8, %sp

	! Print all the employees
	set	testPrint, %o0
	mov	%i1, %o1
	call	printf	

	ret
	restore

searchEmployee:
	! Search for an employee
	save	%sp, (108 -6) & -8, %sp

	set	searchPrompt, %o0
	call	printf
	nop

	! Put the address of the name we are looking for in %l6
	call	malloc
	mov	20, %o0
	call	gets
	mov	%o0, %l6

	add	%fp, employeeList, employeeAdrs
	mov	0, iReg

idxLoop:
	! Compare %l6 and the names in our Stack
	ld	[employeeAdrs], %o0
	call	strcmp
	mov	%l6,	%o1
	cmp	%o0, 0
	be	found
	nop

	! If not found inc iReg and keep going until all registers are checked
	inc	iReg
	cmp	iReg, eltsInArray
	bl,a	idxLoop
	add	employeeAdrs, 12, employeeAdrs
	set	fail, %o0
	call	printf
	nop

	ret
	restore

found:
	! If an employee is found print him
	! call	printEmployee
	! nop

	ret
	restore

done:
	call	exit, 0
	mov	0, %o0
