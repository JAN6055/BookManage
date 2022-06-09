#include "lib_management_sys.h"
#include <cstdlib>
#include <fstream>
#include <exception>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::cerr;
void readAllUser(const string & path)
{
    ifstream fin;
    fin.open((path + USER_DATA).c_str());
    if(!fin.is_open())
    {
        cerr << "file" << path + USER_DATA << "open fail" << endl;
        std::abort();
    }
    
    
}
