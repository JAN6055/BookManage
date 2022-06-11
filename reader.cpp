#include "reader.h"
#include <istream>
#include <memory>
#include <ostream>
using std::make_shared;
using std::ostream;
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

ostream & operator<<(ostream & os, const Reader & reader)
{
    os << reader.getId() << " " << reader.getName() << " " << reader.getPlace() << " "
       << reader.getContactDetails() << " " <<  reader.getFlag() << " "
       << reader.getBorrowed();
    return os;
}