#pragma once

#include <string>

class CPerson
{
public:
	CPerson() = delete;

	CPerson(const std::string& _login, const std::string& _password);

	virtual const std::string& GetLogin();

	virtual const std::string& GetPass();

	friend const bool operator== (const CPerson& _P1, const CPerson& _P2);
	friend const bool operator!= (const CPerson& _P1, const CPerson& _P2);

private:
	const std::string m_login;
	const std::string m_pass;
};
