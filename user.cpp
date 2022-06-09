#include "user.h"
#include <ostream>

ostream & operator<<(ostream & os, const User & user)
{
    os << user.getId() << " " << user.getPassword() << " " << user.getFlag();
    return os;
}

User * read(ostream & os)
{
    int id;
    string password;
    int flag;
    os << id << password << flag;
    return new User(id,std::move(password),flag);
}


