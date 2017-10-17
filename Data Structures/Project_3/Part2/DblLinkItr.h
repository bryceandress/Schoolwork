/************************************************************
* Author: Bryce Andress				    *
* Creation Date: October 20, 2016			    *
* Due Date: October 20, 2016				    *
* Course: CSC237					    *
* Professor Name: Dr. Spiegel				    *
* Assignment: #2				       	    *
* Filename: DblLinkItr.h 				    *
* Purpose: This program is the definitions of the  	    *
* DblLinkItr class					    *
************************************************************/
#ifndef _DblLinkedItr_
#define _DblLinkedItr_
#include <assert.h>
#include <iostream>
#include "Node.h"
#include "DblLink.h"

using namespace std;

template <typename eltType> class DblLinkedItr
{
	public:
		DblLinkedItr(const DblLinkedList<eltType> &l);

		void start();
		void next();
		bool isEmpty();
		bool isLastNode();
		bool isFirstNode();
		eltType  operator()();
		void operator++();
		void operator--();
		
		eltType value();

	private:
		const DblLinkedList<eltType> &itr;
		Node<eltType> *curr;
};

/*!************************************************************************
* Function name: Constructor						 *
* Description: Creates a DblLinkedItr object 	  	 	 	 *
* \param DblLinkedList<eltType> List to have Itr object point at *
* \return none 							 *
*************************************************************************/
template <typename eltType>
DblLinkedItr<eltType>::DblLinkedItr(const DblLinkedList<eltType> &l): itr(l), 
								curr(l.head){}

/*!************************************************************************
* Function name: start 						 *
* Description: Sets curr to list head  	  	 	 	 *
* \param none							 *
* \return none 							 *
*************************************************************************/
template <typename eltType> void DblLinkedItr<eltType>::start(void)
{curr = itr.head;}

/*!************************************************************************
* Function name: next	 						 *
* Description: Sets curr to next element in list  	 	 	 *
* \param none							 *
* \return none 							 *
*************************************************************************/
template <typename eltType> void DblLinkedItr<eltType>::next(void)
{assert(curr != NULL);
 curr = curr->next;
}

/*!************************************************************************
* Function name: isEmpty 						 *
* Description: Checks to see if the list is emtpy  	 	 	 *
* \param none							 *
* \return bool 1 not emtpy, 0 empty				 *
*************************************************************************/
template <typename eltType> bool DblLinkedItr<eltType>::isEmpty(void)
{if (curr == NULL) 
	return true;
 else
	return false;
}

/*!************************************************************************
* Function name: isLastNode 						 *
* Description: Checks to see if curr is the last node 	 	 	 *
* \param none							 *
* \return bool 1 not last, 0 last				 *
*************************************************************************/
template <typename eltType> bool DblLinkedItr<eltType>::isLastNode(void)
{
 if (curr->next == NULL) 
	return true;
 else
	return false;
}

/*!************************************************************************
* Function name: isFirstNode 						 *
* Description: Checks to see if curr is the first node	 	 	 *
* \param none							 *
* \return bool - 1 not first, 0 first				 *
*************************************************************************/
template <typename eltType> bool DblLinkedItr<eltType>::isFirstNode(void)
{if (curr->prev == NULL)
	return true;
 else
	return false;
}

/*!************************************************************************
* Function name: value 						 *
* Description: Returns the value at the current node	 	 	 *
* \param none							 *
* \return Data stored in Node object				 *
*************************************************************************/
template <typename eltType> eltType DblLinkedItr<eltType>::value(void)
{assert( curr != NULL);
 return curr->data;
}

/*!************************************************************************
* Function name: operator()() 						 *
* Description: Returns the value at the current node	 	 	 *
* \param none							 *
* \return Data stored in Node object				 *
*************************************************************************/
template <typename eltType> eltType DblLinkedItr<eltType>::operator()()
{assert( curr != NULL);
 return curr->data;
}

/*!************************************************************************
* Function name: operator++() 						 *
* Description: Sets curr to the next node		 	 	 *
* \param none							 *
* \return none							 *
*************************************************************************/
template <typename eltType> void DblLinkedItr<eltType>::operator++ ()
{
	if (!isLastNode())
	{ curr = curr->next; }	
}

/*!************************************************************************
* Function name: operator--() 						 *
* Description: Sets curr to the prev node		 	 	 *
* \param none							 *
* \return none							 *
*************************************************************************/
template <typename eltType> void DblLinkedItr<eltType>::operator--()
{
	if (!isFirstNode())
	{ curr = curr->prev; }
}

#endif
