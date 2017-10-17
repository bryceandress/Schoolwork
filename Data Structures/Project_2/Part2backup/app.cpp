/****************************************************************/
/*   Author:         Dr. Spiegel (with thanks to Adam Tal)      */
/*   Course:         CIS237 310                                 */
/*   Filename:       app.cpp                                    */
/*   Purpose:        This Example inputs a file name and demon- */
/*                   strates how to store it using a subclass   */
/*                   of an abstract base class that incorporates*/
/*                   virtual functions to enable polymorphism   */
/*                   If a file name is                          */
/*                   input through the command line all of the  */
/*                   options will be done automatically         */
/****************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "TermList.h"
#include "TermArrayList.h"
#include "TermDblLinkList.h"
// #include "WordData.h"        app only knows about the lists!

using namespace std;


/*********************************************************************/
/*   Function Name: displayMenu()                                    */
/*                                                                   */
/*   Description: Displays the menu on the screen.                   */
/*********************************************************************/
void displayMenu();

/*********************************************************************/
/*   Function Name: printEverything                                  */
/*                                                                   */
/*   Description: Takes in a sentence and sends it through every     */
/*                parsing and printing function                      */
/*                                                                   */
/*   Parameters:  string fileName - file name sent to every function */
/*                TermArrayList ThePoly - The array of object        */
/*********************************************************************/
void printEverything(const string &fileName,TermList *ThePoly, double evalX);

/*********************************************************************/
/*   Function Name: evalPoly                                         */
/*                                                                   */
/*   Description: Computes P(x) for variable x, supplied by the user.*/
/*                                                                   */
/*   Parameters:  TermArrayList *ThePoly - The TermList object       */
/*********************************************************************/
void evalPoly(TermList *ThePoly);

int main(int argc,char *argv[])
{
  fstream file;
  TermList *ThePoly;
  if(argc==1) //if there was an input on the command line
    { double evalX=atof(argv[2]);
      file.open(argv[1]); //try and open the file
      if (file.fail())       //if the file does not open, terminate
          {                    
            cout<<"Sorry, the file failed to open."<<endl;
            return 0;
          }
      file.close();
      string fName(argv[1]);
      printEverything(fName,ThePoly,evalX);
      return 0;
    }
  else
  {
    cout << "Format app <file to read> <int to evaluate>" << endl;
  }
  string filename;
  char selection;
  cout<<"Please enter a file name:"<<endl;
  getline(cin,filename);
  file.open(filename.c_str()); //try and open the file
  if (file.fail())       //if the file does not open, terminate
      {                    
        cout<<"Sorry, the file failed to open."<<endl;
        return 0;
      }
  file.close();
  
  // ThePoly is a pointer to a TermList that is pointed at a TermList subclass
  ThePoly=new TermArrayList;
  ThePoly->readIntoList(filename);  // Apply polymorphism
  while (true)
    {
      displayMenu();
      cin>>selection;
      switch(selection)
        { case '1':
            ThePoly->printIteratively();
            break;
          case '2':
            ThePoly->printPtr();
            break;
	  case '3':
	    evalPoly(ThePoly);
	    break;
          case '4':
            cout<<"Goodbye"<<endl;
            return 0;
          default:
            cout<<"I cannot understand "<<selection<<".  Try again."<<endl;
            break;
        }
    }
  
  return 0;
}

// Displays the menu on the screen
void displayMenu()
{
  cout <<endl;
  cout << "Select Term List Type ?"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "Object C++ Array"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "1. Object Array Iterative Print" << endl;
  cout << "2. Object Array Pointer Print" << endl;
  cout << "3. Evaluate the Polynomial" << endl;
  cout << "4. Exit Object Array" << endl;
}

// Takes in a sentence and sends it through every parsing and printing function
void printEverything(const string &filename,TermList *ThePoly, double evalX)
{ ThePoly=new TermArrayList;
  ThePoly->readIntoList(filename);
  ThePoly->printIteratively();
  ThePoly->printPtr();
  cout << "P(" << evalX << ")=" << (*ThePoly)(evalX) << endl;
  ThePoly=new TermDblLinkList;
  ThePoly->readIntoList(filename);
  ThePoly->printIteratively();
  cout << "P(" << evalX << ")=" << (*ThePoly)(evalX) << endl;
}

// Computes P(x) for variable x, supplied by the user
void evalPoly(TermList *ThePoly)
{ double x;
  cout << "Enter a value x for P(x) >";
  cin >> x;
  cout << "P(" << x << ")=" << (*ThePoly)(x) << endl;
}  
