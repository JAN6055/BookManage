#include "bookcirinfo.h"
#include "book.h"
#include <istream>
#include <ostream>

ostream & operator<<(ostream & os, const BookCirInfo & book_cir_info)
{
    cout  << book_cir_info._book_tot << " " << book_cir_info._borrowed << " " << book_cir_info._borrowed_tot;
    return os;
}

istream & operator>>(istream & is, BookCirInfo & book_cir_info)
{
    is >> book_cir_info._book_tot >> book_cir_info._borrowed >> book_cir_info._borrowed_tot;
    return is;
}

