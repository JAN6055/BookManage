#include "lib_management_sys.h"
#include "menu.h"
#include "password.h"
#include "reader.h"
#include "tools.h"
#include "user.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <pthread.h>
#include <string>

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

void LibMS::writeAllUser(const string &path) {
  ofstream fout;
  fout.open(path.c_str());
  if (!fout.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  int i = 0;
  int size = _uid_map.size();
  for (const auto &user : _uid_map) {
    if (++i == size)
      fout << *user.second;
    else
      fout << *user.second << endl;
  }
}

void LibMS::readAllBook(const string &path) {
  ifstream fin;
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  while (!fin.eof()) {
    int log_id;
    fin >> log_id;
    auto _book = std::make_shared<Book>(log_id);
    fin >> *_book;
    _bid_map.insert({_book->getBookId(), _book});
    _bname_map.insert({_book->getName(), weak_ptr<Book>(_book)});
    _baut_map.insert({_book->getAuthor(), weak_ptr<Book>(_book)});
    _bpub_map.insert({_book->getPub(), weak_ptr<Book>(_book)});
  }
  fin.close();
}

void LibMS::writeAllBook(const string &path) {
  ofstream fout;
  fout.open(path.c_str());
  if (!fout.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }

  auto size = _bid_map.size();
  int i = 0;
  for (const auto &_pair : _bid_map) {
    if (++i == size)
      fout << *_pair.second;
    else
      fout << *_pair.second << endl;
  }
  fout.close();
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
    _rid_map.insert({reader->getId(), reader});
    _rname_map.insert({reader->getName(), weak_ptr<Reader>(reader)});
  }
}

void LibMS::writeAllReader(const string &path) {
  ofstream fout;
  fout.open(path.c_str());
  if (!fout.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  auto size = _rid_map.size();
  int i = 0;
  for (const auto &it : _rid_map) {
    cout << "write a" << endl;
    if (++i == size)
      fout << *it.second;
    else
      fout << *it.second << endl;
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
      if (sing_up(SING_STYLE::NO_READER))
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

bool LibMS::sing_up(SING_STYLE style) {
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

  if (style == SING_STYLE::READER) {
    string name;
    cout << "请输入姓名:";
    cin >> name;
    string place;
    cout << "请输入住址:";
    cin >> place;
    string phone;
    cout << "请输入联系方式:";
    cin >> phone;
    cin.get();
    char ch;
    cout << "教工/学生(1/2)";
    ch = getch();
    ch -= 48;
    if (ch != Reader::STUDENT && ch != Reader::TEACHER) {
      cout << "输入违法" << endl;
      return false;
    }
    auto reader = std::make_shared<Reader>(uid, "", name, place, phone, ch);
    if (!Password::setNewPassword(*reader)) {
      cout << "违法输入" << endl;
      return false;
    }
    _uid_map.insert({uid, std::make_shared<User>(uid, reader->getPassword(),
                                                 User::READER)});
    _rid_map.insert({uid, reader});
    _rname_map.insert({reader->getName(), weak_ptr<Reader>(reader)});
    return true;
  }
  cout << "user admin/book admin(1/2)" << endl;

  char flag = getch();
  flag -= 48;
  if (flag < User::USES_ADMIN || flag > User::BOOK_ADMIN) {
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
      // add new user
      if (sing_up())
        cout << "\nsing up success" << endl;
      getch();
      break;
    case '2': {
      int uid = get_uid();
      if (uid == 0) {
        cout << "输入的uid不合法" << endl;
        getch();
        continue;
      }
      auto finded = _uid_map.find(uid);
      if (finded == _uid_map.end()) {
        cout << "不存在此用户" << endl;
        continue;
      }
      user_info_change_scence(*finded->second);
    } break;
    case '3':
      // delete a user
      {

        int uid = get_uid();
        if (uid == 0) {
          cout << "输入的uid不合法" << endl;
          getch();
          continue;
        }
        auto finded = _uid_map.find(uid);
        if (finded == _uid_map.end()) {
          cout << "不存在此用户" << endl;
          continue;
        }
        _uid_map.erase(uid);
        if (finded->second->getFlag() == User::READER) {
          int uid = finded->second->getId();
          string name = _rid_map[uid]->getName();
          _rid_map.erase(uid);
          _rname_map.erase(name);
        }
      }
      break;
    case '4':
      // view all user
      for (const auto &user : _uid_map) {
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
      if (sing_up())
        cout << "sing up success" << endl;
      getch();

      break;
    case '2': {
      int uid = get_uid();
      if (uid == 0) {
        cout << "请输入合法的uid" << endl;
        getch();
        continue;
      }
      auto finded = _rid_map.find(uid);
      if (finded == _rid_map.end()) {
        cout << "不存在该用户" << endl;
        getch();
        continue;
      }
      reader_info_change_scence(*finded->second);
    } break;
    case '3':
      // delete a reader
      {
        int uid = get_uid();
        if (uid == 0) {
          cout << "输入的uid不合法" << endl;
          getch();
          continue;
        }
        auto finded = _rid_map.find(uid);
        if (finded == _rid_map.end()) {
          cout << "没有此用户" << endl;
          getch();
          continue;
        }
        _uid_map.erase(uid);
        _rid_map.erase(uid);
        _rname_map.erase(finded->second->getName());
        cout << "删除成功" << endl;
        getch();
      }
      break;
    case '4':
      // serch a reader
      reader_info_serch_scence();
      break;
    case '5':
      // view all reader
      for (const auto &it : _rid_map) {
        cout << *it.second << endl;
      }
      getch();
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
      {
        cout << "请以此输入书号书名作者出版社" << endl;
        shared_ptr<Book> book = std::make_shared<Book>(Book::_book_tot + 1);
        cin >> *book;
        cin.get();
        _bid_map.insert({book->getBookId(), book});
        _bname_map.insert({book->getName(), weak_ptr<Book>(book)});
        _baut_map.insert({book->getAuthor(), weak_ptr<Book>(book)});
        _bpub_map.insert({book->getPub(), weak_ptr<Book>(book)});
        cout << "添加成功" << endl;
        getch();
      }
      break;
    case '2': {
      cout << "请输入要修改的bid" << endl;
      string bid = cin_string();
      auto finded = _bid_map.find(bid);
      if(finded ==  _bid_map.end())
      {
        cout << "没有这本书" << endl;
        getch();
        continue;
      }
      book_info_change_scence(*finded->second);
    }
    // book_info_change_scence(Book());
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

void LibMS::user_info_change_scence(User &user) {
  while (true) {
    user_info_change_menu();
    int uid = get_uid();
    if (uid == 0) {
      cout << "输入的uid不合法" << endl;
      getch();
      continue;
    }
    auto finded = _uid_map.find(uid);
    if (finded == _uid_map.end()) {
      cout << "不存在该用户" << endl;
      getch();
      continue;
    }

    char ch = getch();
    switch (ch) {
    case '1':
      // change password
      if (Password::setNewPassword(*finded->second)) {
        cout << "设置新密码成功" << endl;
        getch();
      }
    case '2':
      // change flag
      {
        cout << "user admin/book admin(1/2)";
        char ch = getch();
        ch -= 48;
        if (ch != User::USES_ADMIN && ch != User::BOOK_ADMIN) {
          cout << "违法输入" << endl;
          getch();
          break;
        }
        finded->second->setFlag(ch);
        cout << "修改成功" << endl;
        getch();
      }
      break;
    case '3':
      return;
    }
  }
}
void LibMS::reader_info_change_scence(Reader &reader) {
  while (true) {
    reader_info_change_menu();
    char ch = getch();
    switch (ch) {
    case '1':
      // name
      reader.setName(cin_string("请输入新名字"));
      cout << "修改成功" << endl;
      getch();
      break;
    case '2':
      // place
      {
        reader.setPlace(cin_string("请输入新的住址:"));
        cout << "修改成功" << endl;
        getch();
      }
      break;
    case '3':
      // phone
      reader.setCon(cin_string("请输入一个新的联系方式:"));
      cout << "修改成功" << endl;
      getch();
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
      {
        string bid = cin_string("请输入bid");
        auto finded = _bid_map.find(bid);
        if (finded == _bid_map.end()) {
          cout << "没有这本书" << endl;
          getch();
          continue;
        }
        cout << *finded->second;
        getch();
      }
      break;
    case '2':
      // book_name
      {
        string name = cin_string("请输入书名");
        auto range = _bname_map.equal_range(name);
        auto first = range.first, last = range.second;
        if (first == last) {
          cout << "没有这本书" << endl;
          getch();
          continue;
        }
        for (auto it = first; it != last; ++it) {
          cout << *it->second.lock() << endl;
        }
        getch();
      }
      break;
    case '3':
      // author
      {
        string aut = cin_string("请输入作者");
        auto range = _baut_map.equal_range(aut);
        auto first = range.first, last = range.second;
        if (first == last) {

          cout << "没有这本书" << endl;
          getch();
          continue;
        }
        for (auto it = first; it != last; ++it) {
          cout << *it->second.lock() << endl;
        }
        getch();
      }
      break;
    case '4':
      // pub
      {
        string pub = cin_string("请输入出版社");
        auto range = _bpub_map.equal_range(pub);
        auto first = range.first, last = range.second;
        if (first == last) {
          cout << "没有这本书" << endl;
          getch();
          continue;
        }
        for (auto it = first; it != last; ++it) {
          cout << *it->second.lock() << endl;
        }
        getch();
      }
      break;
    case '5':
      return;
    }
  }
}
void LibMS::book_info_change_scence(Book &book) {
  while (true) {
    book_info_change_menu();

    char ch = getch();
    switch (ch) {
    case '1':
      // name
      book.setName(cin_string("请输入书名"));
      break;
    case '2':
      // author
      book.setAuthor(cin_string("请输入作者"));
      break;
    case '3':
      // pub
      book.setPub(cin_string("请输入出版社"));
      break;
    case '4':
      // book_tot
      {

      }
      break;
    case '5':
      return;
    }
    cout << "修改成功" << endl;
    getch();
  }
}

void LibMS::reader_info_serch_scence() {
  while (true) {
    reader_info_serch_menu();
    char ch = getch();
    switch (ch) {
    case '1': {
      int uid = get_uid();
      if (uid == 0) {
        cout << "输入的uid不合法" << endl;
        getch();
        continue;
      }
      auto finded = _rid_map.find(uid);
      if (finded == _rid_map.end()) {
        cout << "没有查找到此读者" << endl;
        getch();
        continue;
      }
      cout << *finded->second << endl;
      getch();
    } break;
    case '2': {
      string name;
      cout << "请输入姓名" << endl;
      cin >> name;
      cin.get();
      auto finded_pair = _rname_map.equal_range(name);
      if (_rname_map.find(name) == _rname_map.end()) {
        cout << "没有找到" << endl;
        getch();
        continue;
      }
      for (auto it = finded_pair.first; it != finded_pair.second; ++it) {
        cout << *it->second.lock() << endl;
      }
      getch();
    } break;
    case '3':
      return;
    }
  }
}