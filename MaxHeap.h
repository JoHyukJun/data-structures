#pragma once

#include "HeapBase.h"

template <typename T>
class MaxHeap : public HeapBase<T>
{
public:
	/**
	*	default constructor.
	*/
	MaxHeap();


	/**
	*	custom constructor.
	*/
	MaxHeap(int inSize);


	/**
	*	@brief	Heap down.
	*	@pre	Root is the index of the node that may violate the heap order property.
	*	@post	Heap order property is restored between root and bottom.
	*/
	virtual void ReHeapDown(int inParent, int inBottom);


	/**
	*	@brief	Heap up.
	*	@pre	Bottom is the index of the node that may violate the heap order property. The order property is satisfied from root to next-to-last node.
	*	@post	Heap order property is restored between root and bottm.
	*/
	virtual void ReHeapUp(int inRoot, int inBottom);


	/**
	*	@brief	Delete item from this tree.
	*	@pre	Tree is not empty. the item exists in tree.
	*	@post	Item is deleted from this tree.
	*/
	virtual void Delete(T inData, bool& isFound, int inParent);


	/**
	*	@brief	Retrieve tree element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@param	inData		data to find. Key member is initialized.
	*/
	virtual void Retrieve(T& inData, bool& isFound, int inParent);
};


template <typename T>
MaxHeap<T>::MaxHeap() {

}


template <typename T>
MaxHeap<T>::MaxHeap(int inSize) {
	this->m_MasSize = inSize;
	this->m_Heap = new T[this->m_MasSize];
}


template <typename T>
void MaxHeap<T>::ReHeapDown(int inParent, int inBottom) {
	int tempMaxChild;
	int tempLeftChild;
	int tempRightChild;

	tempLeftChild = inParent * 2 + 1;
	tempRightChild = inParent * 2 + 2;

	if (tempLeftChild <= inBottom) {
		if (tempLeftChild == inBottom) {
			tempMaxChild = tempLeftChild;
		}
		else {
			if (this->m_Heap[tempLeftChild] < this->m_Heap[tempRightChild]) {
				tempMaxChild = tempRightChild;
			}
			else {
				tempMaxChild = tempLeftChild;
			}
		}

		if (this->m_Heap[inParent] < this->m_Heap[tempMaxChild]) {
			this->Swap(inParent, tempMaxChild);
			ReHeapDown(tempMaxChild, inBottom);
		}
	}

	return;
}


template <typename T>
void MaxHeap<T>::ReHeapUp(int inRoot, int inBottom) {
	int tempParent;

	if (inBottom > inRoot) {
		tempParent = (inBottom - 1) / 2;

		if (this->m_Heap[tempParent] < this->m_Heap[inBottom]) {
			this->Swap(tempParent, inBottom);
			ReHeapUp(inRoot, tempParent);
		}
	}

	return;
}


template <typename T>
void MaxHeap<T>::Delete(T inData, bool& isFound, int inParent) {
	int tempLeftChild;
	int tempRightChild;

	tempLeftChild = inParent * 2 + 1;
	tempRightChild = inParent * 2 + 2;

	if (this->m_Heap[inParent] == inData) {
		this->m_Heap[inParent] = this->m_Heap[this->m_LastNode - 1];
		ReHeapDown(inParent, this->m_LastNode - 2);

		isFound = false;
	}

	if (tempLeftChild < this->m_LastNode && !isFound) {
		Delete(inData, isFound, tempLeftChild);
	}

	if (tempRightChild < this->m_LastNode && !isFound) {
		Delete(inData, isFound, tempRightChild);
	}

	return;
}


template <typename T>
void MaxHeap<T>::Retrieve(T& inData, bool& isFound, int inParent) {
	int tempLeftChild;
	int tempRightChild;

	tempLeftChild = inParent * 2 + 1;
	tempRightChild = inParent * 2 + 2;

	if (this->m_Heap[inParent] == inData) {
		inData = this->m_Heap[inParent];
		isFound = true;
	}

	if (tempLeftChild < this->m_LastNode && !isFound) {
		Retrieve(inData, isFound, tempLeftChild);
	}

	if (tempRightChild < this->m_LastNode && !isFound) {
		Retrieve(inData, isFound, tempRightChild);
	}

	return;
}