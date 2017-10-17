/****************************************************************/
/*   Author:         Dr. Spiegel (with thanks to Adam Tal)      */
/*   Updater:        Bryce Andress
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
#include "TermVectorList.h"
#include "TermDblLinkList.h"
#include <chrono>

using namespace std;


/*********************************************************************/
/*   Function Name: displayArrayMenu()                               */
/*                                                                   */
/*   Description: Displays the array menu on the screen.             */
/*********************************************************************/
void displayArrayMenu(const string &);

/*********************************************************************/
/*   Function Name: displayVectorMenu()                              */
/*                                                                   */
/*   Description: Displays the Vector menu on the screen.            */
/*********************************************************************/
void displayVectorMenu(const string&);

/*********************************************************************/
/*   Function Name: displayDblLinkMenu()                             */
/*                                                                   */
/*   Description: Displays the Double Link menu on the screen.       */
/*********************************************************************/
void displayDblLinkMenu(const string&);

/*********************************************************************/
/*   Function Name: displayMenu()                                    */
/*                                                                   */
/*   Description: Displays the main menu on the screen.              */
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
  if(argc > 1) //if there was an input on the command line
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
  // If only 1 command line argument was given start main menu
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
  // Get input from user until they decide to exit
  while (true)
    {
      displayMenu();
      cin >> selection;
      cin.ignore();
      switch(selection)
        { case '1':
            displayArrayMenu(filename);
            break;
          case '2':
            displayVectorMenu(filename);
            break;
	  case '3':
	    displayDblLinkMenu(filename);
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


//Display Object options for user
void displayMenu()
{ 
  cout << "Select An Object "<< endl;
  cout << "1. Object Array " << endl;
  cout << "2. Object Vector " << endl;
  cout << "3. Object Double Link List " << endl;
  cout << "4. Exit " << endl;
}

// Displays array menu on the screen
void displayArrayMenu(const string &filename)
{
  TermList *ThePoly;
  char selection;
  bool menu = true;
  cout <<endl;
  while (menu){
  cout << "\nSelect Term List Type ?"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "Object C++ Array"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "1. Object Array Iterative Print" << endl;
  cout << "2. Object Array Pointer Print" << endl;
  cout << "3. Object Array Recursive Print" << endl;
  cout << "4. Evaluate the Polynomial" << endl;
  cout << "5. Exit Object Array" << endl;
  cin  >> selection; 
  ThePoly = new TermArrayList;
  ThePoly->readIntoList(filename);
  switch(selection)
        { case '1':
	  {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printIteratively();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
          }
          case '2':
          {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printPtr();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
          }
	  case '3':
	  {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printRecursively();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
	  }
          case '4':
	    evalPoly(ThePoly);
            break;
          case '5':
	    menu = false;
            delete ThePoly;
            break;
          default:
            cout<<"I cannot understand "<<selection<<".  Try again."<<endl;
            break;
	}
  }
}

void displayVectorMenu(const string &filename)
{
  TermList *ThePoly;
  char selection;
  cout <<endl;
  bool menu = true;
  while (menu) {
  cout << "\nSelect Term List Type ?"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "Object C++ Vector"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "1. Object Vector Iterative Print" << endl;
  cout << "2. Object Vector Recursive Print" << endl;
  cout << "3. Evaluate the Polynomial" << endl;
  cout << "4. Exit Object Vector" << endl;
  cin  >> selection; 
  ThePoly = new TermVectorList;
  ThePoly->readIntoList(filename);
  switch(selection)
        { case '1':
	  {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printIteratively();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
	  }

          case '2':
	  {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printRecursively();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
	  }
	  case '3':
	    evalPoly(ThePoly);
	    break;
          case '4':
	    menu = false;
            delete ThePoly;
	    break;
          default:
            cout<<"I cannot understand "<<selection<<".  Try again."<<endl;
            break;
	}
  }
}

void displayDblLinkMenu(const string &filename)
{ TermList *ThePoly;
  char selection;
  cout <<endl;
  bool menu = true;
  while (menu){
  cout << "\nSelect Term List Type ?"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "Object C++ Double Linked List"<<endl;
  cout << "------------------------------------------------"<<endl;
  cout << "1. Object Double Linked List Iterative Print" << endl;
  cout << "2. Object Double Linked List Recursive Print" << endl;
  cout << "3. Evaluate the Polynomial" << endl;
  cout << "4. Exit Object Double Linked List" << endl;
  cin  >> selection; 
  ThePoly = new TermDblLinkList;
  ThePoly->readIntoList(filename);
  switch(selection)
        { case '1':
	  {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printIteratively();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
	  }
          case '2':
  	  {
	    auto begin = std::chrono::high_resolution_clock::now();
            ThePoly->printRecursively();
            auto end = std::chrono::high_resolution_clock::now();

	    auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
	    cout << "It took " << ticks.count() << " microseconds.\n";
            break;
	  }
	  case '3':
	    evalPoly(ThePoly);
	    break;
          case '4':
            menu = false;
            delete ThePoly;
            break;
          default:
            cout<<"I cannot understand "<<selection<<".  Try again."<<endl;
            break;
	}
  }
}
// In batch mode print all the objects iteratively and evaluate
void printEverything(const string &filename,TermList *ThePoly, double evalX)
{ auto begin = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now(); 
  auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  std::ofstream out; 
  out.open("data.txt", std::ios_base::app);
  // Array 
  ThePoly=new TermArrayList;
  ThePoly->readIntoList(filename);
  for (int i = 0; i < 10; i++)
  { 
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printIteratively();
  end = std::chrono::high_resolution_clock::now(); 
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  }
  for (int i = 0; i< 10; i++)
  {
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printPtr();
  end = std::chrono::high_resolution_clock::now();
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  }
  for (int i = 0; i < 10; i++)
  {
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printRecursively();
  end = std::chrono::high_resolution_clock::now();
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  cout << "P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
  out << ticks.count() << endl;
  }
  // Vector
  ThePoly = new TermVectorList; 
  ThePoly->readIntoList(filename);
  for (int i = 0; i < 10; i++)
  {
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printIteratively();
  end = std::chrono::high_resolution_clock::now();
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  }
  for (int i = 0; i < 10; i++)
  {
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printRecursively();
  end = std::chrono::high_resolution_clock::now();
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  cout << "P(" << evalX << ")=" << (*ThePoly)(evalX) << endl << endl;
  }
  
  // Double Link List
  ThePoly=new TermDblLinkList;
  ThePoly->readIntoList(filename);
  for (int i = 0; i < 10; i++)
  {
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printIteratively();
  end = std::chrono::high_resolution_clock::now();
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  }
  for (int i = 0; i < 10; i++)
  {
  begin = std::chrono::high_resolution_clock::now();
  ThePoly->printRecursively();
  end = std::chrono::high_resolution_clock::now();
  ticks = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "It took " << ticks.count() << " microseconds.\n";
  cout << "P(" << evalX << ")=" << (*ThePoly)(evalX) << endl;
  out << ticks.count() << endl;
  }
}

// Computes P(x) for variable x, supplied by the user
void evalPoly(TermList *ThePoly)
{ double x;
  cout << "Enter a value x for P(x) >";
  cin >> x;
  cout << "P(" << x << ")=" << (*ThePoly)(x) << endl;
}  
