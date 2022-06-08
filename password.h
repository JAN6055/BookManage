#ifndef __PASSWORD_H_
#define __PASSWORD_H_
#include "tools.h"
#include <algorithm>
#include <iostream>
#include <string>

using std::string;
class Password
{
public:
    enum {PASS = 0, PASSWORD_SHORT = 1, PASSWORLD_LONG = 2};
    static const string get(const string & mess)
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
    static int check_password(const string & password)
    {
        auto len = password.length();
        if(len < 8)
            return PASSWORD_SHORT;
        else if(len > 12)
            return PASSWORLD_LONG;
        else
            return PASS;
    }
    void set(const Password & password)
    {
        _password = password._password;
    }
    void set(Password & password)
    {
        _password = std::move(password._password);
    }
    const string & data() const
    {
        return _password;
    }
    explicit Password(const string & password) : _password(password)
    { }

    explicit Password(string && password) : _password(std::move(password))
    { }
private:
    string _password;
};

#endif