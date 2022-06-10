//
// Created by JAN on 2022/6/10.
//
#include "lib_management_sys.h"
#include "tools.h"
int main()
{
    LibMS libMs("/home/jan/Code/BookManage/data");
    libMs.run();
    cout << libMs.findUser(11111111);
    // int id = get_uid();
    // cout << id;
  return 0;
}