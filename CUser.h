#pragma once

#include <list>
#include <string>

struct CChatMessages
{
	CChatMessages(std::string _from, std::string* _message)
		: from(_from)
	{
		messages.push_back(_message);
	}

	std::string from;
	std::list< std::string* > messages;
};

class CUser
{
public:
	CUser() = delete;

	CUser(const std::string& _login, const std::string& _password);

	CUser(const CUser&) = delete;

	CUser& operator=(const CUser&) = delete;

	~CUser();

	friend const bool operator== (const CUser& _P1, const CUser& _P2);
	friend const bool operator!= (const CUser& _P1, const CUser& _P2);

	CUser& operator<< (CChatMessages&);

	virtual const std::string& GetLogin();
	virtual const std::string& GetPass();

	virtual void GetChats(std::list< std::string* >& l);
	virtual void GetMessages(const std::string& s, std::list< std::string* >& l);
	// 
	//virtual const std::string* GetNextMessage();

private:
	const std::string m_login;
	const std::string m_pass;
	//
	//CChatMessages* m_pCurrentChat;
	//
	std::list< CChatMessages > m_messages;
};
