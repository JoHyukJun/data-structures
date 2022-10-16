#pragma once

#include <string>

using namespace std;

#define QUEUESIZE 30


class FullQueue {
public:
	void print() {
		cout << "FullQueue exception thrown" << endl;

		return;
	}
};


class EmptyQueue {
public:
	void print() {
		cout << "Empty exception thrown" << endl;

		return;
	}
};


template <typename T>
class Queue
{
private:
	T *m_Item;			//Pointer for dynamic allocation.
	int m_Front;		//Index of one infront of the first element.
	int m_Rear;			//Index of the last element.
	int m_MaxQueue;		//Max size of the queue.
	int m_Top;

public:
	/**
	 default constructor.
	 */
	Queue();


	/**
	 destructor.
	 */
	~Queue();


	/**
	 @brief  Check capacity of queue is full.
	 @pre    None.
	 @post   None.
	 @return Return true if queue is full, otherwise return false.
	 */
	bool IsFull() const;


	/**
	 @brief  Check capacity of queue is empty.
	 @pre    None.
	 @post   None.
	 @return Return true if queue is empty, otherwise return false.
	 */
	bool IsEmpty() const;


	/**
	 @brief  Add new item to the last of the queue.
	 @pre    The queue should be initialized.
	 @post   If queue is full, fullqueue exception is thrown, otherwise new item is at the last.
	 */
	void Enqueue(T inData);


	/**
	 @brief  Remove first item from the queue.
	 @pre    The queue should be initialized.
	 @post   If queue is empty, emptyqueue exception is thrown, otherwise first element has been removed from queue, item gets value of removed item.
	 */
	void Dequeue(T &inData);


	/**
	*	@brief	Initialize queue iterator.
	*	@pre	Queue has been initialized.
	*	@post	Iterator is reset.
	*/
	void ResetQueue();


	/**
	*	@brief	Print all the items in the queue on screen
	*	@pre	Queue has been initialized.
	*	@post	None.
	*/
	void Print();


	/**
	 @brief  Move list iterator to the next item in list and get that item.
	 @pre    Queue and queue iterator should not be initialized.
	 @post   Iterator is moved to next item.
	 @param  data   get current iterator's item. It does not need to be initialized.
	 @return Index of current iterator's item if is not end of list, otherwise return -1.
	 */
	int GetNextItem(T &inData);
};


template <typename T>
Queue<T>::Queue() {
	m_Item = new T[QUEUESIZE];
	m_Front = QUEUESIZE - 1;
	m_Rear = QUEUESIZE - 1;
	m_MaxQueue = QUEUESIZE;
	m_Top = -1;
}


template <typename T>
Queue<T>::~Queue() {
	delete[] m_Item;
}


template <typename T>
bool Queue<T>::IsFull() const {
	if ((m_Rear + 1) % m_MaxQueue == m_Front) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
bool Queue<T>::IsEmpty() const {
	if (m_Front == m_Rear) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
void Queue<T>::ResetQueue() {
	m_Front = m_MaxQueue - 1;
	m_Rear = m_MaxQueue - 1;

	return;
}


template <typename T>
void Queue<T>::Enqueue(T inData) {
	if (IsFull()) {
		//throw FullQueue();
		cout << "FullQueue exception thrown" << endl;
	}
	else {
		m_Rear = (m_Rear + 1) % m_MaxQueue;
		m_Item[m_Rear % m_MaxQueue] = inData;
		m_Top++;
	}

	return;
}


template <typename T>
void Queue<T>::Dequeue(T &inData) {
	m_Top--;

	if (IsEmpty()) {
		//throw EmptyQueue();
		cout << "Empty exception thrown" << endl;
	}
	else {
		m_Front = (m_Front + 1) % m_MaxQueue;
		inData = m_Item[m_Front];
	}

	return;
}


template <typename T>
void Queue<T>::Print() {
	if (IsEmpty()) {
		cout << "Empty exception thrown" << endl;
	}
	else {
		int start = m_Front;
		int end = m_Rear;

		while (start != end) {
			m_Item[(start + 1) % m_MaxQueue].DisplayRecordOnScreen();

			start = (start + 1) % m_MaxQueue;
		}
	}

	return;
}


template <typename T>
int Queue<T>::GetNextItem(T &inData) {

}
