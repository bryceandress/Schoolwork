/******************************************************************
* File: p4.m
* Dir: CS235/Project_4
* Date: 12/3/16
* Author: Bryce Andress
* Purpose: Read upto 5 variant records of employees. Allow users to
* search employess, print information about the employees, or add 
* employees..
******************************************************************/

! MACROS
	define(employeeAdrs, %l0)
	define(eltOffset, %l3)
	define(eltsInArray, %l4)
	define(eltAddres, %l6)
	define(name, 0)
	define(wage, 4)
	define(salary, 4)
	define(hours, 6)
	define(level, 6)
	define(tag, 8)

	.data
	.align 8
	
hello:	.asciz 	"Enter Employees and their info: "	Ctrl-D to Stop\n"
namePrompt:
	.asciz	"Enter Name of Employee >"
	.align 4
wagePrompt:
	.asciz	"Enter Wage >"
salaryPrompt:
	.asciz	"Enter Salary >"
hourPrompt:
	.asciz 	"Enter Hours Worked >"
levelPrompt:
	.asciz	"Enter Employee Level >"
tagPrompt
	.asciz	"Select H for Hourly or S for Salaried >" 
numIn:	.asciz	"%d"
shortIn: 
	.asciz	"%hi"

eatCR:	.asciz 	"%c"
charIn	.asciz	"%c%c"

hourEmployeeOut:
	.asciz	"%3d:	Name: %20s	Wage: %3d	Hours: %3d\n"

salariedEmployeeOut:
	.asciz "%3d:	Name: %20s	Level: %3d	Salary: %3d\n"
	.align 4















		 
