#pragma once

#include "DoublyLinkedList.h"

/**
*		template reference error prevention. 
*/
template <typename T>
class DoublyLinkedList;


/**
*		template reference error prevention.
*/
template <typename T>
struct DoublyNodeType;


template <typename T>
class DoublyIterator
{
	friend class DoublyLinkedList<T>;

private:
	const DoublyLinkedList<T>& m_List;		//The reference variable of list.
	DoublyNodeType<T>* m_CurPointer;		//Node pointer for pointing current node to use iteration.

public:
	/**
	*	default constructor.
	*/
	DoublyIterator();


	/**
	*	custom constructor.
	*/
	DoublyIterator(const DoublyLinkedList<T>& inList) : m_List(inList), m_CurPointer(inList.m_First) {}


	/**
	*	destructor.
	*/
	~DoublyIterator();


	/**
	*	@brief	Determine if the pointer th the current node is null.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	NULL true, otherwioze false.
	*/
	bool NotNull();


	/**
	*	@brief	Determine if the next node in the current node pointer is null.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	NULL true, otherwioze false.
	*/
	bool NextNotNull();


	/**
	*	@brief	Get the first data of the list.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved th the frist node.
	*	@return	Return the first data of the list.
	*/
	T First();


	/**
	*	@brief	Get the next data of the list.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved th the next node.
	*	@return	Return the next data of the list.
	*/
	T Next();


	/**
	*	@brief	Get the current data of the list and go th the next node.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved th the next node.
	*	@return	Return the first  data of the list.
	*/
	DoublyNodeType<T> GetCurNode();
};


template <typename T>
DoublyIterator<T>::DoublyIterator() {

}


template <typename T>
DoublyIterator<T>::~DoublyIterator() {

}


template <typename T>
bool DoublyIterator<T>::NotNull() {
	if (m_CurPointer == NULL) {
		return false;
	}
	else {
		return true;
	}
}


template <typename T>
bool DoublyIterator<T>::NextNotNull() {
	if (m_CurPointer->next == NULL) {
		return false;
	}
	else {
		return true;
	}
}


template <typename T>
T DoublyIterator<T>::First() {
	if (m_List.IsEmpty()) {
		m_CurPointer = m_List.m_First;

		return m_CurPointer->data;
	}
}


template <typename T>
T DoublyIterator<T>::Next() {
	T temp = m_CurPointer->data;

	if (NotNull()) {
		m_CurPointer = m_CurPointer->next;
	}

	return temp;
}


template <typename T>
DoublyNodeType<T> DoublyIterator<T>::GetCurNode() {
	if (m_CurPointer != NULL) {
		return *m_CurPointer;
	}
}