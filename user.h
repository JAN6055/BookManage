#ifndef BS__USER_H_
#define BS__USER_H_
#include "password.h"
#include <iostream>
#include <fstream>
#include <memory>
using std::ostream;
using std::ifstream;
extern size_t free_count;
extern size_t malloc_count;
class User
{
    friend ifstream & operator>>(ifstream & fin, User & user);
    friend ostream & operator<<(ostream & os, const User & user);
public:
    enum {USES_ADMIN = 1, BOOK_ADMIN = 2, READER = 3};
    
    User() : _id(0), _password(""), _flag(READER)
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
    virtual void setFlag(int flag)
    {
        _flag = flag;
    }
protected:
    int _id;
private:
    string _password;
    int _flag;
};

ostream & operator<<(ostream & os, const User & user);
#endif