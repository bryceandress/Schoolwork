// File: TermArrayList.cpp
// Container of Term objects 
//   Implementations of member functions including inherited pure virtual fns.

#include <fstream>
#include <iostream>
#include <iomanip>
#include "TermDblLinkList.h"

using namespace std;

  TermDblLinkList::TermDblLinkList()
  { numTerms=0; }

  void TermDblLinkList::readIntoList(string filename)
  { ifstream source(filename.c_str());
    double coeff;
    int expn;
    while (source >> expn >> coeff)  {
      Term T(expn,coeff);
      ThePoly.insert(T);
    }
    source.close();
    source.clear();

  }

  // Print the data iteratively
  void TermDblLinkList::printIteratively(DblLinkedList<Term>& ThePoly)
//  void printObjectArrayIterator(TermArray ThePoly[], int numTerms)
  { cout<<"---------------------------------"<<endl;
    cout<<"|   Double Link List  Iterative  |"<<endl;
    cout<<"---------------------------------"<<endl;
    DblLinkedItr<Term> termListItr(ThePoly);
    while (!termListItr.isLastNode())
    {
        cout <<  termListItr() << "+ ";
        ++termListItr;
    } 
    cout <<  termListItr();
    cout << endl << endl;
  }

  // Evaluate the Polynomial
  double TermDblLinkList::operator()(double x) const
  {
    double result=0.0;
    DblLinkedItr<Term> termListItr(ThePoly);
    while (!termListItr.isLastNode())
      result+=termListItr()(x);
      ++termListItr;
    return(result);
  }
