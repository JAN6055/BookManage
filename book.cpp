#include "book.h"
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>
using std::istream;
using std::ostream;
// using std::cout;
int Book::_book_tot = 0;
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
       >> book._author;
    return is;
}