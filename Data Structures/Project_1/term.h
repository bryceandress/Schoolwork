/***************************************************************
Author:         Dr. Spiegel
Modifer:        Bryce Andress
Filename:       Term.cpp
Purpose:        A Term holds a single Term of a Polynomial. Capabilities:
		- Evaluate itself
		- Multiply coefficient by a scalar
		- Increment coefficient by a scalar
		- Compare in several ways
		- set and get (of course)
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "term.h"

using namespace std;

Term::Term(double coeff, int expn)
{
	coefficient=coeff; //sets the coefficient
	exponent=expn; //sets the exponent
}

//Gets
double Term::getCoefficient() const //returns the coefficient
{	/*********************************************************************
	*   Function name:  getCoefficient
	*   Description:   retrieves the coefficient
	*   Parameters:  n/a
	*
	*   Return Value: double- the coefficient at the index
	*********************************************************************/
	return(coefficient); //return  the coefficient
}

int Term::getExponent() const //returns the exponent
{	/*********************************************************************
	*   Function name:  getExponent
	*   Description:   retrieves the exponent
	*   Parameters:  n/a
	*
	*   Return Value: int- the exponent at the index
	*********************************************************************/
	return(exponent); //return  the exponent
}

//Other
double Term::operator()(double x) //evaluates the term with x
{	/*********************************************************************
	*   Function name:  operator()
	*   Description:   Evaluates the term by the input number
	*   Parameters:  double x- the number to evaluate to
	*
	*   Return Value: the sum of the evaluated term
	*********************************************************************/
	return(getCoefficient() * (pow(x, getExponent()))); //returns the evaluation
}

bool Term::operator==(int value) //compares exponents
{	/*********************************************************************
	*   Function name:  operator==
	*   Description:  Compares an int against the exponent
	*   Parameters: int value- the number to compare the exponent by
	*
	*   Return Value: true- if match // false- if doesn't match
	*********************************************************************/
	return(value == getExponent());
}

bool Term::operator==(const Term right)  //compares exponents
{	/*********************************************************************
	*   Function name:  operator==
	*   Description:  Compares an int against the exponent
	*   Parameters: int value- the number to compare the exponent by
	*
	*   Return Value: true- if match // false- if doesn't match
	*********************************************************************/
	return(getExponent()==right.getExponent());
}
//I believe this is the devious shortcut you mentioned but it works!
bool Term::operator< (Term right) const//checks if the incoming value is greater than the exponent
{	/*********************************************************************
	*   Function name:  operator<
	*   Description:  Compares two Terms based on exponent
	*   Parameters: int value- the value to make the comparision to
	*
	*   Return Value: according to the comparison
	*********************************************************************/
	return(getExponent() >  right.getExponent());
}
bool Term::operator< (int right) const//checks if the incoming value is greater than the exponent
{	/*********************************************************************
	*   Function name:  operator<
	*   Description:  Compares Term's exponent to an int
	*   Parameters: int value- the value to make the comparision to
	*
	*   Return Value: according to the comparison
	*********************************************************************/
	return(getExponent() < right);
}


ostream &operator<<(ostream &output,const Term &term)
{	/*********************************************************************
	*   Function name:  operator<<
	*   Description:  For output
	*   Parameters: ofstream &ouput-
	*						const Term &t- the term object to be outputted
	*
	*   Return Value: output
	*********************************************************************/
	if (term.getCoefficient()!=1)
		output << term.getCoefficient();
	if (term.getExponent() ==1)//if it needs an x^ or x
		output << "x"; // x alone if to the one power
	else if (term.getExponent() > 1)
		output << "x^" << term.getExponent();
	return (output); //returns the results //enables cascading
}
