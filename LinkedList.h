#pragma once

#include <iostream>

using namespace std;


template <typename T>
struct NodeType
{
	T data;						//A data for each node.
	NodeType* next;				//A node pointer to point succeed node.
};


template <typename T>
class LinkedList
{
private:
	NodeType<T>* m_List;		//Pointer for pointing a first node.
	NodeType<T>* m_CurPointer;	//Node pointer for pointing current node to use iteration.
	int m_Length;				//Number of node in the list.

public:
	/**
	*	default constructor.
	*/
	LinkedList();


	/**
	*	destructor.
	*/
	~LinkedList();


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
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& inData);


	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();


	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	void GetNextItem(T& inData);


	/**
	*	@brief	Delete item from this list.
	*	@pre	List should be intialized.
	*	@post	Delete selected item.
	*   @return 1 if this function works well, otherwise 0.
	*/
	int Delete(T inData);


	/**
	*	@brief	Replace item into this list.
	*	@pre	List should be intialized.
	*	@post	Replace selected item.
	*   @return 1 if this function works well, otherwise 0.
	*/
	int Replace(T inData);


	/**
	*	@brief  Get the current address pointed by iterator.
	*	@pre	List should be intialized.
	*	@post	None.
	*   @return Return the current address pointed by iterator.
	*/
	T* GetCurPointer();


	/**
	 @brief  Check capacity of list is empty.
	 @pre    None.
	 @post   None.
	 @return Return true if list capacity reached to the bottom bound, otherwise return false.
	 */
	bool IsEmpty();


	/**
	 @brief  Check capacity of list is full.
	 @pre    None.
	 @post   None.
	 @return Return true if list capacity reached to the upper bound, otherwise return false.
	 */
	bool IsFull();


	/**
	*	@brief  Get the current node pointed by iterator.
	*	@pre	None.
	*	@post	None.
	*   @return Return the current node pointed by iterator.
	*/
	NodeType<T> GetCurNode();
};


template<typename T>
NodeType<T> LinkedList<T>::GetCurNode() {

	if (m_CurPointer != NULL) {
		return *m_CurPointer;
	}
}


template <typename T>
LinkedList<T>::LinkedList()
{
	m_Length = 0;
	m_List = NULL;
	m_CurPointer = NULL;
}


template <typename T>
T* LinkedList<T>::GetCurPointer() {
	if (m_CurPointer != NULL) {
		return &(m_CurPointer->data);
	}
	else {
		return NULL;
	}
}


template <typename T>
LinkedList<T>::~LinkedList()
{
	MakeEmpty();
}


template <typename T>
void LinkedList<T>::MakeEmpty()
{
	NodeType<T>* tempPtr;

	while (m_List != NULL)
	{
		tempPtr = m_List;
		m_List = m_List->next;
		delete tempPtr;
	}

	m_Length = 0;

	return;
}


template <typename T>
int LinkedList<T>::GetLength() const
{
	return m_Length;
}


template <typename T>
int LinkedList<T>::Add(T inData)
{
	ResetList();

	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	T tempData;

	node->data = inData;
	node->next = NULL;

	if (!m_Length) {
		m_List = node;
	}
	else {
		while (1)
		{
			pre = m_CurPointer;
			GetNextItem(tempData);

			if (node->data < tempData) {
				node->next = m_CurPointer;

				if (pre == NULL) {
					m_List = node;
				}
				else {
					pre->next = node;
				}
				break;
			}
			if (m_CurPointer->next == NULL) {
				m_CurPointer->next = node;
				break;
			}
		}
	}

	m_Length++;

	return 1;
}


template <typename T>
int LinkedList<T>::Get(T& inData)
{
	bool moreToSearch;
	bool isFind;
	NodeType<T>* location;

	location = m_List;
	isFind = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !isFind)
	{
		if (inData == location->data)
		{
			isFind = true;
			inData = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (isFind) {
		return 1;
	}
	else {
		return 0;
	}
}


template <typename T>
void LinkedList<T>::ResetList()
{
	m_CurPointer = NULL;

	return;
}


template <typename T>
void LinkedList<T>::GetNextItem(T& inData)
{
	if (m_CurPointer == NULL)
	{
		if (m_List != NULL) {
			m_CurPointer = m_List;
		}
		else {
			return;
		}
	}
	else {
		m_CurPointer = m_CurPointer->next;
	}

	inData = m_CurPointer->data;

	return;
}


template <typename T>
int LinkedList<T>::Delete(T inData) {
	if (m_Length == 0 || (!Get(inData))) {
		return 0;
	}
	else {
		ResetList();
		NodeType<T> *pre;
		T temp;
		while (1)
		{
			pre = m_CurPointer;
			GetNextItem(temp);

			if (inData == temp)
			{
				if (pre == NULL) {
					m_List = m_CurPointer->next;
					m_Length--;
					return 1;
				}
				else {
					pre->next = m_CurPointer->next;
					m_Length--;
					return 1;
				}
				break;
			}
		}
		return 0;
	}
}


template <typename T>
int LinkedList<T>::Replace(T inData) {
	m_CurPointer->data = inData;

	return 1;
}


template <typename T>
bool LinkedList<T>::IsEmpty() {
	if (m_List == NULL) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
bool LinkedList<T>::IsFull() {
	NodeType<T> *temp;

	try {
		temp = new NodeType<T>;
		delete temp;
		return false;
	}
	catch (bad_alloc exception) {
		return true;
	}
}