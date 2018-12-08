#pragma once


template <typename T>
class HeapBase
{
protected:
	T* m_Heap;
	int m_LastNode;
	int m_MasSize;

public:
	/**
	*	default constructor.
	*/
	HeapBase();


	/**
	*	destructor.
	*/
	virtual ~HeapBase();


	/**
	*	@brief	Check if the tree is empty.
	*	@pre	None.
	*	@post	None.
	*	@return	1 if tree is empty, otherwise 0.
	*/
	bool IsEmpty();


	/**
	*	@brief	Check if allocation is possible.
	*	@pre	None.
	*	@post	None.
	*	@return	1 if allocation is possible, otherwise 0.
	*/
	bool IsFull();


	/**
	*	@brief	Get number of elements in the tree.
	*	@pre	None.
	*	@post	Function value = number of elements in tree.
	*	@return	Number of elements in this tree.
	*/
	int GetLength() const;


	/**
	*	@brief	Initialize tree to empty state.
	*	@pre	None.
	*	@post	Tree is empty.
	*/
	void MakeEmpty();


	/**
	*	@brief	Add item into appropriate spot of this tree.
	*	@pre	Tree is not full. item is not in the tree.
	*	@post	Item is inserted into this tree.
	*/
	virtual int Add(T inData);


	/**
	*	@brief	Delete item from this tree.
	*	@pre	Tree is not empty. the item exists in tree.
	*	@post	Item is deleted from this tree.
	*/
	virtual int Delete(T inData);


	/**
	*	@brief	Delete item from this tree.
	*	@pre	Tree is not empty. the item exists in tree.
	*	@post	Item is deleted from this tree.
	*/
	virtual void Delete(T inData, bool& isFound, int inParent) = 0;


	/**
	*	@brief	Heap down.
	*	@pre	Root is the index of the node that may violate the heap order property.
	*	@post	Heap order property is restored between root and bottom.
	*/
	virtual void ReHeapDown(int inParent, int inBottom) = 0;


	/**
	*	@brief	Heap up.
	*	@pre	Bottom is the index of the node that may violate the heap order property. The order property is satisfied from root to next-to-last node.
	*	@post	Heap order property is restored between root and bottm.
	*/
	virtual void ReHeapUp(int inRoot, int inBottom) = 0;


	/**
	 @brief  Remove first item from the queue.
	 @pre    The queue should be initialized.
	 @post   If queue is empty, emptyqueue exception is thrown, otherwise first element has been removed from queue, item gets value of removed item.
	 */
	virtual T Dequeue();


	/**
	*	@brief	Retrieve tree element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@param	inData		data to find. Key member is initialized.
	*/
	virtual void Retrieve(T& inData, bool& isFound);


	/**
	*	@brief	Retrieve tree element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@param	inData		data to find. Key member is initialized.
	*/
	virtual void Retrieve(T& inData, bool& isFound, int inParent) = 0;


	/**
	*	@brief	Print all elements of the tree.
	*	@pre	None.
	*	@post	Every elements of the tree is printed.
	*/
	virtual void Print();


	/**
	*	@brief	Swap the items.
	*	@pre	Key member of item is initialized.
	*	@post	Change between the items.
	*/
	void Swap(int inParent, int inBottom);
};


template <typename T>
HeapBase<T>::HeapBase() {
	m_LastNode = 0;
}


template <typename T>
HeapBase<T>::~HeapBase() {
	MakeEmpty();
}


template <typename T>
bool HeapBase<T>::IsEmpty() {
	if (m_LastNode == 0) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
bool HeapBase<T>::IsFull() {
	if (m_LastNode == m_MasSize) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
int HeapBase<T>::GetLength() const {
	return m_LastNode;
}


template <typename T>
void HeapBase<T>::MakeEmpty() {
	delete[] m_Heap;

	return;
}


template <typename T>
int HeapBase<T>::Add(T inData) {
	m_Heap[m_LastNode] = inData;

	ReHeapUp(0, m_LastNode);

	m_LastNode++;

	return 1;
}


template <typename T>
int HeapBase<T>::Delete(T inData) {
	bool isFound = false;

	Delete(inData, isFound, 0);

	if (isFound) {
		m_LastNode--;
	}
	else {
		return 0;
	}

	return 1;
}

template <typename T>
T HeapBase<T>::Dequeue() {
	T tempData = m_Heap[0];

	Delete(tempData);

	return tempData;
}


template <typename T>
void HeapBase<T>::Retrieve(T& inData, bool& isFound) {
	Retrieve(inData, isFound, 0);

	return;
}


template <typename T>
void HeapBase<T>::Print() {
	T tempData;

	for (int i = 0; i < m_LastNode; i++) {
		tempData << m_Heap[i];
	}

	return;
}


template <typename T>
void HeapBase<T>::Swap(int inParent, int inBottom) {
	T tempData = m_Heap[inParent];
	m_Heap[inParent] = m_Heap[inBottom];
	m_Heap[inBottom] = tempData;

	return;
}