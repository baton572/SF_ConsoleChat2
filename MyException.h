#pragma once
//#include <iostream>
#include <string>
#include <exception>

class MyException : public std::exception
{
protected:
	long m_param;

public:
	MyException(long i) noexcept : m_param(i) {};

	//virtual const char* what() const noexcept override {};

	long& getparam() { return m_param; }
};

class no_memory : public MyException
{
public:
	no_memory(long i) noexcept : MyException(i) {};

	virtual const char* what() const noexcept override
	{
		return "No memory";
	};
};

class bad_index : public MyException
{
public:
	bad_index(long i) noexcept : MyException(i) {};

	virtual const char* what() const noexcept override
	{
		return "Bad index";
	};
};

class bad_size : public MyException
{
public:
	bad_size(long i) noexcept : MyException(i) {};

	virtual const char* what() const noexcept override
	{
		return "Bad size";
	};
};
