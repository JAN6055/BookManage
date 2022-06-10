#include <stdio.h>
#include <stdlib.h>
 
#include "menu.h"
 
 
void main_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.用户管理\n");
    printf("\t2.读者管理\n");
    printf("\t3.图书管理\n");
    printf("\t4.图书流通管理\n");
    printf("\t5.退出系统\n");
    printf("+-----------------------+\n");
}
//_1
void user_man_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.用户信息输入\n");
    printf("\t2.用户信息修改.\n");
    printf("\t3.用户信息删除\n");
    printf("\t4.用户信息显示\n");
    printf("\t5.返回主菜单\n");
    printf("+-----------------------+\n");
}
 
void user_info_change_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.修改密码\n");
    printf("\t2.修改权限\n");
    printf("\t3.退出\n");
    printf("+-----------------------+\n");
 
}
void reader_info_change_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.姓名\n");
    printf("\t2.地址\n");
    printf("\t3.电话号码\n");
    printf("\t4.退出\n");
    printf("+-----------------------+\n");
}
//_2
void reader_man_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.新建读者\n");
    printf("\t2.读者信息修改\n");
    printf("\t3.读者信息删除\n");
    printf("\t4.读者信息查询\n");
    printf("\t5.读者信息显示\n");
    printf("\t6.返回主菜单\n");
    printf("+-----------------------+\n");
}
//_3
void book_man_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.图书信息输入\n");
    printf("\t2.图书信息修改\n");
    printf("\t3.图书信息查询\n");
    printf("\t4.汇总统计\n");
    printf("\t5.返回主菜单\n");
    printf("+-----------------------+\n");
}
 
void book_view_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.按书名号查询\n");
    printf("\t2.按书名查询\n");
    printf("\t3.按作者查询\n");
    printf("\t4.按出版社查询\n");
    printf("\t5.返回主菜单\n");
    printf("+-----------------------+\n");
}
 
//_4
void book_stream_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.借书处理\n");
    printf("\t2.还书处理\n");
    printf("\t3.返回主菜单\n");
    printf("+-----------------------+\n");
}
 
 
 
void regmode_menu()
{
    system("clear");
    printf("+----------模式---------+\n");
    printf("\t0.教工");
    printf("\t1.学生\n");
    printf("\t2.图书管理员\n");
    printf("\t3.系统管理员\n");
    printf("+-----------------------+\n");
}
 
void start_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("1.\t登陆\n");
    printf("2.\t注册\n");
    printf("3.\t退出\n");
    printf("+-----------------------+\n");
}
 
void book_info_change_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.修改书名\n");
    printf("\t2.修改作者\n");
    printf("\t3.修改出版社\n");
    printf("\t4.修改藏书量\n");
    printf("\t5.退出\n");
    printf("+-----------------------+\n");
}
 
void book_info_serch_menu()
{
    system("clear");
    printf("+-----------------------+\n");
    printf("\t1.按书号查询\n");
    printf("\t2.按书名查询\n");
    printf("\t3.按作者查询\n");
    printf("\t4.按出版社查询\n");
    printf("\t5.返回\n");
    printf("+-----------------------+\n");
}