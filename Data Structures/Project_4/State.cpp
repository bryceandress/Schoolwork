/// File:		State.cpp
/// Description:	Implementation file for class State member functions;
///	This is an incomplete version that carries out the basic read and print 
/// 	functions. Due to the limited functionality, the usual member functions 
///	have been left out.

#include <iostream>
#include <iomanip>
#include "Date.h"
#include "State.h"

using namespace std;

/// default constructor
State::State()
{
    stateName=stateCapital="";
    popDensity=0;
    popRank=areaRank=0;
    admittOrder=totalPop=area=0;
}

///function returns a state's population  
long State::getPop()
{  return(totalPop);  }
///function returns a state's name
string State::getState()
{  return(stateName);  }
///function returns a state's capital
string State::getCapital()
{  return(stateCapital);  }
///function returns the area
long State::getArea()
{  return(area); }
/// function returns the date
Date State::getDate()
{  return(AdmDate);  }
/// function returns the order of admittance
int State::getAdmittOrder()
{  return(admittOrder); }

/// operator overloading for a state name and attribute input
istream &operator>>(istream &Source,  State &s)
{
	int mm, dd, yyyy;	///month, day, and year of admission
	char nullToken;		///gets the space before the capital
	getline(Source,s.stateName);
	
	Source>>s.totalPop >> s.popRank >> s.popDensity;
	Source>>s.area>>s.areaRank>>mm>>dd>>yyyy;
	s.AdmDate.setDate(mm,dd,yyyy);
	
	Source>>s.admittOrder;

	Source.get(nullToken);	///used to get the blank before the stateCapital

	getline (Source, s.stateCapital);
	string dummy;
	for (int i=0;i<5;i++)
          getline(Source,dummy);

	return Source;
}

/// compare state names (for sorting)
bool State::operator<(State s) const
{	return (stateName < s.stateName);	}

/// check for equality of state name and a key
bool State::operator==(string searchTerm)
{	return (stateName == searchTerm);	}

/// check for equality of state name and another State
bool State::operator==(State searchTerm)
{	return (stateName == searchTerm.stateName);	}

/// Is the state name large than the key?
bool State::operator>(string searchTerm)
{	return (stateName  > searchTerm);	}

/// operator overload for state name and attribute output
ostream &operator<<(ostream &Destination, const State &s)
{
  Destination.setf(ios::left);
  Destination<<endl<<s.stateName<<endl;
  Destination<<setw(10)<<"Captial: "<<s.stateCapital<<endl;
  Destination<<setw(13)<<"Population(1990): ";
  Destination.unsetf(ios::left);

  Destination<<setw(9)<<s.totalPop;

  Destination.setf(ios::left);
  Destination<<setw(3)<<"  Rank:";
  Destination.unsetf(ios::left);

  Destination<<setw(4)<<s.popRank;

  Destination.setf(ios::left);
  Destination<<"  Density: ";
  Destination.unsetf(ios::left);

  Destination<<setw(7)<<s.popDensity<<
			" people/square mile"<<endl;
	
  Destination.setf(ios::left);
  Destination<<setw(10)<<"Area:"<<setw(7)<<s.area;
  Destination.unsetf(ios::left);

  Destination<<setw(17)<<"Rank:"<<setw(4)<<s.areaRank<<endl;

  Destination.setf(ios::left);
  Destination<<setw(10)<<"Admitted:";

  Destination.unsetf(ios::left);

  Destination<<s.AdmDate;
  Destination<<" Order:"<<setw(3)<<s.admittOrder<<endl;  

  return Destination;}
