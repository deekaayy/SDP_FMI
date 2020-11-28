#pragma once
#include <iostream>
#include<cassert>
template<typename T>
class Vector
{
private:
	void resize()
	{
		capacity += SPARE_CAPACITY;
		T* newData = new T[capacity];
		for (int i = 0; i < v_size; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
	void copy(const Vector& other)
	{
		v_size = other.v_size;
		capacity = other.capacity;
		data = new T[capacity];
		for (int i = 0; i < v_size; i++)
		{
			data[i] = other.data[i];
		}
	}
	void del()
	{
		delete[] data;
		capacity = 0;
		v_size = 0;
	}
	const int SPARE_CAPACITY = 16;
	int v_size = 0;
	int capacity;
	T* data;
public:
	class myIterator
	{
	private:
		T* current;
	public:
		myIterator(T* initialLocation)
		{
			current = initialLocation;
		}
		myIterator() :current(0) {}
		bool operator==(const myIterator& rhs) const
		{
			return this->current == rhs.current;
		}
		bool operator!=(const myIterator& rhs) const
		{
			return this->current != rhs.current;
		}
		bool operator>(const myIterator& rhs)
		{
			return *current > *rhs.current;
		}
		bool operator>=(const myIterator& rhs)
		{
			return *current >= *rhs.current;
		}
		bool operator<(const myIterator& rhs)
		{
			return *current < *rhs.current;
		}
		bool operator<=(const myIterator& rhs)
		{
			return *current <= *rhs.current;
		}
		myIterator& operator++() //prefix
		{
			current++;
			return *this;
		}
		myIterator operator++(int parameter) //postfix
		{
			myIterator retVal = *this;
			current++;
			return retVal;
		}
		myIterator& operator--() //prefix
		{
			current--;
			return *this;
		}
		myIterator operator--(int parameter) //postfix
		{
			myIterator retVal = *this;
			current--;
			return retVal;
		}
		myIterator operator+(const size_t num)
		{
			myIterator retVal = *this;
			retVal.current = retVal.current + num;
			return retVal;
		}
		myIterator& operator+=(size_t num)
		{
			current = current + num;
			return *this;
		}
		myIterator operator-(size_t num)
		{
			myIterator retVal = *this;
			if ((v_size - num) < 0)
			{
				std::cout << "Index outside of bonds! \n";
			}
			else
			{
				retVal.current = retVal.current - num;
			}
			return retVal;
		}
		myIterator& operator-=(size_t num)
		{
			if ((v_size - num) < 0)
			{
				std::cout << "Index outside of bonds! \n";
			}
			else
			{
				current = current - num;
			}
			return *this;
		}
		size_t operator-(const myIterator& rhs)
		{
			int dist = this - *rhs;
			std::abs(dist);
			return (size_t)dist;
		}
		T& operator*()
		{
			return *current;
		}
		const T& operator*() const
		{
			return *current; //readOnly
		}
		T* operator->()
		{
			return &(operator*());
		}
		const T* operator->() const
		{
			return &(operator*()); //readOnly
		}
		friend myIterator& operator+(int pos, const myIterator& i)
		{
			myIterator ret(i);
			return ret + pos;
		}
	};
	Vector()
	{
		v_size = 0;
		capacity = SPARE_CAPACITY;
		data = new T[capacity];
	}
	explicit Vector(const int size)
	{
		capacity = SPARE_CAPACITY;
		v_size = size;
		while (v_size >= capacity)
		{
			resize();
		}
		data = new T[v_size];
		for (int i = 0; i < v_size; i++)
		{
			data[i] = 0;
		}
	}
	Vector(const int size, T elem)
	{
		capacity = 8;
		v_size = size;
		while (size >= capacity)
		{
			resize();
		}
		data = new T[size];
		for (int i = 0; i < v_size; i++)
		{
			data[i] = elem;
		}
	}
	~Vector()
	{
		del();
	}
	Vector(const Vector& other)
	{
		copy(other);
	}
	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	bool operator==(const Vector& other)const
	{
		if (v_size == other.v_size)
		{
			for (int i = 0; i < v_size; i++)
			{
				if (data[i] != other.data[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool operator!=(const Vector& other) const
	{
		return !(*this == other);
	}
	bool operator>(const Vector& other) const/////////////////////////
	{
		bool flag=false;
		if (v_size > other.v_size)
		{
			for (int i = 0; i < other.v_size; i++)
			{
				if (data[i] > other.data[i])
				{
					flag = true;
				}
				else
					return false;
			}
		}
		else
		{
			for (int i = 0; i < v_size; i++)
			{
				if (data[i] > other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		return flag;
	}
	bool operator<(const Vector& other) const
	{
		bool flag = false;
		if (v_size > other.v_size)
		{
			for (int i = 0; i < other.v_size; i++)
			{
				if (data[i] < other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		else
		{
			for (int i = 0; i < v_size; i++)
			{
				if (data[i] < other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		return flag;
	}
	bool operator>=(const Vector& other) const
	{
		bool flag = false;
		if (v_size > other.v_size)
		{
			for (int i = 0; i < other.v_size; i++)
			{
				if (data[i] >= other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		else
		{
			for (int i = 0; i < v_size; i++)
			{
				if (data[i] >= other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		return flag;
	}
	bool operator<=(const Vector& other) const
	{
		bool flag = false;
		if (v_size > other.v_size)
		{
			for (int i = 0; i < other.v_size; i++)
			{
				if (data[i] <= other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		else
		{
			for (int i = 0; i < v_size; i++)
			{
				if (data[i] <= other.data[i])
				{
					flag = true;
				}
				else return false;
			}
		}
		return flag;
	}
	const T& operator[](int x) const
	{
		return data[x];
	}
	int size()
	{
		return v_size;
	}
	int capacityOf()
	{
		return capacity;
	}
	int getCapacity()
	{
		return capacity;
	}
	bool empty() const
	{
		return !v_size;
	}
	T& front()
	{
		assert(!empty());
		return data[0];
	}
	T& back()
	{
		assert(!empty());
		return data[v_size - 1];
	}
	myIterator begin()
	{
		return myIterator(data); //return data
	}
	myIterator end()
	{
		return myIterator(data + v_size); // return data+size
	}
	void shrinkToFit()
	{
		capacity -= (capacity - v_size);
		T* temp = new T[capacity];
		for (int i = 0; i < v_size; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
	}
	T& at(int index) const//random access 
	{
		if (index >= 0 && index < v_size)
		{
			return data[index];
		}
		else std::cout << "Invalid index! \n";
	}
	void reserve(int amount)//reserve the amount of memory
	{
		if (capacity < amount)
		{
			capacity += (amount - capacity);
			T* temp = new T[capacity];
			for (int i = 0; i < v_size; i++)
			{
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
	}
	void push_back(const T& elem)
	{
		v_size++;
		if (v_size >= capacity) { resize(); }
		data[v_size] = elem;
	}
	void pop_back()
	{
		if (v_size >= 0)
		{
			--v_size;
		}
	}
	void swap(Vector& other)
	{
		Vector temp = *this;
		*this = other;
		other = temp;
	}
	void pop(const size_t index)
	{
		for (size_t i = index; i < v_size; i++)
		{
			data[i] = data[i + 1];
		}
		this->v_size--;
	}
	void erase(const T elem)
	{
		for (int i = 0; i < v_size; i++)
		{
			if (data[i] == elem)
			{
				pop(i);
			}
		}
	}
	void eraseIf(bool predicate)// ToDo just finish it
	{
		for (int i = 0; i < v_size; i++)
		{
			if (predicate)
			{
				pop(i);
			}
		}
	}
};
