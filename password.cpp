#include "password.h"
#include "tools.h"

const string Password::getNew(const string & mess)
{
    static char buffer[40];
    char ch;
    int i = 0;
    std::cout << mess;
    while ((ch = getch()) && ch != '\n')
    {
        buffer[i++] = ch;
        std::cout << '*';
    }
    buffer[i] = '\0';
    return string(buffer);
}

int Password::checkInvalid(const string & password, bool is_print_message/*=false*/)
{
    auto len = password.length();
    if(len < 8)
    {
        if(is_print_message)
            cout << "密码不能个小于8位" << endl;
        return PASSWORD_SHORT;
    }
    else if(len > 12)
    {
        if(is_print_message)
            cout << "密码不能大于12位" << endl;
        return PASSWORD_LONG;
    }
    else
        return PASS;
}



