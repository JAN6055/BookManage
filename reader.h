#ifndef BS__READER_H_
#define BS__READER_H_
#include "user.h"
#include <fstream>
#include <memory>
#include <type_traits>
#include <utility>
using std::shared_ptr;
class Reader : public User
{
    friend ostream & operator<<(ostream & os, const User & user);
private:
    using only_read_ret = const string &;
public:
    enum {STUDENT = 1, TEACHER = 2};
    enum {STUDENT_ABLE_BORROW = 5, TEACHER_ABLE_BORROW = 10};
    Reader(int id, const string & password, const string & name, const string & place, 
        const string & contact_details, int flag,int borrowed = 0)
        : User(id,password,READER), _name(name), _place(place),
         _contact_details(contact_details), _flag(flag), _borrowed(borrowed)
    { }
    Reader(int id, string && password, string && name, string && place,
        string && contact_details, int flag, int borrowed = 0)
        : User(id, std::move(password),READER), _name(std::move(name)),
          _place(std::move(place)), _contact_details(std::move(contact_details)),
          _flag(flag), _borrowed(borrowed)
    { }
    only_read_ret getName() const 
    {
        return _name;
    }

    only_read_ret getPlace() const
    {
        return _place;
    }
    only_read_ret getContactDetails() const
    {
        return _contact_details;
    }

    int getFlag() const override
    {
        return _flag;
    }

    int getAbleBorrow() const
    {
        return _flag == STUDENT ? STUDENT_ABLE_BORROW : TEACHER_ABLE_BORROW;
    }

    int getBorrowed() const
    {
        return _borrowed;
    }

    void borrowedUp()
    {
        if(_borrowed == getAbleBorrow())
            return;
        ++_borrowed;
    }
    void borrowedDown()
    {
        if(_borrowed <= 0)
            return;
        --_borrowed;
    }
    void setName(string && new_name)
    {
        _name = std::move(new_name);
    }
    void setName(const string & new_name)
    {
        _name = new_name;
    }
    void setPlace(const string & new_place)
    {
        _place = new_place;
    }
    void setPlace(string && new_place)
    {
        _place = std::move(new_place);
    }
    void setCon(const string & new_con)
    {
        _contact_details = new_con;
    }
    void setCon(string && new_con)
    {
        _contact_details = std::move(new_con);
    }
    static shared_ptr<Reader> read(ifstream & fis);
    
private:
    string _name;
    string _place;
    string _contact_details;
    int _flag;
    int _borrowed;
};

ostream & operator<<(ostream & os, const Reader & reader);
#endif