#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <iostream>
#include <cassert>
#include "oneD.h"
using namespace std;

template <typename T>
class Vector {
public:

	Vector(int size = 3);

	//Big Three:
	Vector(const Vector& other);
	~Vector();
	Vector& operator =(const Vector& rhs);

	//Member Access Functions:
	const T operator [](const int index) const;
	T& operator [](const int index);
	T& at(int index);
	const T at(int index) const;
	T& front() const;
	T& back() const;


	//Push and Pop functions:
	Vector& operator +=(const T& item);
	Vector& operator +=(const Vector<T>& vec);
	void push_back(const T& item);
	T pop_back();

	//Insert and Erase:
	void insert(int insert_here, const T& insert_this);
	void erase(int erase_index);
	int index_of(const T& item);

	//size and capacity:
	void set_size(int size);
	void set_capacity(int capacity);
	int size() const;
	int capacity() const;

	bool empty() const;

	//OUTPUT:
	template <typename U>
	friend ostream& operator <<(ostream& outs, const Vector<U>& _a);

private:
	int _size;
	int _capacity;
	T* _v;
	bool _debug;
};


template<typename T>
Vector<T>::Vector(int size)
{
	_debug = false;

	_capacity = size;
	_size = 0;
	_v = allocate<T>(_capacity);

	if (_debug) cout << "Constructor Executed" << endl;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	//Copy Info from other class
	_size = other._size;
	_capacity = other._capacity;
	_debug = other._debug;

	//Create new dynamic location
	_v = allocate<T>(_capacity);

	//Copy items
	copy(_v, other._v, _size);

	if (_debug) cout << "Copy CTOR Executed" << endl;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] _v;
	_v = nullptr;
	if (_debug) cout << "Destructor Executed" << endl;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	//Check for self-reference
	if (this == &rhs) return *this;

	//Delete dynamic space if it exits already
	if (_v != nullptr) delete[] _v;

	//Copy Info from other class
	_size = rhs._size;
	_capacity = rhs._capacity;

	//Create new dynamic location
	_v = allocate<T>(_capacity);

	//Copy items
	copy(_v, rhs._v, _size);

	if (_debug) cout << "Assignment Executed" << endl;

	return *this;
}

template<typename T>
const T Vector<T>::operator[](const int index) const
{
	return at(index);
}

template<typename T>
T& Vector<T>::operator[](const int index)
{
	return at(index);
}

template<typename T>
T& Vector<T>::at(int index)
{
	assert(index >= 0 && index <= _size);

	T* index_ptr = _v + index;

	return *index_ptr;
}

template<typename T>
const T Vector<T>::at(int index) const
{
	assert(index >= 0 && index <= _size);

	T* index_ptr = _v + index;

	return *index_ptr;
}

template<typename T>
T& Vector<T>::front() const
{
	return *_v;
}

template<typename T>
T& Vector<T>::back() const
{
	//Pointer to last element
	T* back = _v + _size - 1;

	return *back;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const T& item)
{
	push_back(item);

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& vec)
{
	for(int i = 0; i < vec._size; i++)
		push_back(vec[i]);

	return *this;
}

template<typename T>
void Vector<T>::push_back(const T& item)
{
	_v = add_entry(_v, item, _size, _capacity);
}

template<typename T>
T Vector<T>::pop_back()
{
	assert(_size > 0);

	T removed = back();

	//Remove last element
	_v = remove<T>(_v, _size, _capacity);

	//return last element
	return removed;
}

template<typename T>
void Vector<T>::insert(int insert_here, const T& insert_this)
{
	assert(insert_here <= _size - 1 && insert_here >= 0);

	push_back(insert_this);

	//pointer to point to index to insert
	T* index_ptr = _v + insert_here;

	shift_right(_v, _size, index_ptr);

	at(insert_here) = insert_this;
}

template<typename T>
void Vector<T>::erase(int erase_index)
{
	assert(erase_index <= _size - 1 && erase_index >= 0);

	_v = remove_index(_v, erase_index, _size, _capacity);
}

template<typename T>
int Vector<T>::index_of(const T& item)
{
	int index = -1;

	//Get pointer to item, null ptr if not found
	T* item_ptr = search(_v, _size, item);

	//Subtract pointers to get location
	if (item_ptr != nullptr) index = item_ptr - _v;

	//assert(index >= 0);

	return index;
}

template<typename T>
void Vector<T>::set_size(int size)
{
	assert(size >= 0);

	//Append lowest element for each type to increase size
	for (int i = _size; i < size; i++)
		_v = add_entry(_v, T(), _size, _capacity);

	_size = size;

	//Create a new dynamic array with half the capacity
	//if size is 1/4 of the capacity
	int quarter_size = static_cast<int>(.25 * _capacity);
	if (_size <= quarter_size)
		set_capacity(_capacity / 2);

}

template<typename T>
void Vector<T>::set_capacity(int capacity)
{
	assert(capacity >= _size);

	//Set capacity
	_capacity = capacity;

	//set new space
	_v = reallocate(_v, _size, _capacity);
}

template<typename T>
int Vector<T>::size() const
{
	return _size;
}

template<typename T>
int Vector<T>::capacity() const
{
	return _capacity;
}

template<typename T>
bool Vector<T>::empty() const
{
	if (_size == 0)
		return true;

	return false;
}

template<typename U>
ostream& operator<<(ostream& outs, const Vector<U>& print_me)
{
	print(print_me._v, print_me._size, outs);
	return outs;
}
#endif //VECTOR_H