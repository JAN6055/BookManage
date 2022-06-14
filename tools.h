#ifndef BS__TOOLS_H_
#define BS__TOOLS_H_
#include "bookcirinfo.h"
#include "user.h"
#include "book.h"
#include "reader.h"
#include <functional>
#include <iostream>
#include <string>
using std::string;

char getch();
char getche();

using std::less;

/**
 *  下列仿函数没有被真正的使用，作用仅仅是列留着当作备用工具 
 * 
 */

struct less_uid
{
    bool operator()(const User & lhs, const User & rhs)
    {
        return less<int>()(rhs.getId(),rhs.getId());
    }
};

struct less_rname
{
    bool operator()(const Reader & lhs, const Reader & rhs)
    {
       return less<string>()(lhs.getName(),rhs.getName());
    }
};

struct less_bid
{
    bool operator()(const Book & lsh, const Book & rhs)
    {
        return less<string>()(lsh.getBookId(),rhs.getBookId());
    }
};

struct less_bname
{
    bool operator()(const Book & lsh, const Book & rhs)
    {
        return less<string>()(lsh.getName(),rhs.getName());
    }
};

struct less_baut
{
    bool operator()(const Book & lsh, const Book & rhs)
    {
        return less<string>()(rhs.getAuthor(),lsh.getName());
    }
};

struct less_bpub
{
    bool operator()(const Book & lsh, const Book & rhs)
    {
        return less<string>()(rhs.getPub(),lsh.getPub());
    }
    
};


int get_uid();
string cin_string(const string & message = "");

template <typename FStream>
struct FileCloser
{
    FStream & _file_stream;
    FileCloser(FStream & file_stream) : _file_stream(file_stream)
    { }

    ~FileCloser()
    {
        _file_stream.close();
    }
};

#endif