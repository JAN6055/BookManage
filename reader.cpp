#include "reader.h"
#include <istream>
#include <memory>
using std::make_shared;
shared_ptr<Reader> Reader::read(ifstream & fis)
{
    int id;
    string name;
    string place;
    string contact_details;
    int flag;
    int borrowed;
    fis >> id >> name >> place >> contact_details
        >> flag >> borrowed;
    return make_shared<Reader>(id,"",name,place,contact_details,flag,borrowed);
    
}