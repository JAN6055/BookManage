#ifndef BS__PASSWORD_H_
#define BS__PASSWORD_H_
#include <algorithm>
#include <iostream>
#include <string>

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
    static bool setNewPassword(T & t);

};

#endif