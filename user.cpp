#include "user.h"
#include <fstream>
#include <memory>


ostream & operator<<(ostream & os, const User & user)
{
    os << user.getId() << " " << user.getPassword() << " " << user.getFlag();
    return os;
}

/**
 * @brief 因为密码的影响，不能直接对用户进行重载键盘的输入
 *        只有对文件输入流的重载，确保文件格式正确，可以有空行
 *        对于Reader同样
 * 
 * @param fin 
 * @param user 
 * @return ifstream& 
 */
ifstream & operator>>(ifstream & fin, User & user)
{
    fin >> user._id
        >> user._password
        >> user._flag;
    return fin;
}
