#pragma once

#include <iostream>
#include <unordered_map>
#include "CUser.h"

//#define SLOTSMAX 80
//#define SLOTSIZE 10

class CChat1
{
public:
	CChat1() = delete;

	CChat1(
		void (*DisplayFunc)(const std::string& _s),
		void (*InputString)(const std::string& _s, std::string& _t1));

	CChat1(const CChat1& _chat) = delete;

	CChat1& operator=(const CChat1& _chat) = delete;

	virtual ~CChat1();

	virtual void CommandHandler(const std::string&);

	//virtual void DisplayStatus();

	virtual void DisplayMessage(const std::string&);

	//virtual void DisplayMessages();

	virtual const std::string* GetCurrentUser();

	virtual bool Send();

private:
	virtual void Users();

	std::unordered_map< std::string, CUser* >::iterator FindUser(const std::string& _s);

	virtual bool AddUser();

	virtual bool DelUser();

	virtual bool Enter();

	virtual void Exit();

	virtual void Send(CUser*, const std::string&, const bool = false);

	virtual bool IsInUse(bool echo = false);

	virtual void Chats();

	virtual bool ShowChat();

	void (*m_OutputString)(const std::string& _s);
	void (*m_InputString)(const std::string& _s, std::string& _t1);
	//
	CUser* m_pCurrentUser;
	//
	std::unordered_map< std::string, CUser* > m_users;
};
