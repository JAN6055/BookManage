#ifndef __USER_H_
#define __USER_H_
#include "password.h"
#include <iostream>
#include <iterator>
#include <string>
#include <memory>
class User
{
public:
    enum {UERS_ADMIN = 1, BOOK_ADMIN = 2, READER = 3};
    User(int id, const string & password, int flag = READER)
        : _id(id), _password(std::make_shared<Password>(password)), _flag(flag)
    { }

    void setPassword();
    int getId() const
    {
        return _id;
    }
    const string & getPassword() const
    {
        return _password->data();
    }
private:
    const int _id;
    std::shared_ptr<Password> _password;
    const int _flag;
};

#endif