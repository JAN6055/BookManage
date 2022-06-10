#include "lib_management_sys.h"
#include "menu.h"
#include "tools.h"
#include "user.h"
#include <cctype>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <pthread.h>

using std::cin;
using std::ifstream;
using std::ofstream;
// using std::make_shared;
using std::cerr;
void LibMS::readAllUser(const string &path) {
  ifstream fin;
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  while (!fin.eof()) {
    shared_ptr<User> user(User::read(fin));
    _uid_map.insert({user->getId(), user});
  }
  fin.close();
}

void LibMS::writeAllUser(const string & path)
{
    ofstream fout;
    fout.open(path.c_str());
    if(!fout.is_open())
    {
        cerr << "file" << path << "open fail" << endl;
        std::abort();
    }
    int i=0;
    int size = _uid_map.size();
    for(const auto & user : _uid_map)
    {
        if(++i == size)
        fout << *user.second;
        else
            fout << *user.second << endl;
    }
}

void LibMS::readAllBook(const string &path) {
  ifstream fin;
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << endl;
    std::abort();
  }
  while (!fin.eof()) {
    auto book = new Book(++Book::_book_tot);
    fin >> *book;
    shared_ptr<Book> _book(book);
    _bid_map.insert({_book->getBookId(), _book});
    _bname_map.insert({_book->getName(), weak_ptr<Book>(_book)});
    _baut_map.insert({book->getAuthor(), weak_ptr<Book>(_book)});
    _bpub_map.insert({book->getPub(), weak_ptr<Book>(_book)});
  }
}

void LibMS::readAllReader(const string &path) {
  ifstream fin;
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  while (!fin.eof()) {
    shared_ptr<Reader> reader(Reader::read(fin));
    _rid_map.insert({reader->getId(),reader});
    _rname_map.insert({reader->getName(), reader});
  }
}

void LibMS::run() {
  while (true) {
    start_menu();
    char ch;
    ch = getch();
    if (ch == '1') {
      if (log_in()) {
        cout << "\nlog in success" << endl;
        getch();
        main_scence();
      }
    } else if (ch == '2') {
      if (sing_up())
        cout << "sing in success" << endl;
      getch();
    } else if (ch == '3') {
      return;
    } else
      continue;
  }
}

bool LibMS::log_in() {

  int uid = get_uid();
  if (uid == 0) {
    cout << "输入的uid不合法" << endl;
  }
  auto finded = _uid_map.find(uid);

  if (finded == _uid_map.end()) {
    cout << "用户不存在" << endl;
    return false;
  }
  for (int i = 2; i >= 0; --i) {
    string password = Password::getNew("请输入密码:");
    if (password == finded->second->getPassword()) {
      _loging_user = weak_ptr<User>(finded->second);
      return true;
    } else {
      cout << "密码错误,你还有" << i << "次机会" << endl;
    }
  }
  return false;
}

bool LibMS::sing_up() {
  int uid = get_uid();
  if (uid == 0) {
    cout << "输入的uid不合法" << endl;
    return false;
  }

  auto finded = _uid_map.find(uid);
  if (finded != _uid_map.end()) {
    cout << "账号重复" << endl;
    return false;
  }
  cout << "以哪种权限注册(1/2/3)" << endl;
  char flag = getch();
  flag -= 48;
  if (flag < User::USES_ADMIN || flag > User::READER) {
    cout << "违法输入" << endl;
    return false;
  }

  shared_ptr<User> user = std::make_shared<User>(uid, "", flag);
  if (Password::setNewPassword(*user)) {
    _uid_map.insert({uid, user});
    return true;
  }
  return false;
}

void LibMS::main_scence() {
  while (true) {
    main_menu();
    char ch = getch();
    switch (ch) {
    case '1':
      user_manage_scence();
      break;
    case '2':
      reader_manage_scence();
      break;
    case '3':
      book_manage_scence();
      break;
    case '4':
      book_stream_scence();
      break;
    case '5':
      return;
    }
  }
}
void LibMS::user_manage_scence() {
  while (true) {
    user_man_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      //add new user
      if(sing_up())
        cout << "\nsing up success" << endl;
        getch();
      break;
    case '2':
      user_info_change_scence();
      break;
    case '3':
      // delete a user
      {

      int uid = get_uid();
      auto finded = _uid_map.find(uid);
      if(finded == _uid_map.end())
      {
        cout << "不存在此用户" << endl;
      }
      _uid_map.erase(uid);
      if(finded->second->getFlag() == User::READER)
      {
        int uid = finded->second->getId();
        string name = _rid_map[uid]->getName();
        _rid_map.erase(uid);
        _rname_map.erase(name);
      }
      }
      break;
    case '4':
      // view all user
      for(const auto & user : _uid_map)
      {
        cout << *user.second << endl;
      }
      getch();
      break;
    case '5':
      return;
    }
  }
}
void LibMS::reader_manage_scence() {
  while (true) {
    reader_man_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // sing up a reader
      break;
    case '2':
      reader_info_change_scence();
      break;
    case '3':
      // delete a reader
      break;
    case '4':
      // serch a reader
      break;
    case '5':
      // view all reader
      break;
    case '6':
      return;
    }
  }
}
void LibMS::book_manage_scence() {
  while (true) {
    book_man_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // input book
      break;
    case '2':
      book_info_change_scence();
      break;
    case '3':
      book_serch_scence();
      break;
    case '4':
      // tot
      break;
    case '5':
      return;
    }
  }
}
void LibMS::book_stream_scence() {
  while (true) {
    book_stream_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // borrow a book
      break;
    case '2':
      // return a book
      break;
    case '3':
      return;
    }
  }
}

void LibMS::user_info_change_scence() {
  while (true) {
    user_info_change_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // change password
      break;
    case '2':
      // change flag
      break;
    case '3':
      return;
    }
  }
}
void LibMS::reader_info_change_scence() {
  while (true) {
    reader_info_change_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // name
      break;
    case '2':
      // place
      break;
    case '3':
      // phone
      break;
    case '4':
      return;
    }
  }
}
void LibMS::book_serch_scence() {
  while (true) {
    book_info_serch_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // book_id
      break;
    case '2':
      // book_name
      break;
    case '3':
      // author
      break;
    case '4':
      // pub
      break;
    case '5':
      return;
    }
  }
}
void LibMS::book_info_change_scence() {
  while (true) {
    book_info_change_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // name
      break;
    case '2':
      // author
      break;
    case '3':
      // pub
      break;
    case '4':
      // book_tot
      break;
    case '5':
      return;
    }
  }
}