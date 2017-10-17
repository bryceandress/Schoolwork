/********************************************************************
* File: p4.m
* Date: 12/8/16
* Author: Bryce Andress
* Purpose: Read up to 5 variant records of employees.
* Allow users to search employees, and print.
*********************************************************************/

/********************************************************************
* Employee Record
			12 Bytes Long
 - ---------------------------------------------------------
 | name (4) | wage (4) | hours (2)  | tag (1) | wasted (1) |
 - ---------------------------------------------------------
 | name (4) | sala (4) |level(1)|(1)| tag (1) | wasted (1) |
 -----------------------------------------------------------
*/

! 	MACROS
	define(iReg, %l0)
	define(employeeAdrs, %l1)
	define(eltOffset, %l2)
	define(eltsInArray, %l3)
	define(eltAdrs, %l4)
	define(arrayAdrs, %i1)
	define(employeeList, 76)
	define(wage, 4)
	define(salary, 4)
	define(hours, 8)
	define(level, 8)
	define(tag, 10)

	.data
	.align 8

hello:	.asciz	"Enter Employees and their info:	CTRL-D to Stop\n"
	.align 8
namePrompt:
	.asciz	"Enter Name of Employee> "
	.align 4
wagePrompt:
	.asciz	"Enter Wage> "
salaryPrompt:
	.asciz	"Enter Salary> "
hourPrompt:
	.asciz	"Enter Hours worked> "
levelPrompt:
	.asciz	"Enter employee Level> "
tagPrompt:
	.asciz	"Select H for hourly or S for salaried> "
newlinePrompt:
	.asciz	"\n"
searchPrompt:
	.asciz	"Enter Name of employee you would like to search for Ctrl-D ends search> "
numIn:	.asciz	"%d"
stringIn:	
	.asciz	"%s"
shortIn:
	.asciz	"%hi"
eatCR:
	.asciz	"%c"
charIn:	.asciz	"%c%c"
hourEmployeeOut:
	.asciz	"Name: %s	Wage: %d         Hours:	%d\n"
salariedEmployeeOut:
	.asciz	"Name: %s	Level: %c	Salary: %d\n"
fail:
	.asciz	"Employee not found.\n"
temp:
	.word	0
	.align 	8
	.text
	.global main
main:
	save	%sp, (-108 -60) & -8, %sp

	! Print Hello
	sethi	%hi(hello), %o0
	call	printf
	or	%o0, %lo(hello), %o0

	add	%fp, -76, employeeAdrs

	! Start reading in employees
	call	readEmployees
	mov	employeeAdrs, %o1				! Pass employeeAdrs

	! Make sure it is not clobbered
	mov	%o0, eltsInArray	

	! Format purpose just a new line
	set	newlinePrompt, %o0
	call	printf	
	nop

	! Set up the printing of all employees
	add	%fp, -76, employeeAdrs
	mov	eltsInArray, %o0				! Pass # of records and employeeAdrs
	call	printEmployees
	mov	employeeAdrs, %o1

	! Search for an employee
	call	searchEmployee
	mov	eltsInArray, %o0				! Pass employeeAdrs

	call	done
	nop

printEmployees:
	save	%sp, (-108) & -8, %sp
	mov	0, iReg 
	mov	%i1, employeeAdrs				! Move the passed in variable to a more secure local register
	mov	%i0, eltsInArray 				! Same as above but for eltsInarray

printinc:
	call	printEmployee	
	mov	employeeAdrs, %o1 				! call printEmployee and pass it employeeAdrs
	
	inc 	iReg

	! Advance to next variant record
	add	employeeAdrs, 12, employeeAdrs

	cmp	iReg, eltsInArray				! Make sure we stil have elements to print
	bl	printinc	
	nop 

	ret
	restore

printEmployee:
	save	%sp, (-108) & -8, %sp
	mov	%i1, employeeAdrs				! Put the passed in parameter in a local register
	ldub	[employeeAdrs+tag], %l2				! Load the tag from memory

	cmp	%l2, 0x48					! Compare it to a S
	be	printHour					! If it is not a S go to printHour
	nop

printSalary:
								! Print Salaried
								! Load data from memory
	set	salariedEmployeeOut, %o0
	ld	[employeeAdrs], %o1
	ldsb	[employeeAdrs+level], %o2
	ld	[employeeAdrs+salary], %o3	

	call	printf
	nop

	ret
	restore

printHour:
								! Print Hour
								! Load from memory
	set	hourEmployeeOut, %o0
	ld	[employeeAdrs], %o1
	ld	[employeeAdrs+wage], %o2
	lduh	[employeeAdrs+hours], %o3

	call	printf
	nop

	ret
	restore

readEmployees:
	save	%sp, (-108) & -8, %sp
	mov	0, eltsInArray				! Make sure we start at the beginning of allocated memory
loop:
	! Get the employees and increment the array
	mov	eltsInArray, %o0
	call	readEmployee
	mov	arrayAdrs, %o1				! Pass the currently address of the array to readEmployee

	! Check to see if ctrl-d was entered

	cmp	%o0, -1
	be	stopemployees
	nop

	! Move to next employee location in array
	add	arrayAdrs, 12, arrayAdrs 		! Go to next record in the array where we want to store an employee

	! Increment
	inc	eltsInArray				! Make sure we make note that an employee was added

	! Eat \n
	set	eatCR, %o0			
	call	scanf
	mov	arrayAdrs, %o1

	! Read in up to 5 employees
	cmp	eltsInArray, 5 				! Only read 5 employees
	bl	loop
	nop

	mov	eltsInArray, %i0			! Return the number of elts we added

stopemployees:
	mov	-1, %o0					! Pass a -1 back because of ctrl-d
	mov	eltsInArray, %i0
	ret
	restore

readEmployee:
	save	%sp, (-108) & -8, %sp
	mov	%i0, eltsInArray

	! Get Name	
	mov	eltsInArray, %o0
	call	readName				! Call the readName function, pass the arrayAdrs
	mov	arrayAdrs, %o1

	! Check to see if ctrl-d was entered

	cmp	%o0, -1					! Check to see if ctrl-d was entered
	be	stopemployee
	nop

	! Get Tag
	call	readTag
	mov	arrayAdrs, %o1				! Get the tag and pass the address

	! Make sure it is stored in uppercase
	ldub	[arrayAdrs+tag], %l2			! Convert the entered to tag to upper. If it is entered as upper do nothing
	call	toupper
	mov	%l2, %o0

	mov	%o0, %l2				! Make sure it does not get clobbered

	! user inputted the letter s
	cmp	%l2, 0x53				! Check to see if user entered S
	be	salaried				! If so branch to salaried
	nop

	! user inputted the letter h
	cmp	%l2, 0x48				! Check to see if user entered h
	be	hour					! If so branch to hour
	nop

	call	done					! If the user does not enter either exit
	nop

stopemployee:
	mov	-1, %i0

	ret
	restore

hour:
	! Get hours
	call	readHours				! Call readHours pass arrayAdrs 
	mov	arrayAdrs, %o1

	! Get wage
	call	readWage				! Call readWage pass arrayAdrs
	mov	arrayAdrs, %o1
	
	ret
	restore	

salaried:
							! Get level
	call	readLevel
	mov	arrayAdrs, %o1

							! Get tag
	call	readSalary
	mov	arrayAdrs, %o1

	ret
	restore

readTag:
	save	%sp, (-108) & -8, %sp
	set	tagPrompt, %o0
	call	printf
	nop

							! Put tag in array + 12	
	set	charIn, %o0				! Tell scanf what we want 
	add	arrayAdrs, tag, %o1			! Put whatever is read in directly into arrayAdrs+tag which is baseEltAddress+10
	call	scanf
	add	arrayAdrs, 11, %o2			! Scrap the  \n
	
	ret
	restore

readName:
	save	%sp, (-108) & -8, %sp

	mov	%i0, eltsInArray			! Keep track of eltsInArray

	sethi	%hi(namePrompt), %o0
	call	printf
	or	%o0, %lo(namePrompt), %o0

							! Generate space on heap for 20 char name
	call	malloc
	mov	20, %o0

							! Put address into arrayAdrs+name
	st	%o0, [arrayAdrs]
	call	gets
	nop

							! Make sure user did not enter 0
	cmp	%o0, 0
	be	ctrld	
	nop

	ret
	restore

ctrld:
	mov	-1, %i0					! Account for a -1
	
	ret	
	restore

readWage:
	save	%sp, (-108) & -8, %sp

	set	wagePrompt, %o0
	call	printf
	nop
							! Store wage in array+8

	set	numIn, %o0			
	add	arrayAdrs, wage, %o1			
	call	scanf
	nop

	ret
	restore

readHours:
	save	%sp, (-108) & -8, %sp

	set	hourPrompt, %o0
	call	printf
	nop
							! Store hours in array+4
	set	shortIn, %o0
	add	arrayAdrs, hours, %o1
	call	scanf
	nop

	ret
	restore

readLevel:
	save	%sp, (-108) & -8, %sp

	set	levelPrompt, %o0
	call	printf
	nop
							! Store level in array+8
	set	charIn, %o0
	add	arrayAdrs, level, %o1
	call	scanf
	add	arrayAdrs, 11, %o2

	ret
	restore

readSalary:
	save	%sp, (-108) & -8, %sp

	set	salaryPrompt, %o0
	call	printf
	nop

							! Store salary in array+8
	set	numIn, %o0
	add	arrayAdrs, salary, %o1
	call	scanf
	add	arrayAdrs, 11, %o2

	ret
	restore

searchEmployee:
	save	%sp, (-108) & -8, %sp
	mov	%i1, eltsInArray			! Move param to a more secure location

searchLoop:
	set	searchPrompt, %o0
	call	printf
	nop
							! Put the address of the name we are looking for in %l6
	call	malloc
	mov	20, %o0

	mov	%o0, %l6

	set	stringIn, %o0				! Get name from employee
	call	scanf
	mov	%l6, %o1

	mov	%o0, %l6				! Move to local reg

	cmp	%l6, 0
	be	out	
	nop
							! Get the employeeAdrs this also could have been passed in
	add	%fp, employeeList, employeeAdrs
	mov	0, iReg


idxLoop:
	! Compare %l6 and teh names in our array
	ld	[employeeAdrs], %o0
	call	strcmp
	mov	%l6, %o1

	cmp	%o0, 0					! If equal branch to found
	be	found
	nop
							! If not found inc iReg and keep going until all recs are checked
	inc	iReg
	cmp	iReg, eltsInArray
	bl	idxLoop
	add	employeeAdrs, 12, employeeAdrs		! Go to next employee
	
	set	fail, %o0				! Once all are check print out employee not found msg
	call	printf
	nop

	ret
	restore

found:
	call	printEmployee
	mov	employeeAdrs, %o1
	nop

out:
	ret
	restore
done:
	call	exit
	mov	0, %o0
