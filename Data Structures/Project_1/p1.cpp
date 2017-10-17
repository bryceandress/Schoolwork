///////////////////////////////////////////////////////
// 										Bryce Andress 								 //
// 								CSC 237 Data Structures 					 //
// 		Read a list of polynomials and output their    //
// 				values from multiple data structures       //
// 								September 29th 2016 							 //
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Current Bugs: When parallel array recursive is not /
// Also sorry some of the comments are malialigned    /
// once again on my laptop it looks great!            /
///////////////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include "term.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*************************************************************************/
/* 																																			 */
/* Function name: duplicate 																						 */
/* Description: Check term vector for dup exponents if they are dups add */
/* 							bases together, delete old term and continue             */
/* Parameters:                                                           */
/* vector<Term> termVec: vector of type term - input/output              */
/* double base: Current base value, used if term is dup - input          */
/* int exponent: Current exponent, used to check if term is dup - input  */
/* Return Value: vector<Term> - A vector of terms                        */
/* 																																			 */
/*************************************************************************/
vector<Term> duplicate(vector<Term> termVec, double base, int exponent)
{
	for(int iter = 0; iter < termVec.size(); iter++)
	{
		//If exponents are the same combine terms
		if(termVec[iter].getExponent() == exponent)
		{
			Term tmpTerm((base + termVec[iter].getCoefficient()), exponent);
			termVec.erase(termVec.begin()+iter);
			termVec.push_back(tmpTerm);
			return termVec;
		}
	}
	//If not create new term
	Term tmpTerm(base, exponent);
	termVec.push_back(tmpTerm);
	return termVec;
}

/*************************************************************************/
/* Function name: duplicate 																						 */
/* Description: Check bases and exponents arrays for dup exponents if    */
/* 							they are dups add 																			 */
/* 							bases together, delete old term and continue             */
/* Parameters:                                            							 */
/* double bases[]: An array of the bases that have been read in - input  */
/* int exponents[]: An array of exponents that have been read in - input */
/* double base: Current base value, used if term is dup - input          */
/* int exponent: Current exponent, used to check if term is dup - input  */
/* int arrayLength: The length of the array - input/output               */
/* Return Value: int arrayLength: Return the arrayLength                 */
/* 																																			 */
/*************************************************************************/
int duplicate(double bases[], int exponents[], double base, int exponent, int arrayLength)
{
	for(int iter = 0; iter < arrayLength; iter++)
	{
		//If the array is full check to see if we can combine bases
		if(arrayLength > 10)
		{
			if(exponents[iter] == exponent)
			{
				bases[iter] += base;
				return arrayLength;
			}
			//If not do nothing
			else
				return arrayLength;
		}
		//If exponents are equal combine bases
		if(exponents[iter] == exponent)
		{
			bases[iter] += base;
			return arrayLength;
		}
	}
	//If array not full and bases are not equal add it anyways
	bases[arrayLength] = base;
	exponents[arrayLength] = exponent;
	arrayLength++;
	return arrayLength;
}

/*************************************************************************/
/* Function name: duplicate 																						 */
/* Description: Check bases and exponents arrays for dup exponents if    */
/* 							they are dups add 																			 */
/* 							bases together, delete old term and continue             */
/* Parameters:                                            							 */
/* Term termArray[]: An array of terms that have been read in - input    */
/* int arrayLength: The length of the array - input/output               */
/* double base: Current base value, used if term is dup - input          */
/* int exponent: Current exponent, used to check if term is dup - input  */
/* Return Value: int arrayLength: Return the arrayLength                 */
/*************************************************************************/
int duplicate(Term termArray[], int arrayLength, double base, int exponent)
{
	for(int iter = 0; iter < arrayLength; iter++)
	{
		//If array is full check to see if exponents are the same and combine
		if(arrayLength > 10)
		{
			if(termArray[iter].getExponent() == exponent)
			{
				Term tmpTerm((base + termArray[iter].getCoefficient()), exponent);
				termArray[iter] = tmpTerm;
				return arrayLength;
			}
			//If not do nothing
			else
				return arrayLength;
		}

		if(termArray[iter].getExponent() == exponent)
		{
			Term tmpTerm((base + termArray[iter].getCoefficient()), exponent);
			termArray[iter] = tmpTerm;
			return arrayLength;
		}
	}
	Term tmpTerm(base, exponent);
	termArray[arrayLength] = tmpTerm;
	arrayLength++;
	return arrayLength;
}

/*************************************************************************/
/* Function name: parseData 																						 */
/* Description: Read data from file for parallel arrays                  */
/* Parameters: fstream& termFile: file to be read - input 							 */
/* double bases[]: An array of bases - input                             */
/* int exponents[]: An array of exponents - input                        */
/* Return Value: int arrayLength: Return the arrayLength                 */
/*************************************************************************/
int parseData(fstream& termFile, double bases[], int exponents[])
{
	int arrayLength = 0;
	double base = 0.0;
	int exponent = 0;
	// Read each base and exponent into the array
	while(termFile >> base >> exponent)
	{
		//If the array is empty return the first array
		if(arrayLength == 0)
		{
			bases[arrayLength] = base;
			exponents[arrayLength] = exponent;
			arrayLength++;
		}
		else
		{
			arrayLength = duplicate(bases, exponents, base, exponent, arrayLength);
		}
	}
	//Reset file
	termFile.clear();
	termFile.seekg(0, ios::beg);
	return arrayLength;
}

/*************************************************************************/
/* Function name: parseData 																						 */
/* Description: Read data from file for Vector of Terms                  */
/* Parameters: fstream& termFile: file to be read - input 							 */
/* vector<Term> termVec: A vector of terms - input/output                */
/* Return Value: termVec: Return the vector of Terms for more work       */
/*************************************************************************/
vector<Term> parseData(fstream& termFile, vector<Term> termVec)
{
	double base = 0.0;
	int exponent = 0;
	int count = 0;
	//Read in base and exponent
	while(termFile >> base >> exponent)
	{
		if(count == 0)
		{
			Term tmpTerm(base, exponent);
			termVec.push_back(tmpTerm);
			count++;
		}
		else
			termVec = duplicate(termVec, base, exponent);
	}
	sort(termVec.begin(),termVec.end());
	//Reset file
	termFile.clear();
	termFile.seekg(0, ios::beg);
	return termVec;
}

/*************************************************************************/
/* Function name: parseData 																						 */
/* Description: Read data from file for Term array                       */
/* Parameters: fstream& termFile: file to be read - input 							 */
/* Term termArray[]: An array of terms - input                           */
/* Return Value: arrayLength : Return arrayLength    for more work       */
/*************************************************************************/
int parseData(fstream& termFile, Term termArray[])
{
	double base;
	int exponent;
	int arrayLength = 0;
	//Read in base and exponent
	while(termFile >> base >> exponent)
	{
		if(arrayLength == 0)
		{
			Term tmpTerm(base, exponent);
			termArray[arrayLength] = tmpTerm;
			arrayLength++;
		}
		else
			arrayLength = duplicate(termArray, arrayLength, base, exponent);
	}
	termFile.clear();
	termFile.seekg(0, ios::beg);
	return arrayLength;
}

/*************************************************************************/
/* Function name: bubbleSort 																						 */
/* Description: Sort parallel arrays, keep bases & exponents together    */
/* Parameters: double bases[]: An array of base - input   							 */
/* int exponents[]: An array of exponents to be sorted - input           */
/* int arrayLength: The length of the arrays to be sorted - input        */
/* Return Value: none                                                    */
/*************************************************************************/
void bubbleSort(double bases[], int exponents[], int arrayLength)
{
	//Bubblesort the arrays bases on exponent
	int a, b, flag = 1;
	double tempBase;
	int tempExp;
	for(a = 1; (a <= arrayLength)  && flag; a++)
	{
		flag = 0;
		for(b = 0; b < (arrayLength-1); b++)
		{
			if(exponents[b+1] > exponents[b])
			{
				tempExp = exponents[b];
				tempBase = bases[b];
				exponents[b] = exponents[b+1];
				bases[b] = bases[b+1];
				exponents[b+1] = tempExp;
				bases[b+1] = tempBase;
				flag = 1;
			}
		}
	}
}
/************************************************************************/
/* Function name: bubbleSort                                            */
/* Description: Order the array of terms in descending order            */
/* Paramters: Term array[]: An array of Terms - input                   */
/* int arrayLength: The length of the array - input                     */
/* Retrun Value: none                                                   */
/***********************************************************************/
void bubbleSort(Term termarray[], int arraylength)
{
	int a, b, flag = 1;
	Term tmpterm;
	for(a = 1; (a <= arraylength)  && flag; a++)
	{
		flag = 0;
		for(b = 0; b < (arraylength-1); b++)
		{
			if(termarray[b+1].getExponent() > termarray[b].getExponent())
			{
				tmpterm = termarray[b];
				termarray[b] = termarray[b+1];
				termarray[b+1] = tmpterm;
				flag = 1;
			}
		}
	}
}

/*************************************************************************/
/* Function name: printParallelArrayIterative   												 */
/* Description: Print the parallel arrays iteratively                    */
/* Parameters: double bases[]: An array of base - input   							 */
/* int exponents[]: An array of exponents to be sorted - input           */
/* int arrayLength: The length of the arrays to be sorted - input        */
/* double xValue: The value given by the user                            */
/* Return Value: none                                                    */
/*************************************************************************/
void printParallelArrayIterative(double bases[], int exponents[], int arrayLength, double xValue)
{
	double total = 0.0;
	cout << "PARALLEL ITERATIVE\n";
	for(int iter = 0; iter < arrayLength; iter++)
	{
		cout << bases[iter] << "x^" << exponents[iter] << "+";
		total += (bases[iter] * pow(xValue, exponents[iter]));
	}
	cout << "\b \n";
	cout << "Evaluated: " << total << endl << endl;
}

/*************************************************************************/
/* Function name: parallelIterative   												           */
/* Description: Initiate variables and print the evaluation call other   */
/* 							functions needed 																				 */
/* Parameters: fstream& termfile: File to be read - input  							 */
/* double xValue: The value given by the user                            */
/* Return Value: none                                                    */
/*************************************************************************/
void parallelIterative(fstream& termFile,  double xValue)
{
	// Print the parallel arrays iteratively
	int arrayLength;
	double bases[10];
	int exponents[10];
	double total = 0.0;

	arrayLength = parseData(termFile, bases, exponents);
	bubbleSort(bases, exponents, arrayLength);
	printParallelArrayIterative(bases, exponents, arrayLength, xValue);

}

/*************************************************************************/
/* Function name: printParallelArraysRecursive  							           */
/* Description: Print the parallel arrays recursively                    */
/* Parameters: double bases[]: Array of bases - input                    */
/* int exponents: An array of exponents - input                          */
/* int arrayLength: The length of the array - input                      */
/* double xValue: The value given by the user - input                    */
/* double total: The total of the evaluations - inut/output              */
/* Return Value: double total: total of the evaluations                  */
/*************************************************************************/
double printParallelArraysRecursive(double bases[], int exponents[], int arrayLength, double xValue, double total)
{
	//BUGS: IF ARRAY IS LESS THAN 10 INF shows up
	//If the array is zero calculate total then shoot back up recursion
	if(arrayLength == 0)
	{
		total += (bases[arrayLength] * pow(xValue, exponents[arrayLength]));
	}
	else
	{
		total += (bases[arrayLength] * pow(xValue, exponents[arrayLength]));
		total = printParallelArraysRecursive(bases, exponents, arrayLength-1, xValue, total);
	}
	//print in reverse order
	if(arrayLength >= 1)
	{
		cout << bases[arrayLength-1] << "x^" << exponents[arrayLength-1] << "+";
	}
	return total;
}

/*************************************************************************/
/* Function name: parallelRecursive             							           */
/* Description: Helper function to set up recursive array print          */
/* Parameters: fstream& termFile: File to be read - input                */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void parallelRecursive(fstream& termFile, double xValue)
{
	double bases[10];
	int exponents[10];
	int arrayLength = 0;
	double total;

	arrayLength = parseData(termFile, bases, exponents);
	bubbleSort(bases, exponents, arrayLength);
	cout << "PARALLEL ARRAY RECURSIVE\n";

	total = printParallelArraysRecursive(bases, exponents, arrayLength, xValue, 0.0);
	cout << "\b \nEvaluated: " << total << endl << endl;
}

/*************************************************************************/
/* Function name: printObjectArrayIterative      							           */
/* Description: Print the object array iteratively                       */
/* Parameters: Term termArray[]: An array of Terms - inputs              */
/* int arrayLength: The length of the array - input                      */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void printObjectArrayIterative(Term termArray[], int arrayLength, double xValue)
{
	double total = 0.0;
	for(int iter = 0; iter < arrayLength; iter++)
	{
		cout << termArray[iter] << "+";
		total += termArray[iter](xValue);
	}
	cout << "\b \n";
	cout << "Evaluated: " << total << endl << endl;
}

/*************************************************************************/
/* Function name: objectArrayIterative           							           */
/* Description: Helper function to setup print the array iteratively     */
/* Parameters: fstream& termFile - inputs                                */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void objectArrayIterative(fstream& termFile, double xValue)
{
	Term termArray[10];
	int arrayLength = 0;

	arrayLength = parseData(termFile, termArray);
	bubbleSort(termArray, arrayLength);

	cout << "OBJECT ARRAY ITERATIVE\n";
	printObjectArrayIterative(termArray, arrayLength, xValue);
}

/*************************************************************************/
/* Function name: printObjectArrayRecursive      							           */
/* Description: Print the object array recursively                       */
/* Parameters: Term termArray[]: An array of term - inputs               */
/* int arrayLength: The array length - input                             */
/* double xValue: The value given by the user - input                    */
/* double total: The total of the evaluation - input/output              */
/* Return Value: double total: the total of the evaluation               */
/*************************************************************************/
double printObjectArrayRecursive(Term termArray[], int arrayLength, double xValue, double total)
{
	//If 0 add to total shoot back up array
	if(arrayLength == 0)
	{
		total += termArray[0](xValue);
	}
	else
	{
		total += termArray[arrayLength](xValue);
		total = printObjectArrayRecursive(termArray, arrayLength-1, xValue, total);
	}
	if(arrayLength >=1)
	{
		cout << termArray[arrayLength-1] << "+";
	}
	return total;
}

/*************************************************************************/
/* Function name: objectArrayRecursive           							           */
/* Description: Helper function to setup print the array recursively     */
/* Parameters: fstream& termFile - inputs                                */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void objectArrayRecursive(fstream& termFile, double xValue)
{
	Term termArray[10];
	int arrayLength = 0;
	double total = 0.0;

	arrayLength = parseData(termFile, termArray);
	bubbleSort(termArray, arrayLength);
	cout << "OBJECT ARRAY RECURSIVE\n";

	total += printObjectArrayRecursive(termArray, arrayLength, xValue, total);
	cout << "\b " << endl;
	cout << "Evaluated: " << total << endl << endl;
}

/*************************************************************************/
/* Function name: printObjectArrayPointerRecursive						           */
/* Description: Print the object array recursively using pointers        */
/* Parameters: Term termArray[]: An array of term - inputs               */
/* int arrayLength: The array length - input                             */
/* double xValue: The value given by the user - input                    */
/* Return Value: double total: the total of the evaluation               */
/*************************************************************************/
double printObjectArrayPointerRecursive(Term termArray[], double xValue, int arrayLength, double total)
{
	// If arrayLength == 0 shoot back up the recursion
	if(arrayLength <= 0)
	{
		return total;
	}
	cout << *termArray << "+";
	total = total + (*termArray)(xValue);
	printObjectArrayPointerRecursive(termArray+1, xValue, arrayLength-1, total);
}

/*************************************************************************/
/* Function name: objectArrayPointerRecursive    							           */
/* Description: Helper function to setup print the array recursively     */
/* Parameters: fstream& termFile - inputs                                */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void objectArrayPointerRecursive(fstream& termFile, double xValue)
{
	Term termArray[10];
	int arrayLength = 0;

	arrayLength = parseData(termFile, termArray);
	bubbleSort(termArray, arrayLength);
	cout << "OBJECT ARRAY POINTER RECURSIVE\n";

	double total = printObjectArrayPointerRecursive(termArray, xValue, arrayLength, 0.0);
	cout << "\b \nEvaluated: " << total <<  endl << endl;
}

/*************************************************************************/
/* Function name: printSTLVectorForLoop         							           */
/* Description: Print the vector of Terms                                */
/* Parameters: vector<Term> termVec: A vector of terms - inputs          */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void printSTLVectorForLoop(vector<Term> termVec, double xValue)
{
	//Print the STL Vector in a For Loop
	double total = 0.0;
	cout << "STL VECTOR FOR LOOP\n";
	for(int iter = 0; iter < termVec.size(); iter++)
	{
		cout << termVec[iter] << "+";
		total += termVec[iter](xValue);
	}
	cout << "\b \n";
	cout << "Evaluated: " << total << endl << endl;
}

/*************************************************************************/
/* Function name: stlVectorForLoop              							           */
/* Description: Setup function to print stl vector                       */
/* Parameters: fstream& termFile: A file of terms to be read - inputs    */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void stlVectorForLoop(fstream& termFile, double xValue)
{
	vector<Term> termVec;
	termVec = parseData(termFile, termVec);
	printSTLVectorForLoop(termVec, xValue);
}

/*************************************************************************/
/* Function name: stlVectorIterator              							           */
/* Description: print stl vector iteratively                             */
/* Parameters: vector<Term> termVec: A vector of terms - inputs          */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void printSTLVectorIterator(vector<Term> termVec, double xValue)
{
	//Print the stl vector with an iterator
	double total = 0.0;
	cout << "STL VECTOR ITERATOR\n";
	vector<Term>::iterator iter;

	for(iter = termVec.begin(); iter < termVec.end(); iter++)
	{
		cout << *iter << "+";
		total += (*iter)(xValue);
	}
	cout << "\b \n";
	cout << "Evaluated: " << total << endl << endl;
}

/*************************************************************************/
/* Function name: stlVectorIterator              							           */
/* Description: Setup function to print stl vector with an iterator      */
/* Parameters: fstream& termFile: A file of terms to be read - inputs    */
/* double xValue: The value given by the user - input                    */
/* Return Value: none                                                    */
/*************************************************************************/
void stlVectorIterator(fstream& termFile, double xValue)
{
	vector<Term> termVec;
	termVec = parseData(termFile, termVec);
	printSTLVectorIterator(termVec, xValue);
}

/*************************************************************************/
/* Function name: mainScreen                    							           */
/* Description: Print main menu options                                  */
/* Return Value: none                                                    */
/*************************************************************************/
void mainScreen()
{
	cout << "1: PARALLEL ITERATIVE\n";
	cout << "2: PARALLEL RECURSIVE\n";
	cout << "3: OBJECT ARRAY ITERATIVE\n";
	cout << "4: OBJECT ARRAY RECURSIVE\n";
	cout << "5: OBJECT ARRAY POINTER RECURSIVE\n";
	cout << "6: STL VECTOR FOR LOOP\n";
	cout << "7: STL VECTOR ITERATOR\n";
	cout << "8: EXIT\n\n";
}

/**************************************************************************/
/* Function name: main                          							           */
/* Description: Call all other functions. Setup program                  */
/* Parameters: int argc: The number of arguments - input                 */
/* char *argv[]: An array of pointers to the arguments                   */
/* Return Value: none                                                    */
/*************************************************************************/
int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		string file = argv[1];
		double xValue = atof(argv[2]);

		fstream termFile(file.c_str());

		mainScreen();
		stlVectorForLoop(termFile, xValue);
		stlVectorIterator(termFile, xValue);
		objectArrayIterative(termFile, xValue);
		objectArrayRecursive(termFile, xValue);
		objectArrayPointerRecursive(termFile, xValue);
		parallelIterative(termFile, xValue);
		parallelRecursive(termFile, xValue);

	}
}
