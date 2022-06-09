#include "lib_management_sys.h"
#include "user.h"
#include <cstdlib>
#include <fstream>
#include <exception>
#include <iostream>
#include <memory>

using std::ifstream;
using std::ofstream;
// using std::make_shared;
using std::cerr;
void LibMS::readAllUser(const string & path)
{
    ifstream fin;
    fin.open((path + USER_DATA).c_str());
    if(!fin.is_open())
    {
        cerr << "file" << path + USER_DATA << "open fail" << endl;
        std::abort();
    }
    while (!fin.eof())
    {
        shared_ptr<User> user(User::read(fin));
        _uid_set.insert(user);
    }
}

void LibMS::readAllBook(const string & path)
{
    ifstream fin;
    fin.open((path + BOOK_DATA).c_str());
    if(!fin.is_open())
    {
        cerr << "file" << path + BOOK_DATA << "open fail" << endl;
        std::abort();
    }
    while (!fin.eof())
    {
        auto book = new Book(++Book::_book_tot);
        fin >> *book;
        shared_ptr<Book> _book(book);
        _bid_set.insert(_book);
        _bname_map.insert({_book->getName(),weak_ptr<Book>(_book)});
        _baut_map.insert({book->getAuthor(),weak_ptr<Book>(_book)});
        _bpub_map.insert({book->getPub(),weak_ptr<Book>(_book)});
    }
}


