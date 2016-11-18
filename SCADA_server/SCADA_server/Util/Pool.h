#pragma once
#ifndef  POOL_H
#define POOL_H
#include "stdafx.h"
#define DEFAULT_ARR_LENGTH 16
template <class T>
class Pool {
public:
	Pool(int defaultValue) {
		pool = new T[DEFAULT_ARR_LENGTH];
		for (int i = 0; i < DEFAULT_ARR_LENGTH; i++) {
			pool = defaultValue;
		}
		size = DEFAULT_ARR_LENGTH;
		count = 0;
	}
	~Pool() {
		delete pool, pool = 0;
	}

	void add(T value, int defaultValue);
	void remove(T value, int defaultValue);
	int getSize() const;
	int getCount() const;
	T getValue(int idx) const;
private:
	T *pool;
	int size;
	int count;
	void expand(int defaultValue);
	void shrink(int defaultValue);
};

#endif // ! POOL_H

template<class T>
inline void Pool<T>::add(T value, int defaultValue)
{
	if (count % size < 5)
		expand();

	pool[count] = value;
}

template<class T>
inline void Pool<T>::remove(T value, int defaultValue)
{
	if (count % size < 2.5)
		shrink();
}

template<class T>
inline void Pool<T>::expand(int defaultValue)
{
	T *pool_;
	int size_ = this->size*2;
	pool_ = new T[size];

	for (int i = 0, j = 0; i < this->size; i++, j++) {
		pool_[j] = this->pool[i];
	}
	for (int i = this->size; i < size_; i++) {
		pool_[i] = 0;
	}
	delete this->pool;
	this->pool = pool_;
	this->size = size_;

}

template<class T>
inline void Pool<T>::shrink(int defaultValue)
{
	T *pool_;
	int size_ = this->size/2;
	pool_ = new T[size];

	for (int i = 0, j = 0; i < this->size; i++) {
		if (this->pool[i] != 0) {
			pool_[j] = this->pool[i];
			j++
		}
	}

	delete this->pool;
	this->pool = pool_;
	this->size = size_;
}

template<class T>
int Pool<T>::getSize() const {
	return size;
}

template<class T>
inline int Pool<T>::getCount() const
{
	return count;
}

template<class T>
inline T Pool<T>::getValue(int idx) const
{
	return pool[idx];
}

