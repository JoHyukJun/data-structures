#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


template <typename T>
class SortedArrayList {
private:
	T *m_List;				//Dynamic list.
	int m_Size;             //List size.
	int m_Length;           //Number of elements in list.
	int m_CurPointer;       //Iterator pointer.

public:
	/**
	 default constructor.
	 */
	SortedArrayList();


	/**
	 destructor.
	 */
	~SortedArrayList();


	/**
	 @brief  Add a new data into list.
	 @pre    List should be initialized.
	 @post   Added the new record into the list.
	 @param  data   new data.
	 @return Return 1 if this function works well, otherwise 0.
	 */
	int Add(T data);


	/**
	 @brief  Delete a data on list with the input primary key data.
	 @pre    List should be initialized.
	 @post   Delete selected data.
	 @param  data   new data.
	 @return Return 1 if this function works well, otherwise 0.
	 */
	int Delete(T data);


	/**
	 @brief  Replace a data on list with the input primary key data.
	 @pre    List should be initialized.
	 @post   Replace selected data.
	 @param  data   new data.
	 @return Return 1 if this function works well, otherwise 0.
	 */
	int Replace(T data);


	bool Check(T data);


	/**
	 @brief  Find the primary key in target from the list and copy the record to target.
	 @pre    List should be initialized.
	 @post   Copy the selected record.
	 @param  data   data for copy.
	 @return Return 1 if this function works well, otherwise 0.
	 */
	int Get(T& data);


	/**
	 @brief  Move list iterator to the next item in list and get that item.
	 @pre    List and list iterator should not be initialized.
	 @post   Iterator is moved to next item.
	 @param  data   get current iterator's item. It does not need to be initialized.
	 @return Index of current iterator's item if is not end of list, otherwise return -1.
	 */
	int GetNextItem(T& data);


	/**
	 @brief  Geta a number of records in current list.
	 @pre    None.
	 @post   None.
	 @return Number of records in current list.
	 */
	int GetLength();


	/**
	 @brief  Make list empty.
	 @pre    None.
	 @post   Clear list.
	 */
	void MakeEmpty();


	/**
	 @brief  Initialize list iterator.
	 @pre    List should be initialized.
	 @post   Iterator is reset.
	 */
	void ResetList();


	/**
	 @brief  Check capacity of list is full.
	 @pre    None.
	 @post   None.
	 @return Return true if list capacity reached to the upper bound, otherwise return false.
	 */
	bool IsFull();


	/**
	 @brief  Change the size of list.
	 @pre    None.
	 @post   Double the size of the list.
	 */
	void ReSize();
};


template <typename T>
SortedArrayList<T>::SortedArrayList() {
	m_Size = 5;
	m_Length = 0;
	m_List = new T[m_Size];
	ResetList();
}


template <typename T>
SortedArrayList<T>::~SortedArrayList() {
}


template <typename T>
int SortedArrayList<T>::Add(T data) {
	IsFull();

	if (m_Length == 0) {
		m_List[m_Length] = data;
		m_Length++;

		return 1;
	}
	else {
		for (int i = 0; i < m_Length; i++) {
			if (m_List[i] < data) {
				if (i == m_Length - 1) {
					m_List[m_Length] = data;
					m_Length++;

					return 1;
				}
			}
			else if (m_List[i] > data) {
				for (int j = m_Length; j > i; j--) {
					m_List[j] = m_List[j - 1];
				}
				m_List[i] = data;
				m_Length++;

				return 1;
			}
			else {
				return -1;
			}
		}
	}

	return 0;
}


template <typename T>
int SortedArrayList<T>::Delete(T data) {
	for (int i = 0; i < m_Length; i++) {
		if (m_List[i] == data) {
			for (int j = i; j < m_Length; j++) {
				m_List[j] = m_List[j + 1];
			}
			m_Length--;

			return 1;
		}
	}

	return 0;
}


template <typename T>
int SortedArrayList<T>::Replace(T data) {
	for (int i = 0; i < m_Length; i++) {
		if (m_List[i] == data) {
			m_List[i] = data;

			return 1;
		}
	}

	return 0;
}


template <typename T>
bool SortedArrayList<T>::Check(T data) {
	for (int i = 0; i < m_Length; i++) {
		if (m_List[i] == data) {
			return true;
		}
		else {
			return false;
		}
	}
}


template <typename T>
int SortedArrayList<T>::Get(T &data) {
	for (int i = 0; i < m_Length; i++) {
		if (m_List[i] == data) {
			data = m_List[i];

			return 1;
		}
	}

	return 0;
}


template <typename T>
int SortedArrayList<T>::GetNextItem(T &data) {
	m_CurPointer++;
	data = m_List[m_CurPointer];

	return m_CurPointer;
}


template <typename T>
void SortedArrayList<T>::MakeEmpty() {
	m_Length = 0;

	return;
}


template <typename T>
int SortedArrayList<T>::GetLength() {
	return m_Length;
}


template <typename T>
void SortedArrayList<T>::ResetList() {
	m_CurPointer = -1;

	return;
}


template <typename T>
bool SortedArrayList<T>::IsFull() {
	if (m_Length == m_Size - 1) {
		ReSize();

		return true;
	}
	else {
		return false;
	}
}


template <typename T>
void SortedArrayList<T>::ReSize() {
	T *tempList = new T[m_Size * 2];

	memcpy(tempList, m_List, m_Size * sizeof(T));

	m_Size = m_Size * 2;
	m_List = tempList;

	return;
}