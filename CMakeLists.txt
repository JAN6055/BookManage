cmake_minimum_required(VERSION 3.10)

project(BookManage)

add_executable(BookManage main.cpp book.cpp
        lib_management_sys.cpp menu.cpp password.cpp tools.cpp
        user.cpp reader.cpp bookcirinfo.cpp)

