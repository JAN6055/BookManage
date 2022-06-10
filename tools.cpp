#include "tools.h"
#include <iostream>
#include <string>
#include "menu.h"
#include "user.h"
using std::string;
using std::cin;


char getche()
{
    char ch;
    system("stty -icanon");
    ch = getchar();
    system("stty icanon");
    return ch;
}

/**
 * @brief 输入字符不回显，并且立刻刷新缓冲区
 * 
 * @return char 
 */
char getch()
{
    char ch;
    system("stty -echo");
    ch = getche();
    system("stty echo");
    return ch;
}
/**
 * @brief 从键盘获取一个uid，并校验uid
 * 
 * @return 如果此uid不合法，返回0，否则返回uid（int）
 */
int get_uid()
{
    cout << "请输入uid:";
    string uid;
    cin >> uid;
    cin.get();
    if(uid.length() != 8)
        return 0;
    for(const auto & ch : uid)
    {
        if(ch > '9' || ch < '0')
            return 0;
    }
    return std::stoi(uid.c_str());
}



