#ifndef BS__BOOK_H_
#define BS__BOOK_H_
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
using std::string;
using std::istream;
using std::ostream;
extern size_t free_count;
extern size_t malloc_count;
class Book
{
    friend istream & operator>>(istream & is, Book & book);
public:
    Book()
    { }
    Book(int log_id) : _log_id(log_id)
    { 
        ++_book_tot;
    }
    Book(int log_id, const string & book_id, const string & book_name, 
        const string & author, const string & pub) 
        : _log_id(log_id), _book_id(book_id), _book_name(book_name),
        _author(author), _pub(pub)
    { 
        ++_book_tot;
    }
    int getLogId() const
    {
        return _log_id;
    }

    using only_read_ret = const string &;
    only_read_ret getBookId() const
    {
        return _book_id;
    }
    only_read_ret getName() const
    {
        return _book_name;
    }

    only_read_ret getAuthor() const
    {
        return _author;
    }

    only_read_ret getPub() const
    {
        return _pub;
    }

    void setName(const string & new_name)
    {
        _book_name = new_name;
    }

    void setName(string && new_name)
    {
        _book_name = std::move(new_name);
    }

    void setAuthor(const string &new_author)
    {
        _author = new_author;
    }

    void setAuthor(string &&new_author)
    {
        _author = std::move(new_author);
    }

    void setPub(const string & new_pub)
    {
        _pub = new_pub;
    }

    void setPub(string && new_pub)
    {
        _pub = std::move(new_pub);
    }
    
    static int _book_tot;
private:
    int _log_id;
    string _book_id;
    string _book_name;
    string _author;
    string _pub;
};

ostream & operator<<(ostream & os, const Book & book);
istream & operator>>(istream & is, Book & book);
#endif