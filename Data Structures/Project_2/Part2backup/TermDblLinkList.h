// File: TermDblLinkList.h
// Container of TermArray objects. 
// Printing can be iterative or recursive. 


#ifndef TERMDBLLINKLIST_H
#define TERMDBLLINKLIST_H

#include <fstream>
#include <string>
#include "TermList.h"
#include "term.h"
#include "DblLink.h"
#include "DblLinkItr.h"

using namespace std;

class TermDblLinkList : public TermList {
public:

  TermDblLinkList();

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
  DblLinkedList<Term> ThePoly;
  int numTerms;
  
};
  
#endif
