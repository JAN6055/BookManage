#include "password.h"


const string Password::getNew(const string & mess)
{
    static char buffer[40];
    char ch;
    int i = 0;
    std::cout << mess;
    while ((ch = getche()) && ch != '\n')
    {
        buffer[i++] = ch;
        std::cout << '*';
    }
    buffer[i] = '\0';
    return string(buffer);
}

int Password::checkInvalid(const string & password, bool is_print_message)
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

template <typename T>
bool Password::setNewPassword(T & t)
{
    string new_password = getNew("请输入密码:");
    if(checkInvalid(new_password) == PASS)
    {
        t.setPassword(std::move(new_password));
        return true;
    }
    else
        return false;
}



