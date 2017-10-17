/**************************************************
* Bryce Andress
* CS237
* Purpose: Read in the states file and have the 
* ability to print it, reorder it, list what letters
* have a state with that letter in the name, as well
* as capitals, also be able to search for a State and
* print its info
**************************************************/
/*!
\mainpage Read in the states file and have the ability to print it, reorder it, list what letters have a state with that letter in the name, as well as capitals, also be able to search for a State and print its info.
*/ 
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include "Date.h"
#include "State.h"

using namespace std;

/// Struct Name: capitalOrder
/// Sort the States by Capital
struct capitalOrder
{  
		bool operator()(State state1, State state2) {
			return (state1.getCapital() < state2.getCapital());
		}
} capitalOrder;

/// Struct Name: stateOrder
/// Sort the States by State 
struct stateOrder
{  
               bool operator()(State state1, State state2) {
                        return (state1.getState() < state2.getState());
               } 
} stateOrder;
                                                          
/// Struct Name: popOrder
/// Sort the States by population 
struct popOrder
{
        public:
                bool operator()(State state1, State state2) const {
                        if (state1.getPop() > state2.getPop())
                                return true;
                        else
                                return false;
                }
} popOrder;

/// Struct Name: areaOrder
/// Sort the States by area 
struct areaOrder
{
        public:
                bool operator()(State state1, State state2) const {
                        if (state1.getArea() < state2.getArea())
                                return true;
                        else
                                return false;
                }
} areaOrder;

/// Struct Name: dateOrder
/// Sort the States by date of admission 
struct dateOrder
{
        public:
                bool operator()(State state1, State state2) {
                        if (state1.getAdmittOrder() < state2.getAdmittOrder())
                                return true;
                        else
                                return false;
                }
} dateOrder;

/*!
 * Function Name: readInState
 * Description: Read in States from the States file
 * \param vector<State> stateVec
 * \return stateVec
 */
vector<State> readInState(vector<State> &stateVec)
{ 
  fstream infile("States.data.txt");
  State tempState;
  while (infile >> tempState)
  {
    stateVec.push_back(tempState);
  }
  sort(stateVec.begin(), stateVec.end()); 
  return stateVec;
}

/*!
 * Function Name: print 
 * Description: Print all the states
 * \param vector<State> stateVec
 */
void print(vector<State> &stateVec)
{
  for (int iter = 0; iter < stateVec.size(); iter++)
  {
    cout << stateVec[iter] << endl;  
  }
}

/*!
 * Function Name: stateSearch 
 * Description: Create a multipmap of a Char and a String. Have each state added
 * to a pair of char if it has a letter of that char
 * \param vector<State> stateVec
 */
void stateSearch(vector<State> &stateVec)
{
  char letter;
  cout << "Enter Letter: ";
  cin  >> letter;
  cin.ignore();
  letter = toupper(letter);
  multimap<char, string> state;
  // check the logic for capitalSearch
  for (int vecIter = 0; vecIter < stateVec.size(); vecIter++)
  {
    string name;
    name = stateVec[vecIter].getState();
    for (int sIter = 0; sIter < name.size(); sIter++) 
    {
      multimap<char, string>::iterator itr;
      for(itr = state.begin(); itr != state.end(); itr++)
      {
	if(itr->first == name[sIter])
          if(itr->second == name)
	    break;
      }
      if(itr == state.end())
        state.insert(pair<char, string>(name[sIter], name));
    } 
  }

  pair<multimap<char, string>::iterator, multimap<char, string>::iterator> ppp;
  ppp = state.equal_range(letter);
  cout << "[" << letter << ": ";
  for(multimap<char, string>::iterator it2 = ppp.first; it2 != ppp.second; ++it2)
  {
    cout << it2->second << ",";
  }
  cout << "]" << endl;
}

/*!
 * Function Name: capitalSearch 
 * Description: Create a multipmap of a Char and a String. Have each capital added
 * to a pair of char if it has a letter of that char
 * \param vector<State> stateVec
 */
void capitalSearch(vector<State> &stateVec)
{
  char letter;
  cout << "Enter Letter: ";
  cin >> letter;
  cin.ignore();
  letter = toupper(letter);
  multimap<char, string> state;
  // go thru whole vector
  for (int vecIter = 0; vecIter < stateVec.size(); vecIter++)
  {
    string name;
    name = stateVec[vecIter].getCapital();
    // go thru the whole state name
    for (int sIter = 0; sIter < name.size(); sIter++) 
    {
      multimap<char, string>::iterator itr;
      // for each letter in the state (may be redundant???)
      for(itr = state.begin(); itr != state.end(); itr++)
      {
	// is the letter in the map?
	if(itr->first == name[sIter])
	  // is the state name matched to that letter?
          if(itr->second == name)
	    // if so get out of here
	    break;
      }
      // if those conditions were not met add the state
      if(itr == state.end())
        state.insert(pair<char, string>(name[sIter], name));
    }
  }
  pair<multimap<char, string>::iterator, multimap<char, string>::iterator> ppp;
  ppp = state.equal_range(letter);
  cout << "[" << letter << ": ";
  for(multimap<char, string>::iterator it2 = ppp.first; it2 != ppp.second; ++it2)
  {
    cout << it2->second << ",";
  }
  cout << "]" << endl;
}

/*!
 * Function Name: letterSearch 
 * Description: Prompt the user if they want to go back, call stateSearch
 * or call capitalSearch 
 * \param vector<State> stateVec
 */
void letterSearch(vector<State> &stateVec)
{
  char letter;
  while (true)
  {
    cout << "Select Letter in " << endl;
    cout << "N)ame of State " << endl;
    cout << "C)apital" << endl;
    cout << "G)o back" << endl;
    cin >> letter;
    cin.ignore();
    letter = toupper(letter);
    switch(letter)
    {
      { case 'N':
        {
          stateSearch(stateVec);
          break;
        }
        case 'C':
        {
          capitalSearch(stateVec);
	  break;
        }
        case 'G':
	  return;
        default:
          cout << "Please enter a correct option." << endl; 
      } 
    }
  }  
}

/*!
 * Function Name: nameSearch 
 * Description: Search for a state, if found print that states info
 * \param vector<State> stateVec
 */
void nameSearch(vector<State> &stateVec)
{
  string state; 
  cout << "Enter Name of State: ";
  getline(cin, state); 
  transform(state.begin(), state.end(), state.begin(), ::toupper); 
  vector<State>::iterator it = find(stateVec.begin(), stateVec.end(), state);
  if (it != stateVec.end())
    cout << *it << endl;
  return;
}

/*!
 * Function Name: reorder 
 * Description: Helper function to decide how to reorder the vector 
 * \param vector<State> stateVec
 */
void reorder(vector<State> &stateVec)
{
  char letter;
  while (true)
  {
    cout << "Select Letter in " << endl;
    cout << "N)ame" << endl;
    cout << "C)apital" << endl;
    cout << "P)opulation" << endl;
    cout << "A)rea" << endl;
    cout << "D)ate of Admission" << endl;
    cout << "G)o back" << endl;
    cin >> letter;
    cin.ignore();
    letter = toupper(letter);
    switch(letter)
    {
      { case 'N':
        {
          sort(stateVec.begin(), stateVec.end());
          break;
        }
        case 'C':
        {
          sort(stateVec.begin(), stateVec.end(), capitalOrder);
	  break;
        }
	case 'P':
	  sort(stateVec.begin(), stateVec.end(), popOrder );
          break;
	case 'A':
	  sort(stateVec.begin(), stateVec.end(), areaOrder );
	  break;
        case 'D':
          sort(stateVec.begin(), stateVec.end(), dateOrder );
          break;
        case 'G':
	  return;
        default:
          cout << "Please enter a correct option." << endl; 
      } 
    }
  } 
}

/*!
 * Function Name: mainMenu 
 * Description: Helper function to prompt the user what to do
 * \param vector<State> stateVec
 */
void mainMenu(vector<State> &stateVec)
{
  char selection;
  while(true)
  {
    cout << "Select: " << endl;
    cout << "P)rint "  << endl;
    cout << "L)etter Search " << endl;
    cout << "N)ame Search   " << endl;
    cout << "R)eorder Search " << endl;
    cout << "Q)uit "	<< endl;

    cin >> selection;
    cin.ignore();
    selection = toupper(selection);
    switch(selection)
    {
      { case 'P':
        {
          print(stateVec);
	  break;
        }
        case 'L':
        {
	  letterSearch(stateVec);
          break;
        }
        case 'N':
        {
	  nameSearch(stateVec);
	  break;
        }
        case 'R':
        {
	  reorder(stateVec);
	  break;
        }
        case 'Q':
        {
          return;
        }
        default:
        {
	  cout << "Please enter a correct prompt." << endl;
        }
      }
    }
  } 
}

/*!
 * Function Name: main 
 * Description: start the program 
 */
int main()
{
  vector<State> stateVec;
  stateVec = readInState(stateVec);
  mainMenu(stateVec);
}
