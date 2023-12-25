#pragma once

#include <iostream>

static const int MAXSIZE = 10000;

template <class T>
class TQueue {
	T* pMem;					// ��������� �� ������ �������
	size_t size;				// ������������ ���-�� ��������� � �������
	int count;					// �������������� ���-�� ��������� � �������
	int start, finish;			// ������ �������� ������� � ���������� ��������� � �������
public:
	TQueue(int _size);						// �����������
	TQueue(const TQueue& q);				// ����������� �����������
	~TQueue();								// ����������

	TQueue& operator=(const TQueue& q);		// �������� �����������

	int GetCount() const { return count; }

	int IsEmpty() const;					// �������� �� �������
	int IsFull() const;						// �������� �� �������������

	void Push(const T& val);				// �������� ������� � �������
	T Pop();								// ������� ������� � �������
	T Front() const;						// �������� ������ ������� � �������
	T Back() const;							// �������� ��������� ������� � �������

	void Clear(void);						// �������� �������

	friend std::ostream& operator<<(std::ostream& os, const TQueue& tq);
};

template <class T>
TQueue<T>::TQueue(int _size) {
	if (_size < 1)
		throw "_size < 1";

	pMem = new T[_size];
	size = _size;
	count = 0;
	start = 0, finish = -1;
}

template <class T>
TQueue<T>::TQueue(const TQueue<T>& q) {
	pMem = new T[q.size];
	size = q.size;
	count = q.count;						// count = 0 <=> finish < start, start - finish = 1
	start = q.start, finish = q.finish;

	if (count > 0) {
		if (start <= finish)
			for (int i = start; i <= finish; ++i)
				pMem[i] = q.pMem[i];
		else {
			for (int i = 0; i <= finish; ++i)
				pMem[i] = q.pMem[i];
			for (int i = start; i < size; ++i)
				pMem[i] = q.pMem[i];
		}
	}
}

template <class T>
TQueue<T>::~TQueue() {
	delete[] pMem;
}

template <class T>
TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q) {
	if (this == &q)
		return *this;

	if (this->size != q.size) {
		T* p = new T[q.size];
		delete[] pMem;
		pMem = p;
		size = q.size;
	}
	count = q.count;
	start = q.start, finish = q.finish;

	if (count > 0) {
		if (start <= finish)
			for (int i = start; i <= finish; ++i)
				pMem[i] = q.pMem[i];
		else {
			for (int i = 0; i <= finish; ++i)
				pMem[i] = q.pMem[i];
			for (int i = start; i < size; ++i)
				pMem[i] = q.pMem[i];
		}
	}

	return *this;
}

template <class T>
int TQueue<T>::IsEmpty() const {
	return count == 0;
}

template <class T>
int TQueue<T>::IsFull() const {
	return count == size;
}

template <class T>
void TQueue<T>::Push(const T& val) {
	if (this->IsFull())
		throw "IsFull()";	
	
	++finish;
	finish = finish * (finish != size);
	pMem[finish] = val;

	++count;
}

template <class T>
T TQueue<T>::Pop() {
	if (this->IsEmpty())
		throw "IsEmpty()";

	T res = pMem[start];

	++start;
	start = start * (start != size);
	--count;

	return res;
}

template <class T>
T TQueue<T>::Front() const {
	if (this->IsEmpty())
		throw "Front(), IsEmpty()";
	
	return pMem[start];
}

template <class T>
T TQueue<T>::Back() const {
	if (this->IsEmpty())
		throw "Back(), IsEmpty()";

	return pMem[finish];
}

template <class T>
void TQueue<T>::Clear() {
	count = 0; 
	start = 0, finish = -1;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TQueue<T>& q) {
	// ���� ��������� �� ������� � ����

	if (q.count > 0) {
		if (q.start <= q.finish) {
			for (int i = q.start; i <= q.finish; ++i)
				os << q.pMem[i] + ' ';
			os << '\b';
		}
		else {
			for (int i = q.start; i < q.size; ++i)
				os << q.pMem[i] + ' ';
			for (int i = 0; i <= finish; ++i)
				os << q.pMem[i] + ' ';
			os << '\b';
		}
	}

	return os;
}
