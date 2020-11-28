#pragma once
#include<iostream>

template <typename T>
class Queue
{
private:
	size_t size=0;
	size_t capacity=1;
	T* elements;
	void resize();
	void copy(const Queue&);
	void del();
public:
	Queue();
	Queue(const Queue&);
	Queue<T>& operator=(const Queue&);
	~Queue();
	void push_back(const T&);
	void pop_front();
	T front();
	bool isEmpty();
	size_t getSize();
	void print(); // not sure if needed but good to have
};

template<typename T>
inline void Queue<T>::resize()
{
	T *tmp = new T[capacity * 2];

	for (int i = 0; i < size; ++i) 
	{
		tmp[i] = elements[i];
	}

	capacity *= 2;
	delete[] elements;
	elements = tmp;
}

template<typename T>
inline void Queue<T>::copy(const Queue & other)
{
	if (other.size >= capacity) 
	{
		resize();
	}
	size = other.size;
	for (int i = 0; i < size; ++i) {
		elements[i] = other.elements[i];
	}
}

template<typename T>
inline void Queue<T>::del()
{
	delete[] elements;
}

template<typename T>
inline Queue<T>::Queue()
{
	size = 0;
	capacity = 8;
	elements = new T[capacity];
}

template<typename T>
inline Queue<T>::Queue(const Queue & other)
{
	capacity = other.capacity;
	size = other.size;
	copy(other);
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue &other)
{
	if (this != &other)
	{
		del();
		capacity = other.capacity;
		size = other.size;
		copy(other);
	}
	return *this;
}

template<typename T>
inline Queue<T>::~Queue()
{
	del();
}

template<typename T>
inline void Queue<T>::push_back(const T& pushed)
{
	if (size == capacity)
	{
		resize();
	}
	elements[size++] = pushed;
}

template<typename T>
inline void Queue<T>::pop_front()
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	size--;
}

template<typename T>
inline T Queue<T>::front()
{
	return elements[0];
}

template<typename T>
inline bool Queue<T>::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
inline size_t Queue<T>::getSize()
{
	return size;
}

template<typename T>
inline void Queue<T>::print()
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << elements[i] << " ";
	}
	std::cout << std::endl;
}


///////examples
/*
Queue <int> p;
p.push_back(5);
p.push_back(3);
p.push_back(6);
p.push_back(9);
p.print();
p.pop_front();
p.print();
Queue <int> q(p);
q.print();
q.pop_front();
q.print();
q.push_back(20);
q.print();
Queue<char> o;
o.push_back('a');
o.push_back('b');
o.push_back('c');
o.push_back('d');
o.print();
o.pop_front();
o.print();
*/