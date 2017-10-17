// File: TermArrayList.cpp
// Container of Term objects 
//   Implementations of member functions including inherited pure virtual fns.

#include <fstream>
#include <iostream>
#include <iomanip>
#include "TermArrayList.h"

using namespace std;

  TermArrayList::TermArrayList()
  { numTerms=0; }

  void TermArrayList::readIntoList(string filename)
  { ifstream source(filename.c_str());
    double coeff;
    int expn;
    while (source >> expn >> coeff)  {
      Term T(expn,coeff);
      ThePoly[numTerms++]=T;
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

  // Print the data iteratively
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


  // Print the data with a pointer
  void TermArrayList::printPtr()
  //void printObjectArrayPointerRecursive(TermArray* ThePoly, int numTerms)
  { cout<<"---------------------------------"<<endl;
    cout<<"|Object  Array  Pointer         |"<<endl;
    cout<<"---------------------------------"<<endl;
    Term *now=ThePoly;
    for(int i=0; i<numTerms; i++)
      cout << " " << *(now++)  << (i < numTerms-1?" +":"");
    cout << endl << endl;
  }

  // Evaluate the Polynomial
  double TermArrayList::operator()(double x) const
  { double result=0.0;
    for (int idx=0;idx<numTerms;idx++)
      result+=ThePoly[idx](x);
    return(result);
  }
