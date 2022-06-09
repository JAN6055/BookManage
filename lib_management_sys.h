#ifndef __LIB_MANAGEMENT_SYS_H_
#define __LIB_MANAGEMENT_SYS_H_
#include "user.h"
#include "reader.h"
#include "book.h"
#include <cstdio>
#include <map>
#include <memory>
#include <iostream>
#include <set>
using std::shared_ptr;
using std::multimap;
using std::map;
using std::weak_ptr;
using std::set;

#define USER_DATA   "/userdata"
#define READER_DATA "/readerdata"
#define BOOK_DATA   "/bookdata"


class LibMS
{
public:
    LibMS(const char * path)
    {
        
    }
    LibMS(const string & path)
    {

    }
private:

    void readAllUser(const string & path);
    void readAllReader(const string & path);
    void readAllBook(const string & path);
    void readAllBookBorrowedTot(const string & path);
    void readAllReaderBorrowTot(const string & path);

    weak_ptr<User> _loging_user;
    //                         key, data
    //uid and uname is only
    using uid_set_type   = set<shared_ptr<User>>;
    using uname_map_type = map<string,weak_ptr<User>>;
    //bid is only bname and other is not only
    using bid_set_type   = set<shared_ptr<Book>>;
    using bname_map_type = multimap<string,weak_ptr<Book>>;
    using baut_map_type  = multimap<string,weak_ptr<Book>>;
    using bpub_map_type  = multimap<string,weak_ptr<Book>>;

    
};

#endif