#ifndef BS__READER_H_
#define BS__READER_H_
#include "user.h"
//#include <curses.h>

class Reader : public User
{
private:
    using only_read_ret = const string &;
public:
    enum {STUDENT = 1, TEACHER = 2};
    enum {STUDENT_ABLE_BORROW = 5, TEACHER_ABLE_BORROW = 10};
    Reader(int id, const string & password, const string & name, const string & place, 
        const string & contact_details, int flag)
        : User(id,password,READER), _name(name), _place(place),
         _contact_details(contact_details), _flag(flag), _borrowed(0)
    { }
    Reader(int id, string && password, string && name, string && place,
        string && contact_details, int flag)
        : User(id, std::move(password),READER), _name(std::move(name)),
          _place(std::move(place)), _contact_details(std::move(contact_details)),
          _flag(flag), _borrowed(0)
    { }
    only_read_ret getName() const 
    {
        return _name;
    }

    [[nodiscard]] only_read_ret getPlace() const
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
private:
    string _name;
    string _place;
    string _contact_details;
    const int _flag;
    int _borrowed;
};
#endif