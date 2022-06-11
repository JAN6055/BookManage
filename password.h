#ifndef BS__PASSWORD_H_
#define BS__PASSWORD_H_
#include <algorithm>
#include <iostream>
#include <string>
// #include "user.h"

using std::string;
using std::cout;
using std::endl;
class Password
{
public:
    enum {PASS = 0, PASSWORD_SHORT = 1, PASSWORD_LONG = 2};
    static const string getNew(const string & mess);
    static int checkInvalid(const string & password,
                             bool is_print_message =false);
    
    template <typename T>
    static bool setNewPassword(T & t)
    {
        string new_password = getNew("请输入密码:");
        string new_password_again = getNew("\n再次输入密码:");
        if(new_password != new_password_again)
        {
            cout << "两次密码不相同" << endl;
            return false;
        }

         if(checkInvalid(new_password) == PASS)
        {
            t.setPassword(std::move(new_password));
            return true;
        }
        return false; 
    }

};

#endif