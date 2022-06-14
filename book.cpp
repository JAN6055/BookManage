#include "book.h"
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>
using std::istream;
using std::ostream;
//记录号不用手动输入
int Book::_book_tot = 0;

/**
 * @brief 文件IO与键盘IO公用
 * 
 * @param os 
 * @param book 
 * @return ostream& 
 */
ostream & operator<<(ostream & os, const Book & book)
{
    os << book.getLogId() << " " << book.getBookId() << " "
       << book.getName() << " " << book.getAuthor() << " "
       << book.getPub();
    return os;
}

istream & operator>>(istream & is, Book & book)
{
    is >> book._book_id >> book._book_name >> book._author 
       >> book._pub;
    return is;
}