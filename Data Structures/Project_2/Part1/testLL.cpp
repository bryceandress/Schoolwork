/************************************************************/
/* Author: Bryce Andress				    */
/* Creation Date: October 20, 2016			    */
/* Due Date: October 20, 2016				    */
/* Course: CSC237					    */
/* Professor Name: Dr. Spiegel				    */
/* Assignment: #2					    */
/* Filename: testLL.cpp 				    */
/* Purpose: This program can add elemets to a doubly linked */
/* list. It can print the list forwards and backwards, and  */
/* it can also delete elements from the list. 		    */
/************************************************************/
#include <iostream>
#include "DblLinkItr.h"
#include "DblLink.h"

using namespace std;
void addTerm(DblLinkedList<int>&);
void printForwards(DblLinkedList<int>&);
void printBackwards(DblLinkedList<int>&);
void removeTerm(DblLinkedList<int>&);
int main()
{
	int choice = 0;
	DblLinkedList<int> termList;
	while (choice != 5)
	{
		cout << "1: Add a Term \n";
		cout << "2: Remove a Term \n";
		cout << "3: Print Forwards \n";
		cout << "4: Print Backwards \n";
		cout << "5: Exit \n";
		cin >> choice;

		switch(choice)
		{
		case 1 :
			addTerm(termList);
			break;
		case 3 :
			printForwards(termList);
			break;
		case 4 :
			printBackwards(termList);
			break;
		case 2 :
			removeTerm(termList);
			break;
		}
	}
	return 0;
}

/*************************************************************************/
/* Function name: addTerm 						 */
/* Description: Adds a term/element to the double linked list. 		 */
/* Parameters: termList - List to add element to			 */
/* Return Value: none							 */
/*************************************************************************/
void addTerm(DblLinkedList<int>& termList)
{
	int term;
	cout << "Enter a Term to add: ";
	cin >> term;
	termList.insert(term);
}

/*************************************************************************/
/* Function name: printForwards						 */
/* Description: Print the double linked list forwards 	 		 */
/* Parameters: termList - List to add element to			 */
/* Return Value: none							 */
/*************************************************************************/
void printForwards(DblLinkedList<int>& termList)
{
	DblLinkedItr<int> termListItr(termList);
	if(termListItr.isEmpty()) {
		cout << "empty list" << endl;
		return;
	}
        while (!termListItr.isLastNode())
        { 
		cout << termListItr() << " ";
		++termListItr;
        }
	cout << termListItr();
        cout << endl;	
}

/*************************************************************************/
/* Function name: printBackwards					 */
/* Description: Print the double linked list backwards 	 		 */
/* Parameters: termList - List to add element to			 */
/* Return Value: none							 */
/*************************************************************************/
void printBackwards(DblLinkedList<int>& termList)
{
	DblLinkedItr<int> termListItr(termList);
	if(termListItr.isEmpty()) {
		cout << "Empty List" << endl;
		return;
	}
	while (!termListItr.isLastNode())
	{ ++termListItr; }

	while (!termListItr.isFirstNode())
	{ cout << termListItr() << " " ;
	  --termListItr;
	}
	
	cout << termListItr();
	cout << endl;
}

/*************************************************************************/
/* Function name: removeTerm						 */
/* Description: Remove an element from the double linked list  		 */
/* Parameters: termList - List to add element to			 */
/* Return Value: none							 */
/*************************************************************************/
void removeTerm(DblLinkedList<int>& termList)
{
	int term;
	cout << "Enter a Term to remove: ";
	cin >> term;
	termList.remove(term);
}

