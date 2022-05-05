#include <iostream>
#include <conio.h>

#include "CChat1.h"

template <typename T>
void GetT(const std::string& _s, T& _t)
{
    do
    {
        std::cout << _s;
        std::cin >> _t;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        else
        {
            std::cin.ignore(32767, '\n');
            break;
        }
    } while (true);
}

void OutString(const std::string& _s)
{
    std::cout << _s << std::endl;
}

int main()
{
    std::cout << std::endl;
    std::cout << "Chat 2.0" << std::endl;
    std::cout << "Welcome!" << std::endl;
    //
    //GetT("Enter slots number: ", sln);
    //GetT("Enter slot size   : ", sls);
    //
    std::cout << std::endl;
    //
    CChat1* chat = new CChat1(OutString, GetT< std::string& >);

    while (true)
    {
        std::cin.clear();
        std::cout << "For exit press q, or press any key to continue";
        //
        while (!_kbhit()) {}
        if (_getch() == 'q')
            break;
        //
        std::cout << "\r                                                                 \r";
        //
        std::string sCommand;
        std::string sLogin;
        auto pCurrentLogin = chat->GetCurrentUser();
        if (pCurrentLogin)
            sLogin = *pCurrentLogin + ": ";
        else
            sLogin = "Command: ";
        GetT(sLogin, sCommand);
        //
        if (sCommand == "send")
        {
            //std::string sLogin;
            //GetT("Enter login: ", sLogin);
            //
            if (chat->Send())
                std::cout << "Message is sent!" << std::endl << std::endl;
            else
                std::cout << "Message isn't sent!" << std::endl << std::endl;
            //
            continue;
        }
        //
        chat->CommandHandler(sCommand);
    }

    std::cout << std::endl;
    //
    delete chat;
}
