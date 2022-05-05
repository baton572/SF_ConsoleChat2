#include "CChat1.h"

#define ECHO true
#define BROADCAST "common"

CChat1::CChat1(
    void (*OutputString)(const std::string& _s),
    void (*InputString)(const std::string& _s, std::string& _t1))
    //
    : m_pCurrentUser(nullptr)
    , m_OutputString(OutputString)
    , m_InputString(InputString)
{
}

CChat1::~CChat1()
{
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        delete it->second;
    }
}

void CChat1::DisplayMessage(const std::string& _s)
{
    m_OutputString(_s);
}

void CChat1::CommandHandler(const std::string& _s)
{
    std::string s = "\r\n";
    //
    if (_s == "?")
    {
        s += "Commands:\r\n";
        s += "users, adduser, deluser, enter, exit, chats, show, send [login / common]\r\n";
        //
        DisplayMessage(s);
    }
    else
    {
        //if (_s == "status")
        //{
        //    DisplayStatus();
        //}
        //else
        if (_s == "users")
        {
            Users();
        }
        else if (_s == "adduser")
        {
            if (!IsInUse(ECHO))
                AddUser();
        }
        else if (_s == "deluser")
        {
            if (!IsInUse(ECHO))
                DelUser();
        }
        else if (_s == "enter")
        {
            if (!IsInUse(ECHO))
                Enter();
        }
        else if (_s == "exit")
        {
            Exit();
        }
        else if (_s == "send")
        {
            if (IsInUse())
                Send();
            else
                DisplayMessage("\r\nChoose user!\r\n");
        }
        else if (_s == "chats")
        {
            if (IsInUse())
                Chats();
            else
                DisplayMessage("\r\nChoose user!\r\n");
        }
        else if (_s == "show")
        {
            if (IsInUse())
                ShowChat();
            else
                DisplayMessage("\r\nChoose user!\r\n");
        }
        else
        {
            DisplayMessage("\r\nUnknown command!\r\n");
        }
    }
}

//void CChat1::DisplayStatus()
//{
//    std::string s = "\r\nChat 1.0\r\n";
//    s += "Users   : ";
//    s += std::to_string(m_users.size()) + "\r\n";
//    //s += "Messages: ";
//    //
//    //for ()
//
//    //s += std::to_string(m_slotsEmpty) + "\r\n";
//    //s += "Slot size  : ";
//    //s += std::to_string(m_slotSize) + "\r\n";
//    //s += "Snack types: ";
//    //s += (m_types.size() > 0 ? std::to_string(m_types.size()) : "-") + "\r\n";
//    //
//    DisplayMessage(s);
//}

void CChat1::Users()
{
    std::string s = "\r\nUsers:";
    if (m_users.size() > 0)
    {
        for (auto it = m_users.begin(); it != m_users.end(); ++it)
            s += "\r\nLogin: " + it->second->GetLogin();
        s += "\r\n";
    }
    else
        s += " -\r\n";
    //
    DisplayMessage(s);
}

std::unordered_map< const std::string, CUser* >::iterator CChat1::FindUser(const std::string& _s)
{
    return m_users.find(_s);
}

bool CChat1::AddUser()
{
    std::string login;
    m_InputString("\r\nLogin: ", login);
    //
    if (login == BROADCAST)
    {
        DisplayMessage("Forbidden login!\r\n");
        return false;
    }
    //
    auto it = FindUser(login);
    if (it != m_users.end())
    {
        DisplayMessage("Already existed!\r\n");
        return false;
    }
    //
    std::string pass;
    m_InputString("\r\nPassword: ", pass);
    //
    DisplayMessage("");
    //
    CUser* pUser = new CUser(login, pass);
    if (pUser)
    {
        m_users[login] = pUser;
        return true;
    }
    return false;
}

bool CChat1::DelUser()
{
    std::string s;
    m_InputString("\r\nLogin: ", s);
    //
    auto it = FindUser(s);
    if (it == m_users.end())
    {
        DisplayMessage("Login is not found!\r\n");
        return false;
    }
    std::string pass;
    m_InputString("\r\nPassword: ", pass);
    //
    DisplayMessage("");
    //
    if (pass == it->second->GetPass())
    {
        delete it->second;
        m_users.erase(it);
        //
        return true;
    }
    else
    {
        DisplayMessage("Incorrect password!\r\n");
        return false;
    }
}

bool CChat1::IsInUse(bool echo)
{
    if (m_pCurrentUser)
    {
        if (echo)
            DisplayMessage("Interface is in use!\r\n");
        return true;
    }
    else
        return false;
}

bool CChat1::Enter()
{
    std::string s;
    m_InputString("\r\nLogin: ", s);
    //
    auto it = FindUser(s);
    if (it == m_users.end())
    {
        DisplayMessage("Login is not found!\r\n");
        return false;
    }
    std::string pass;
    m_InputString("\r\nPassword: ", pass);
    //
    DisplayMessage("");
    //
    if (pass == it->second->GetPass())
    {
        m_pCurrentUser = it->second;
        return true;
    }
    else
    {
        DisplayMessage("Incorrect password!\r\n");
        return false;
    }
}

const std::string* CChat1::GetCurrentUser()
{
    const std::string* ret = nullptr;
    //
    if (m_pCurrentUser)
        ret = &(m_pCurrentUser->GetLogin());
    return ret;
}

//void CChat1::DisplayMessages()
//{
//    if (m_pCurrentUser)
//    {
//        //for (auto from : m_pCurrentUser->m_messages)
//        //Displa
//
//
//
//    }
//}

void CChat1::Exit()
{
    DisplayMessage("Interface is free!\r\n");
    //
    m_pCurrentUser = nullptr;
}

void CChat1::Chats()
{
    std::string s = "\r\nChats:";

    std::list< std::string* > l;
    m_pCurrentUser->GetChats(l);

    if (l.size() > 0)
    {
        for (auto c: l)
            s += "\r\nChat: " + *c;
        s += "\r\n";
    }
    else
        s += " -\r\n";
    //
    DisplayMessage(s);
}

bool CChat1::ShowChat()
{
    std::string chat_name;
    m_InputString("\r\nChat: ", chat_name);
    //
    std::list< std::string* > l;
    m_pCurrentUser->GetMessages(chat_name, l);

    if (l.size() > 0)
    {
        for (auto c : l)
            DisplayMessage(*c);
        DisplayMessage("");
        return true;
    }
    else
    {
        DisplayMessage("Chat is not found!\r\n");
        return false;
    }
}

bool CChat1::Send()
{
    bool ret = false;
    //
    if (m_pCurrentUser)
    {
        std::string address;
        std::string message;
        m_InputString("\r\nRecipient: ", address);
        m_InputString("\r\nMessage:   ", message);
        //
        // For simplicity, while sending messages is done by directly writing messages into the queue of the recipients
        //
        bool bBroadcast = address == BROADCAST;
        //
        if (bBroadcast)
        {
            for (auto it = m_users.begin(); it != m_users.end(); ++it)
            {
                Send(it->second, message, true);
                ret = true;
            }
        }
        else
        {
            auto it = m_users.find(address);
            if (it != m_users.end())
            {
                Send(it->second, message);
                ret = true;
            }
        }
        //
        if (ret && !bBroadcast)
        {
            std::string* sent_message = new std::string("Sent     >> " + message);
            auto letter = CChatMessages(address, sent_message);
            (*m_pCurrentUser) << letter;
        }
    }
    //
    return ret;
}

void CChat1::Send(CUser* pUser, const std::string& message, const bool bBroadcast)
{
    std::string* received_message = new std::string(
        bBroadcast ? m_pCurrentUser->GetLogin() + " >> " + message : "Received << " + message);
    auto letter = CChatMessages(
        bBroadcast ? BROADCAST : m_pCurrentUser->GetLogin(),
        received_message);
    *pUser << letter;
}
