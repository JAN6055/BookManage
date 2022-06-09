#include "user.h"
#include <ostream>

ostream & operator<<(ostream & os, const User & user)
{
    os << user.getId() << " " << user.getPassword() << " " << user.getFlag();
    return os;
}

User * read(istream & is)
{
    int id;
    string password;
    int flag;
    is >> id >> password >> flag;
    return new User(id,std::move(password),flag);
}


