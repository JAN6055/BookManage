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

#define USER_DATA   "/userdata"
#define READER_DATA "/readerdata"
#define BOOK_DATA   "/bookdata"


class LibMS
{
public:
    LibMS(const char * path) : LibMS(string(path))
    { }
    LibMS(const string & path) : _data_path(path), _uid_map(), _rname_map(), _bid_map(), 
        _bname_map(), _baut_map(), _bpub_map(), _loging_user()
    {
        readAllUser(path + USER_DATA);
        readAllReader(path + READER_DATA);
        readAllBook(path + BOOK_DATA);
    }

    ~LibMS()
    {
        writeAllUser(_data_path + USER_DATA);
    }
    User & findUser(int uid)
    {
        return *_uid_map[uid];
    }

    void addUser(User & user)
    {
        _uid_map.insert({user.getId(),shared_ptr<User>(&user)});
    }

    void eraseUser(int uid)
    {
        _uid_map.erase(uid);
    }

    void run();
    bool log_in();
    bool sing_up();
protected:
    void main_scence();
    void user_manage_scence();
    void reader_manage_scence();
    void book_manage_scence();
    void book_stream_scence();
    void user_info_change_scence();
    void reader_info_change_scence();
    void book_serch_scence();
    void book_info_change_scence();
private:

    void readAllUser(const string & path);
    void readAllReader(const string & path);
    void readAllBook(const string & path);
    // void readAllBookBorrowedTot(const string & path);
    // void readAllReaderBorrowTot(const string & path);
    void writeAllUser(const string & path);
    weak_ptr<User>       _loging_user;
    //                         key, data
    //uid rid is only
    using uid_map_type   = map<int,shared_ptr<User>>;
    using rid_map_type   = map<int,shared_ptr<Reader>>;
    using rname_map_type = map<string,weak_ptr<Reader>>;
    
    //bid is only and others is not only
    using bid_map_type   = map<string,shared_ptr<Book>>;
    using bname_map_type = multimap<string,weak_ptr<Book>>;
    using baut_map_type  = multimap<string,weak_ptr<Book>>;
    using bpub_map_type  = multimap<string,weak_ptr<Book>>;

    string _data_path;
    uid_map_type         _uid_map;
    
    rid_map_type         _rid_map;
    rname_map_type       _rname_map;

    bid_map_type         _bid_map;
    bname_map_type       _bname_map;
    baut_map_type        _baut_map;
    bpub_map_type        _bpub_map;
};

#endif