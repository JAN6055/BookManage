#ifndef BS_BOOKCIRINFO
#define BS_BOOKCIRINFO
#include "book.h"
#include "user.h"
#include <iostream>
#include <fstream>
extern size_t free_count;
extern size_t malloc_count;
struct BookCirInfo
{
    BookCirInfo(int book_tot = 0, int borrowed = 0, int borrowed_tot = 0) :  _book_tot(book_tot), _borrowed(borrowed), _borrowed_tot(borrowed_tot)
    { }
    int _book_tot;
    int _borrowed;
    int _borrowed_tot;
};

ostream & operator<<(ostream & os, const BookCirInfo & book_cir_info);
istream & operator>>(istream & is, BookCirInfo & book_cir_info);

#endif