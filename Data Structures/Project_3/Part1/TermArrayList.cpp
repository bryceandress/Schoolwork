// File: TermArrayList.cpp
// Author: Dr. Spiegel
// Updater: Bryce Andress
// Container of Term objects 
//   Implementations of member functions including inherited pure virtual fns.

#include <fstream>
#include <iostream>
#include <iomanip>
#include "TermArrayList.h"

using namespace std;

  //Constructor
  //Iniat numTerms to 0 and create object
  //Parameters none
  //Return none
  TermArrayList::TermArrayList()
  { numTerms=0; }
  
  //readIntoList
  //Read a file into a list of terms and sort
  //Paramets: Take a string that is a file name
  //Return none
  void TermArrayList::readIntoList(string filename)
  { ifstream source(filename.c_str());
    double coeff;
    int expn;
    bool added;
    while (source >> expn >> coeff)  {
      added = false;
      for (int iter = 0; iter < numTerms; iter++)
      {
        if(ThePoly[iter].getExponent() == coeff)
        {
          Term tmpTerm((expn + ThePoly[iter].getCoefficient()), coeff);
          ThePoly[iter] = tmpTerm;
          numTerms;
          added = true;
        }
      }
      if (!added)
      {
        Term T(expn,coeff);
        ThePoly[numTerms++]=T;
        added = false;
      }
    }
    source.close();
    source.clear();

    int a, b, flag = 1;
    Term tmpterm;
    for(a=1; (a <= numTerms) && flag; a++)
    {
        flag = 0;
        for(b=0; b<(numTerms-1); b++)
        {
            if(ThePoly[b+1].getExponent() > ThePoly[b].getExponent())
            {
                tmpterm = ThePoly[b];
                ThePoly[b] = ThePoly[b+1];
                ThePoly[b+1] = tmpterm;
                flag = 1;
            }
        }
    }
  }
  // printIteratively
  // Print the data iteratively
  // No Parameters
  // Return none
  void TermArrayList::printIteratively()
//  void printObjectArrayIterator(TermArray ThePoly[], int numTerms)
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Iterative       |"<<endl;
    cout<<"---------------------------------"<<endl;
    for(int i=0; i<numTerms; i++) {
//      cout<<" "<<ThePoly[i]<< "    " << ThePoly[i].getArea() << 
//	    		"    " << ThePoly[i].getPerimeter() << endl;
      cout <<  ThePoly[i] << (i < numTerms-1?" + ":"");
    }
    cout << endl << endl;
  }

  // printArrayRecursively
  // Prints the data recursively
  // int arrayLength - the length of the array to be printed
  // Returns none
  void TermArrayList::printArrayRecursively(int arrayLength)
  {
    if(arrayLength == 0)
    {
	cout << ThePoly[arrayLength] << " + ";
	return;
    }
    printArrayRecursively(arrayLength-1);
    if(arrayLength == numTerms)
        return;
    cout << ThePoly[arrayLength] << (arrayLength < numTerms-1?" + ":"") ;
  }
  
  // printRecursively
  // Prints the data recursively
  // Parameters: none
  // Returns: none
  void TermArrayList::printRecursively()
  {
    cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Recursive:       |"<<endl;
    cout<<"---------------------------------"<<endl;

    printArrayRecursively(numTerms);
    cout << endl;
  }

  // printPtr
  // Print the data with a pointer
  // Parameters: none
  // Return None
  void TermArrayList::printPtr()
  //void printObjectArrayPointerRecursive(TermArray* ThePoly, int numTerms)
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Pointer         |"<<endl;
    cout<<"---------------------------------"<<endl;
    Term *now=ThePoly;
    for(int i=0; i<numTerms; i++)
      cout << *(now++)  << (i < numTerms-1?" + ":"");
    cout << endl << endl;
  }
  // ()  
  // Evaluate the Polynomial
  // Parameters double x which is value to evaluate for
  // Return double
  double TermArrayList::operator()(double x) const
  { double result=0.0;
    for (int idx=0;idx<numTerms;idx++)
      result+=ThePoly[idx](x);
    return(result);
  }
