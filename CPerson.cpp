#include "CPerson.h"

CPerson::CPerson(const std::string& _login, const std::string& _password)
	: m_login(_login)
	, m_pass(_password)
{
}

const bool operator==(const CPerson& _P1, const CPerson& _P2)
{
	return _P1.m_login == _P2.m_login;
}

const bool operator!=(const CPerson& _P1, const CPerson& _P2)
{
	return _P1.m_login != _P2.m_login;
}

const std::string& CPerson::GetLogin()
{
	return m_login;
}

const std::string& CPerson::GetPass()
{
	return m_pass;
}
