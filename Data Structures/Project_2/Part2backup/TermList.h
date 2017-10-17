// File: TermList.h
// Abstract base class for containers of Terms
// Known subclasses:
//      TermArray
// Coming soon: ParallelArrayTermList, TermVectorList, ...

#ifndef TERMLIST_H
#define TERMLIST_H

#include <fstream>
#include <string>

using namespace std;

class TermList {
public:

  // Place the line of text into the data structure
  virtual void readIntoList(string filename)=0;
  //
  // Print the data iteratively
  virtual void printIteratively()=0;

  // Print the data Iteratively with a pointer
  virtual void printPtr() {}   // not pure virtual; why?

  // Evaluate the Polynomial
  virtual double operator()(double x) const=0;
    
};
  
#endif
