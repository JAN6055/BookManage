#include "user.h"

void User::setPassword()
{
    string password = Password::get("passworld:");
    while (true)
    {
        auto flag = Password::check_password(password);
        if(flag == Password::PASS)
        {
            _password->set(Password(std::move(password)));
            std::cout << "设置成功！" << std::endl;
        }
        else if(flag == Password::PASSWORD_SHORT)
        {
            std::cout << "密码不能小于八位！" << std::endl;
        }
        else
        {
            std::cout << "密码不能大于10位！" << std::endl;
        }
    }
}
