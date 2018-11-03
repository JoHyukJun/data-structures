#pragma once

#include <iostream>
#include "DoublyIterator.h"

using namespace std;


/**
*		template reference error prevention.
*/
template <typename T>
class DoublyIterator;


template <typename T>
struct DoublyNodeType {
	T data;
	DoublyNodeType* pre;
	DoublyNodeType* next;
};


template <typename T>
class DoublyLinkedList
{
	friend class DoublyIterator<T>;

private:
	DoublyNodeType<T>* m_First;
	DoublyNodeType<T>* m_Last;
	int m_Length;

public:
	/**
	*	default constructor.
	*/
	DoublyLinkedList();


	/**
	*	destructor.
	*/
	~DoublyLinkedList();


	/**
	*	@brief	Determines whether the list is full.
	*	@pre	List has been initialized.
	*	@post	None.
	*	@return	If there is not memory left, throws bad_alloc exception and return true, otherwise false.
	*/
	bool IsFull();


	/**
	*	@brief	Determines whether the list is empty.
	*	@pre	List has been initialized.
	*	@post	None.
	*	@return	Return true if the list is empty, otherwise false.
	*/
	bool IsEmpty();


	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();


	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;


	/**
	*	@brief	Add item into this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T inData);


	/**
	*	@brief	Delete item from this list.
	*	@pre	List has been initialized.
	*	@post	Item is deleted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Delete(T inData);


	/**
	*	@brief	Replace item from this list.
	*	@pre	List has been initialized.
	*	@post	Item is replaced in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T inData);


	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& inData);
};


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	m_Length = 0;
	m_First = nullptr;
	m_Last = nullptr;
}


template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	MakeEmpty();
}


template <typename T>
bool DoublyLinkedList<T>::IsFull() {
	try {
		DoublyNodeType<T>* temp = NULL;
		delete temp;

		return false;
	}
	catch (bad_alloc& err) {
		cerr << "bad_alloc exception capture : " << err.what() << endl;

		return true;
	}
}


template <typename T>
bool DoublyLinkedList<T>::IsEmpty() {
	if (m_First == NULL) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
void DoublyLinkedList<T>::MakeEmpty() {
	DoublyNodeType<T>* tempPtr;
	DoublyIterator<T> tempItr(*this);

	while (tempItr.NotNull()) {
		tempPtr = tempItr.m_CurPointer;
		tempItr.Next();

		delete tempPtr;
	}

	m_Length = 0;
}


template <typename T>
int DoublyLinkedList<T>::GetLength() const {
	return m_Length;
}


template <typename T>
int DoublyLinkedList<T>::Add(T inData) {
	if (IsFull()) {
		return 0;
	}
	else {
		DoublyNodeType<T>* tempPtr = new DoublyNodeType<T>;
		DoublyIterator<T> tempItr(*this);

		tempPtr->data = inData;
		tempPtr->pre = NULL;
		tempPtr->next = NULL;

		if (m_First == NULL) {
			m_First = tempPtr;
			m_Last = m_First;
		}
		else {
			DoublyNodeType<T>* tempCurPtr;

			while (tempItr.NotNull()) {
				tempCurPtr = tempItr.m_CurPointer;

				if (tempPtr->data < tempCurPtr->data) {
					tempPtr->next = tempCurPtr;

					if (m_Length == 1) {
						m_First = tempPtr;
					}
					else {
						tempPtr->pre = tempCurPtr->pre;
						tempPtr->pre->next = tempPtr;
					}

					tempCurPtr->pre = tempPtr;

					break;
				}
				else {
					if (!tempItr.NextNotNull()) {
						tempCurPtr->next = tempPtr;
						tempPtr->pre = tempCurPtr;
						m_Last = tempPtr;

						break;
					}
					else {
						tempItr.Next();
					}
				}
			}
		}

		m_Length++;

		return 1;
	}
}


template <typename T>
int DoublyLinkedList<T>::Delete(T inData) {
	int tempIndex = Get(inData);
	DoublyNodeType<T>* tempPtr = m_First;
	
	if (tempIndex) {
		for (int i = 1; i < tempIndex; i++) {
			tempPtr = tempPtr->next;
		}

		if (tempPtr->next != NULL) {
			tempPtr->next->pre = tempPtr->pre;
		}
		else {
			m_Last = tempPtr->pre;
		}

		if (tempPtr->pre != NULL) {
			tempPtr->pre->next = tempPtr->next;
		}
		else {
			m_First = tempPtr->next;
		}

		delete tempPtr;
		m_Length--;

		return 1;
	}
	else {
		return 0;
	}
}


template <typename T>
int DoublyLinkedList<T>::Replace(T inData) {
	int tempIndex = Get(inData);
	T temp = inData;
	DoublyNodeType<T>* tempPtr = m_First;

	for (int i = 1; i < tempIndex; i++) {
		tempPtr = tempPtr->next;
	}

	tempPtr->data = inData;

	return 1;
}


template <typename T>
int DoublyLinkedList<T>::Get(T& inData) {
	int count = 0;
	bool isFind = false;
	DoublyIterator<T> tempItr(*this);

	while (tempItr.NotNull()) {
		count++;

		if (inData == tempItr.GetCurNode().data) {
			inData = tempItr.GetCurNode().data;
			isFind = true;

			break;
		}
		else if (inData < tempItr.GetCurNode().data) {
			break;
		}
		else {
			tempItr.Next();
		}
	}

	if (isFind) {
		return count;
	}
	else {
		return 0;
	}
}