/// File: 	State.h
/// Description: State class holds all information for a single state

#ifndef H_stateClass
#define H_stateClass

#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

class State
{

public:
	State();			///basic constructor
        string getState();		///get state
	string getCapital();		///get capital
	long getArea();			///get area
	Date getDate();			///get date
        int getAdmittOrder();		///get admittance order
	bool operator<(State) const;	///compare state names
	bool operator>(string);		///compare state name and key
	bool operator==(string);	///compare for state name and 
					///key equality on State and string
	bool operator==(State);		///compare for state name and 
					///key equality on States

	long getPop();

private:

	Date   AdmDate;
	string stateName, stateCapital;
	int    popRank, areaRank, admittOrder;

	float popDensity;
	long area;
	int totalPop;

///output State objects
friend ostream &operator<<(ostream&, const State &s);

///input State objects
friend istream &operator>>(istream&, State &s);

};

///output State objects
ostream &operator<<(ostream&, const State &s);

///input State objects
istream &operator>>(istream&, State &s);

#endif
