#ifndef BS__USER_H_
#define BS__USER_H_
#include "password.h"
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
using std::ostream;
using std::istream;
#include <memory>
class User
{
    friend ostream & operator<<(ostream * os, const User & user);
public:
    enum {UERS_ADMIN = 1, BOOK_ADMIN = 2, READER = 3};
    User(int id, const string & password, int flag = READER)
        : _id(id), _password(password), _flag(flag)
    { }

    void setPassword(const string & new_password)
    {
        _password = new_password;
    }
    void setPassword(string && new_password)
    {
        _password = std::move(new_password);
    }
    int getId() const
    {
        return _id;
    }
    const string & getPassword() const
    {
        return _password;
    }
    int getFlag() const
    {
        return _flag;
    }
protected:
    static User * read(ostream & os);
private:
    const int _id;
    string _password;
    const int _flag;
};

ostream & operator<<(ostream & os, const User & user);
#endif