#include "CUser.h"

CUser::CUser(const std::string& _login, const std::string& _password)
	: m_login(_login)
	, m_pass(_password)
	//, m_pCurrentChat(nullptr)
{
}

CUser::~CUser()
{
	for (auto& from : m_messages)
	{
		for (auto& m : from.messages)
			delete m;
	}
}

const bool operator==(const CUser& _P1, const CUser& _P2)
{
	return _P1.m_login == _P2.m_login;
}

const bool operator!=(const CUser& _P1, const CUser& _P2)
{
	return _P1.m_login != _P2.m_login;
}

CUser& CUser::operator<<(CChatMessages& _messages)
{
	CChatMessages* pFrom = nullptr;
	//
	for (auto itChat = m_messages.begin(); itChat != m_messages.end(); ++itChat)
	{
		if (itChat->from == _messages.from)
		{
			pFrom = &*itChat;
			break;
		}
	}
	//
	if (pFrom)
	{
		for (auto m : _messages.messages)
			pFrom->messages.push_back(m);
	}
	else
	{
		m_messages.push_back(_messages);
	}
	//
	return *this;
}

const std::string& CUser::GetLogin()
{
	return m_login;
}

const std::string& CUser::GetPass()
{
	return m_pass;
}

void CUser::GetChats(std::list< std::string* >& l)
{
	for (auto it = m_messages.begin(); it != m_messages.end(); ++it)
	{
		l.push_back(&(it->from));
	}
}

void CUser::GetMessages(const std::string& s, std::list< std::string* >& l)
{
	for (auto itChat = m_messages.begin(); itChat != m_messages.end(); ++itChat)
	{
		if (s == itChat->from)
		{
			for (auto itMessage = itChat->messages.begin(); itMessage != itChat->messages.end(); ++itMessage)
			{
				l.push_back(*itMessage);
			}
		}
	}
}
