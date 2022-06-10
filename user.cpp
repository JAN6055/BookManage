#include "user.h"
#include <fstream>
#include <memory>
using std::make_shared;
ostream & operator<<(ostream & os, const User & user)
{
    os << user.getId() << " " << user.getPassword() << " " << user.getFlag();
    return os;
}

/**
 * @brief 从绑定的文件流中获取一个用户，用户的格式必须固定，否则会出错误
 * 
 * @param is 
 * @return User* 这个指针必须被处理，转换成shared_ptr
 */
shared_ptr<User> User::read(ifstream & is)
{
    int id;
    string password;
    int flag;
    is >> id >> password >> flag;
    return make_shared<User>(id,std::move(password),flag);
}


