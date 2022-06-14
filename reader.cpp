#include "reader.h"
#include <fstream>
#include <istream>
#include <memory>
#include <ostream>
using std::ostream;
using std::ifstream;

ifstream & operator>>(ifstream & fin, Reader & reader)
{
    fin >> reader._id >> reader._name >> reader._place >> reader._contact_details
        >> reader._flag >> reader._borrowed;
    return fin;
}

ostream & operator<<(ostream & os, const Reader & reader)
{
    os << reader.getId() << " " 
       << reader.getName() << " "
       << reader.getPlace() << " "
       << reader.getContactDetails() << " "
       << reader.getFlag() << " "
       << reader.getBorrowed();
    return os;
}