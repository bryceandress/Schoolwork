// File: TermArrayList.cpp
// Author: Dr. Spiegel
// Updater: Bryce Andress
// Container of Term objects 
//   Implementations of member functions including inherited pure virtual fns.

#include <fstream>
#include <iostream>
#include <iomanip>
#include "TermVectorList.h"
#include <algorithm>

using namespace std; // readIntoList // read a file into a vector of terms // Parameters: string filename which is the file to open
  // Return: none 
  void TermVectorList::readIntoList(string filename) 
  { 
      ifstream source(filename.c_str()); 
      double coeff; 
      int expn; 
      while (source >> expn >> coeff)  
      {
        Term T(expn,coeff);
        ThePoly.push_back(T);
      }
      sort(ThePoly.begin(),ThePoly.end());
      source.close();
      source.clear();
      for(int iter = 0; iter < ThePoly.size(); iter++)
      {
        if(ThePoly[iter].getExponent() == ThePoly[iter+1].getExponent())
        {
          Term tmpTerm((ThePoly[iter].getCoefficient()+ThePoly[iter+1].getCoefficient()), ThePoly[iter].getExponent());
          ThePoly.erase(ThePoly.begin()+iter+1);
          ThePoly.erase(ThePoly.begin()+iter);
          ThePoly.push_back(tmpTerm);
          sort(ThePoly.begin(), ThePoly.end());
        }
      }
  }
  // printIteratively()
  // Print the data iteratively
  // Parameters: none
  // Return none
  void TermVectorList::printIteratively()
  { cout<<"---------------------------------"<<endl;
    cout<<"|   Object  Vector  Iterative   |"<<endl;
    cout<<"---------------------------------"<<endl;
    for(int iter = 0; iter < ThePoly.size(); iter++){
      if (iter < ThePoly.size()-1)
      	cout <<  ThePoly[iter] << " + ";
      else
	cout << ThePoly.back() << endl << endl;
    }
  }
  
  // printVectorRecursively
  // Print the vector in a recursive manor
  // int index - where we are in the vector
  // Returns none
  void TermVectorList::printVectorRecursively(int index)
  {
    if (index != ThePoly.size())
    {  
       cout << ThePoly[index] << (index < (ThePoly.size()-1)?" + ":""); 
       printVectorRecursively(index + 1);
    }
  }

  // printRecursively
  // Start the recursive print
  // Parameters none
  // Returns none
  void TermVectorList::printRecursively()
  {
    cout<<"---------------------------------"<<endl;
    cout<<"|   Object  Vector  Recursive   |"<<endl;
    cout<<"---------------------------------"<<endl;

    printVectorRecursively(0);
    cout << endl; 
  }
  // ()
  // Evaluate the Polynomial
  // Parameters: Double x which is the value to evaluate for
  // Return: None
  double TermVectorList::operator()(double x) const
  { double result=0.0;
    for(int iter = 0; iter < ThePoly.size(); iter++) 
    {   
	result+=ThePoly[iter](x);
    }
    return(result);
  }
