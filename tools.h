#ifndef BS__TOOLS_H_
#define BS__TOOLS_H_
#include "user.h"
#include "book.h"
#include "reader.h"
#include <functional>
#include <iostream>
#include <string>
using std::string;

char getche();

using std::less;
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



#endif