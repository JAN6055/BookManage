//
// Created by JAN on 2022/6/10.
//

#include "lib_management_sys.h"
#include "tools.h"
#include "date.h"
void testDate()
{
  Date().osoffornt(cout);
}
int main()
{
    LibMS libMs("/home/jan/Code/BookManage/data");
    libMs.run();
  // testDate();
  return 0;
}