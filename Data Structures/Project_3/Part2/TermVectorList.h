// File: TermArrayList.h
// Container of TermArray objects. 
// Printing can be iterative or recursive. 


#ifndef TERMVECTORLIST_H
#define TERMVECTORLIST_H

#include <fstream>
#include <string>
#include "TermList.h"
#include "term.h"
#include <vector>

using namespace std;

class TermVectorList : public TermList {
public:

  // Put a string of strings into the list object
  //void readIntoList(ifstream &source);
  void readIntoList(string filename);

  // Print the data iteratively
  void printIteratively();
  
  // Evaluate the Polynomial
  virtual double operator()(double x) const;

  // Print the data recursively
  void printRecursively();

  void printVectorRecursively(int);

private:
  vector<Term> ThePoly;
  int numTerms;
  
};
  
#endif
