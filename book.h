#ifndef BS__BOOK_H_
#define BS__BOOK_H_
#include <iostream>
using std::string;
class Book
{
public:
    Book(int log_id, const string & book_id, const string & book_name, 
        const string & author, const string & pub) 
        : _log_id(log_id), _book_id(book_id), _book_name(book_name),
        _author(author), _pub(pub)
    { }
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

    void setAuthor(const string & new_anuthor)
    {
        _author = new_anuthor;
    }

    void setPub(const string & new_pub)
    {
        _pub = new_pub;
    }
    
private:
    const int _log_id;
    const string _book_id;
    string _book_name;
    string _author;
    string _pub;
};

#endif