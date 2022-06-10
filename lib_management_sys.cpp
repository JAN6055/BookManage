#include "lib_management_sys.h"
#include "user.h"
#include "menu.h"
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
    fin.open(path.c_str());
    if(!fin.is_open())
    {
        cerr << "file" << path + USER_DATA << "open fail" << endl;
        std::abort();
    }
    while (!fin.eof())
    {
        shared_ptr<User> user(User::read(fin));
        _uid_map.insert({user->getId(),user});
    }
}

void LibMS::readAllBook(const string & path)
{
    ifstream fin;
    fin.open(path.c_str());
    if(!fin.is_open())
    {
        cerr << "file" << path + BOOK_DATA << endl;
        std::abort();
    }
    while (!fin.eof())
    {
        auto book = new Book(++Book::_book_tot);
        fin >> *book;
        shared_ptr<Book> _book(book);
        _bid_map.insert({_book->getBookId(),_book});
        _bname_map.insert({_book->getName(),weak_ptr<Book>(_book)});
        _baut_map.insert({book->getAuthor(),weak_ptr<Book>(_book)});
        _bpub_map.insert({book->getPub(),weak_ptr<Book>(_book)});
    }
}

void LibMS::readAllReader(const string & path)
{
    ifstream fin;
    fin.open(path.c_str());
    if(!fin.is_open())
    {
        cerr << "file" << path << "open fail" << endl;
        std::abort();
    }
    while(!fin.eof())
    {
        shared_ptr<Reader> reader(Reader::read(fin));
        _rname_map.insert({reader->getName(),reader});
    }
}

void LibMS::run()
{
    start_menu();
}
