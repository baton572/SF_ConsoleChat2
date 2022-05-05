#pragma once
#include <exception>
#include "MyException.h"
#include "TArray.h"

template <typename T> TArray<T>::TArray()
	: m_size(0)
	, m_array(nullptr)
{
}

template <typename T> T* TArray<T>::get_memory(const unsigned int size)
{
	T* p = nullptr;
	//
	try
	{
		p = new T[size] {};
	}
	catch (std::bad_alloc&)
	{
		throw no_memory(sizeof(T) * size);
	}
	return p;
}

template <typename T> void TArray<T>::copy_array(const T* pTo, const T* pFrom, const int size)
{
	T* pTo_ = (T*)pTo;
	T* pFrom_ = (T*)pFrom;
	for (auto i = 0; i < size; ++i)
	{
		*pTo_ = *pFrom_;
		++pTo_;
		++pFrom_;
	}
}

template <typename T> TArray<T>::TArray(const int size)
	: m_size(size)
	, m_array(nullptr)
{
	if (m_size > 0)
		m_array = get_memory(m_size);
	else if (m_size < 0)
		throw bad_size(m_size);
}

template <typename T> TArray<T>::TArray(const TArray& other)
	: TArray(other.m_size)
{
	copy_array(m_array, other.m_array, m_size);
}

template <typename T> TArray<T>& TArray<T>::operator=(const TArray& other)
{
	if (this != &other)
	{
		if (m_array)
			delete[] m_array;
		//
		m_size = other.m_size;
		m_array = get_memory(m_size);
		//
		copy_array(m_array, other.m_array, m_size);
	}
	return *this;
}

template <typename T> TArray<T>::TArray(TArray&& other) noexcept
	: m_size(other.m_size)
	, m_array(other.m_array)
{
	other.m_size  = 0;
	other.m_array = nullptr;
}

template <typename T> TArray<T>& TArray<T>::operator=(TArray&& other) noexcept
{
	if (this != &other)
	{
		if (m_array)
			delete[] m_array;
		//
		m_size = other.m_size;
		m_array = other.m_array;
		//
		other.m_size = 0;
		other.m_array = nullptr;
	}
	return *this;
}

template <typename T> TArray<T>::~TArray()
{
	if (m_array)
		delete[] m_array;
}

template <typename T> T& TArray<T>::operator[](const int index)
{
	if ((index >= m_size) || (index < 0))
		throw bad_index(index);
	else
		return m_array[index];
}

template <typename T> const int& TArray<T>::size()
{
	return m_size;
}

template <typename T> void TArray<T>::clear()
{
	if (m_array)
	{
		delete[] m_array;
		m_array = nullptr;
	}
	//
	m_size = 0;
}

template <typename T> void TArray<T>::resize(const int new_size)
{
	if (new_size == m_size)
		return;
	//
	if (new_size < 0)
		throw bad_size(new_size);
	//
	if (m_array)
	{
		T* new_array = nullptr;
		//
		if (new_size > 0)
			new_array = get_memory(new_size);
		//
		if (new_array)
			copy_array(new_array, m_array, m_size < new_size ? m_size : new_size);
		//
		delete[] m_array;
		//
		m_size = new_size;
		m_array = new_array;
	}
}

template <typename T> void TArray<T>::push_back(const T value)
{
	auto size_ = m_size;
	resize(m_size + 1);
	//
	(*this)[size_] = value;
}

template <typename T> void TArray<T>::insert(const int index, const T value)
{
	// Last + 1
	if (index == m_size)
	{
		push_back(value);
		return;
	}
	// Exception, if position is out of range
	auto element = (*this)[index];
	//
	if ((long)(m_size + 1) > INT_MAX)
		throw bad_size((long)(m_size + 1));
	//
	if (m_array)
	{
		T* new_array = get_memory(m_size + 1);
		//
		if (new_array)
		{
			copy_array(new_array, m_array, index);
			//
			*(new_array + index) = value;
			//
			copy_array(new_array + index + 1, m_array + index, m_size - index);
		}
		//
		delete[] m_array;
		//
		m_size += 1;
		m_array = new_array;
	}
}

template <typename T> void TArray<T>::erase(const int index)
{
	// The last element
	if (index == (m_size - 1))
	{
		resize(m_size - 1);
		return;
	}
	// Exception, if position is out of range
	auto element = (*this)[index];
	//
	if (m_size == 1)
	{
		clear();
		return;
	}
	//
	if (m_array)
	{
		T* new_array = get_memory(m_size - 1);
		//
		if (new_array)
		{
			copy_array(new_array, m_array, index);
			//
			copy_array(new_array + index, m_array + index + 1, m_size - index - 1);
		}
		//
		delete[] m_array;
		//
		m_size -= 1;
		m_array = new_array;
	}
}
