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
    friend ostream & operator<<(ostream & os, const User & user);
    friend class LibMS;
public:
    enum {USES_ADMIN = 1, BOOK_ADMIN = 2, READER = 3};
    
    User() : _id(0), _flag(READER)
    { }
    User(int id, const string & password, int flag = READER)
        : _id(id), _password(password), _flag(flag)
    { }

    User(int id, string && password, int flag = READER)
        : _id(id), _password(std::move(password)), _flag(flag)
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
    virtual int getFlag() const
    {
        return _flag;
    }
protected:
    static User * read(istream & is);
private:
    int _id;
    string _password;
    int _flag;
};

ostream & operator<<(ostream & os, const User & user);
#endif