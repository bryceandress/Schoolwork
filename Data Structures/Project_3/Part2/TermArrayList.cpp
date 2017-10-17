
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

  /*!Constructor
  Iniat numTerms to 0 and create object
  Parameters none
  Return none*/
  TermArrayList::TermArrayList()
  { numTerms=0; }
  
  /*! readIntoList
  Read a file into a list of terms and sort
  \param Take a string that is a file name
  \return none*/
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
  /*! printIteratively
   Print the data iteratively 
   \return none*/
  void TermArrayList::printIteratively()
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Iterative       |"<<endl;
    cout<<"---------------------------------"<<endl;
    for(int i=0; i<numTerms; i++) {
      cout <<  ThePoly[i] << (i < numTerms-1?" + ":"");
    }
    cout << endl << endl;
  }

  /*! printArrayRecursively
    Prints the data recursively
   \param int arrayLength - the length of the array to be printed
   \return none*/
  void TermArrayList::printArrayRecursively(int arrayLength)
  {
    if(arrayLength == 0)
    {
	//cout << ThePoly[arrayLength] << " + ";
	return;
    }
    printArrayRecursively(arrayLength-1);
    if(arrayLength == numTerms)
        return;
    else 
         cout << ThePoly[arrayLength] << (arrayLength < numTerms-1?" + ":"") ;
  }
  
  /*! printRecursively
   Prints the data recursively
   \param none
   \return none*/
  void TermArrayList::printRecursively()
  {
    cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Recursive:       |"<<endl;
    cout<<"---------------------------------"<<endl;

    printArrayRecursively(numTerms);
    cout << endl;
  }

  /*! printPtr
   Print the data with a pointer
   \param none
   \return None */
  void TermArrayList::printPtr()
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Pointer         |"<<endl;
    cout<<"---------------------------------"<<endl;
    Term *now=ThePoly;
    for(int i=0; i<numTerms; i++)
      {
        cout << *(now++)  << (i < numTerms-1?" + ":"");
        cout << endl << endl;
      }
  }
  /*! ()  
   Evaluate the Polynomial
   \param double x which is value to evaluate for
   \return double */
  double TermArrayList::operator()(double x) const
  { double result=0.0;
    for (int idx=0;idx<numTerms;idx++)
      result+=ThePoly[idx](x);
    return(result);
  }
