/************************************************************/
/* Author: Dr. Spiegel 					    */
/* Creation Date: Unknown 				    */
/* Updater: Bryce Andress                                   */
/* Updated: October 20, 2016                                */
/* Due Date: October 20, 2016 				    */
/* Course: CSC237 					    */
/* Professor Name: Dr. Spiegel				    */
/* Assignment: #2					    */
/* Filename: DblLink.h 					    */
/* Purpose:  This is the header file that defines functions */
/* for a doubly linked list object                          */
/************************************************************/

#ifndef _DblLinkedList_
#define _DblLinkedList_

#include <assert.h>
#include <iostream>
#include "Node.h"
#include "DblLinkItr.h"

using namespace std;

template <typename eltType> class DblLinkedList;

template <typename eltType> class DblLinkedList
{
	public:
		DblLinkedList();
		DblLinkedList(const DblLinkedList&);
		~DblLinkedList();
		DblLinkedList& operator=(const DblLinkedList&);
		bool empty();
		bool find(eltType);
		void insert(eltType);
		void remove(eltType);
		void printForwards();
		Node<eltType>* head;
		Node<eltType>* copy(Node<eltType> *);
		void destroy(Node<eltType> *);
	friend class DblLinkItr<eltType>;
	friend class Node<eltType>;
};

/*************************************************************************/
/* Function name: Constructor                                            */
/* Description: Initializes the DblLinkedList object                     */
/* Parameters: none 							 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> DblLinkedList<eltType>::DblLinkedList() : head(NULL)
{}

/*************************************************************************/
/* Function name: Constructor                                            */
/* Description: Initializes the DblLinkedList object and copies another  */
/* DblLinkedList to it.                                                  */
/* Parameters: DblLinkedList this is the list to copy data from 	 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> DblLinkedList<eltType>::DblLinkedList(const DblLinkedList<eltType>& cl)
{
	Node<eltType>* p = cl;
	head = p;
	while (cl->data != NULL)
	{
		p = p;
		p = p-> next;	
	}
}	
/*************************************************************************/
/* Function name: Destructor                                             */
/* Description: Destroys the DblLinkedList object                        */
/* Parameters: none 							 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> DblLinkedList<eltType>::~DblLinkedList()
{destroy(head);}

/*************************************************************************/
/* Function name: = Operator                                             */
/* Description: Destroys the DblLinkedList object and assigns it to      */
/* another								 */
/* Parameters: none							 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> DblLinkedList<eltType>
	&DblLinkedList<eltType>::operator=(const DblLinkedList<eltType>& cl)
{	if (this != &cl)
	{	destroy(head);
		head = copy(cl.head);
	}
	return *this;
}

/*************************************************************************/
/* Function name orderedInsert                                          */
/* Description: Insert an eltType into the correct position in list      */
/* Parameters: eltType x - Put this in list - inputi			 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType>
		void DblLinkedList<eltType>::insert(eltType x)
{	if (empty())
	{
		head=new Node<eltType>(x, NULL, NULL);
	}
	// If insert is first elt
	else if (x < head->data)
	{
		head = new Node<eltType>(x, NULL, head);
		head->next->prev = head;
	}
	// If it is any other elt
	else
	{	Node<eltType>* p = head; 
		Node<eltType>* pPrev = head -> prev; //Null
		// Move to position
		while (p != NULL && x > p->data)
		{	pPrev = p;
			p = p->next;
		}
		// If last
		if (p == NULL)
		{
			p = new Node<eltType>(x,pPrev,NULL);
			pPrev->next = p;
		}
		// Any other
		else
		{ pPrev->next = new Node<eltType>(x,pPrev, p);
		  p->prev = pPrev->next;
		}

	}

}

/*************************************************************************/
/* Function name: empty                                                  */
/* Description: Remove all elements from list                            */
/* Parameters: none                                           		 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> inline bool DblLinkedList<eltType>::empty()
{return (head==NULL);}

/*************************************************************************/
/* Function name: remove                                                 */
/* Description: Remove an element from the list                          */
/* Parameters: eltType x - Remove this from list - input		 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> void DblLinkedList<eltType>::remove(eltType x)
{	if (empty())
	{
		cout << "Cannot delete from empty list.\n";
		return;
	}
	Node<eltType>* p = head;
	Node<eltType>* pPrev = head;
	// Move into position
	while (p->next != NULL && p->data != x )
	{
		pPrev = p;
		p = p->next;
	}

	//If first elt
	if (p == head)
	{
		if (head->next == NULL)
			head = NULL;
		else
		{
			head = head->next;
			head -> prev = NULL;
		}
		delete p;
		return;
	}

	//If not last elt	
	else if (p->next != NULL)
	{
		pPrev->next = p->next;
		p->next->prev = pPrev;
		delete p;
		return;
	}

	//If last elt and data is there
	else if (p->next == NULL && p->data == x)	
	{
		delete p;
		pPrev->next= NULL;
		return;
	}

	else
	{
		cout << "Number not in list.\n";
		return;
	}
	

}

/*************************************************************************/
/* Function name: destroy                                                */
/* Description: Destroy the list 		                         */
/* Parameters: Node<eltType> - Remove this node from list - input 	 */
/* Return Value: none                                                    */
/*************************************************************************/
template <typename eltType> void DblLinkedList<eltType>::destroy(Node<eltType> *l)
{	while (l != NULL)
	{	Node<eltType> *doomed = l;
		l = l-> next;
		delete doomed;
	}
}

#endif
