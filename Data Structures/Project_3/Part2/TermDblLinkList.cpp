
// File: TermDblLinkList.cpp
// Author: Dr. Spiegel
// Updater: Bryce Andress
// Container of Term objects 
//   Implementations of member functions including inherited pure virtual fns.

#include <fstream>
#include <iostream>
#include <iomanip>
#include "TermDblLinkList.h"
#include "term.h"
#include "DblLink.h"
#include "DblLinkItr.h"

using namespace std;
  ///readIntoList
  ///Read a file into a list
  /// \param string filename is a string to a file to read
  /// \return none
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
    DblLinkedItr<Term> termListItr(ThePoly);
    DblLinkedItr<Term> termListItr2(ThePoly);
    ++termListItr2;
    while(!termListItr.isLastNode())
    {
      if(termListItr().getExponent() == termListItr2().getExponent())
      {
        Term tmpTerm((termListItr2().getCoefficient()+termListItr().getCoefficient()), termListItr().getExponent());
        ThePoly.remove(termListItr());
        ThePoly.remove(termListItr2());
        ThePoly.insert(tmpTerm);
      }
      ++termListItr;
      ++termListItr2;
    }
  }
  /// printIteratively
  /// Print the data iteratively
  /// \param none
  /// \return None
  void TermDblLinkList::printIteratively()
  { cout<<"---------------------------------"<<endl;
    cout<<"|   Double Link List  Iterative  |"<<endl;
    cout<<"---------------------------------"<<endl;
    DblLinkedItr<Term> termListItr(ThePoly);
    while (!termListItr.isLastNode())
    {
        cout <<  termListItr() << " + ";
        ++termListItr;
    } 
    cout <<  termListItr();
    cout << endl << endl;
  }
 
  /// print DblLinkRecursively
  /// Print the DblLink List recursively
  /// \param DblLinkedItr<Term> termListItr - The iterator for the list
  /// \return none 
  void TermDblLinkList::printDblLinkRecursively(DblLinkedItr<Term> termListItr)
  {
    if(termListItr.isLastNode())
    {
        cout << termListItr();
	return;
    }
    cout << termListItr() << " + ";
    ++termListItr;
    printDblLinkRecursively(termListItr);
  }

  /// printRecursively
  /// Start printing recursively
  /// \param none
  /// \return none
  void TermDblLinkList::printRecursively()
  {
    cout<<"---------------------------------"<<endl;
    cout<<"|   Double Link List Recursive   |"<<endl;
    cout<<"---------------------------------"<<endl;
    DblLinkedItr<Term> termListItr(ThePoly);
    printDblLinkRecursively(termListItr);
    cout << endl;
  }
  /// ()
  /// Evaluate the Polynomial
  /// \param Double x which is the value to evaluate for
  /// \return double which is the answer
  double TermDblLinkList::operator()(double x) const
  {
    double result=0.0;
    DblLinkedItr<Term> termListItr(ThePoly);
    while (!termListItr.isLastNode())
    {
      result+=termListItr()(x);
      ++termListItr;
    }
    result += termListItr()(x);
    return(result);
  }
