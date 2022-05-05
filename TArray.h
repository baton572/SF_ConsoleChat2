#pragma once
#include <exception>
#include "MyException.h"

template <typename T>
class TArray
{
private:
	int m_size;
	T* m_array;

	T* get_memory(const unsigned int);

	void copy_array(const T* pTo, const T* pFrom, const int size);

public:
	/*explicit*/ TArray();

	/*explicit*/ TArray(const int);
	
	TArray(const TArray&);

	TArray& operator=(const TArray&);

	TArray(TArray&&) noexcept;

	TArray& operator=(TArray&&) noexcept;

	virtual ~TArray();

	T& operator[](const int index);

	const int& size();

	void clear();

	void resize(const int new_size);

	void push_back(const T value);

	void insert(const int index, const T value);

	void erase(const int index);
};
