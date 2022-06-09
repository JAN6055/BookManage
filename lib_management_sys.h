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

    weak_ptr<User>       _loging_user;
    //                         key, data
    //uid rid is only
    using uid_set_type   = set<shared_ptr<User>>;
    using rid_set_type   = set<shared_ptr<Reader>>;
    using rname_map_type = map<string,weak_ptr<Reader>>;
    //bid is only and others is not only
    using bid_set_type   = set<shared_ptr<Book>>;
    using bname_map_type = multimap<string,weak_ptr<Book>>;
    using baut_map_type  = multimap<string,weak_ptr<Book>>;
    using bpub_map_type  = multimap<string,weak_ptr<Book>>;

    uid_set_type         _uid_set;
    rid_set_type         _rid_set;
    rname_map_type       _rname_map;

    bid_set_type         _bid_set;
    bname_map_type       _bname_map;
    baut_map_type        _baut_map;
    bpub_map_type        _bpub_map;
};

#endif