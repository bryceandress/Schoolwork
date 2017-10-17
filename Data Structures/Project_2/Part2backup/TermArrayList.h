// File: TermArrayList.h
// Container of TermArray objects. 
// Printing can be iterative or recursive. 


#ifndef WORDDATALIST_H
#define WORDDATALIST_H

#include <fstream>
#include <string>
#include "TermList.h"
#include "term.h"

using namespace std;

class TermArrayList : public TermList {
public:

  TermArrayList();

  // Put a string of strings into the list object
  //void readIntoList(ifstream &source);
  void readIntoList(string filename);

  // Print the data iteratively
  void printIteratively();
  
  // Print the data recursively with a pointer
  void printPtr();

  // Evaluate the Polynomial
  virtual double operator()(double x) const;

private:
  Term ThePoly[10];
  int numTerms;
  
};
  
#endif
