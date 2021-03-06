#include "lib_management_sys.h"
#include "menu.h"
#include "password.h"
#include "reader.h"
#include "tools.h"
#include "user.h"
#include "bookcirinfo.h"
#include "date.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
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
  FileCloser<ifstream> file_closer(fin);
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  User user;
  while (fin >> user) {
    _uid_map.insert({user.getId(),std::make_shared<User>(std::move(user))});
  }
}

void LibMS::writeAllUser(const string &path) {
  ofstream fout;
  FileCloser<ofstream> file_closer(fout);
  fout.open(path.c_str());
  if (!fout.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }

  for (const auto &user : _uid_map) {
      fout << *user.second << endl;
  }
}

void LibMS::readAllBook(const string &path) {
  ifstream fin;
  FileCloser<ifstream> file_closer(fin);
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  int log_id;
  shared_ptr<Book> _book;
  auto pre_fin = [&]() -> bool{
    if(!(fin >> log_id))
      return false;
    _book.reset(new Book(log_id));
    if(!(fin >> *_book))
      return false;
    return true;
  };
  while(pre_fin())
  {
    _bid_map.insert({_book->getBookId(), _book});
    _bname_map.insert({_book->getName(), weak_ptr<Book>(_book)});
    _baut_map.insert({_book->getAuthor(), weak_ptr<Book>(_book)});
    _bpub_map.insert({_book->getPub(), weak_ptr<Book>(_book)});
  }
}

void LibMS::writeAllBook(const string &path) {
  ofstream fout;
  FileCloser<ofstream> file_closer(fout);
  fout.open(path.c_str());
  if (!fout.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  for (const auto &_pair : _bid_map) {
      fout << *_pair.second << endl;
  }
}

void LibMS::readAllReader(const string &path) {
  ifstream fin;
  FileCloser<ifstream> file_closer(fin);
  fin.open(path.c_str());
  if (!fin.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  Reader reader;
  while (fin >> reader) {
    auto _reader = std::make_shared<Reader>(std::move(reader));
    _rid_map.insert({reader.getId(), _reader});
    _rname_map.insert({reader.getName(), weak_ptr<Reader>(_reader)});
  }
}

void LibMS::writeAllReader(const string &path) {
  ofstream fout;
  fout.open(path.c_str());
  if (!fout.is_open()) {
    cerr << "file" << path << "open fail" << endl;
    std::abort();
  }
  for (const auto &it : _rid_map) {
      fout << *it.second << endl;
  }
}

void LibMS::readAllBookCirInfo(const string &path) {
  ifstream fin;
  fin.open(path);
  if (!fin.is_open()) {
    cout << "file" << path << "open fail" << endl;
    std::abort();
  }
  
  string bid;
  BookCirInfo book_cir_info;
  while (fin >> bid && fin >> book_cir_info) {
    _book_cir_map.insert({bid, std::make_shared<BookCirInfo>(std::move(book_cir_info))});
  }
}

void LibMS::writeAllBookCirInfo(const string &path) {
  ofstream fout;
  FileCloser<ofstream> file_closer(fout);
  fout.open(path);
  if (!fout.is_open()) {
    cout << "file" << path << "open fail" << endl;
    std::abort();
  }

  for(const auto & it : _book_cir_map)
  {
    fout << it.first << " " << it.second->_book_tot << " " 
         << it.second->_borrowed << " "
         << it.second->_borrowed_tot << endl;
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
    cout << "?????????uid?????????" << endl;
  }
  auto finded = _uid_map.find(uid);

  if (finded == _uid_map.end()) {
    cout << "???????????????" << endl;
    return false;
  }
  for (int i = 2; i >= 0; --i) {
    string password = Password::getNew("???????????????:");
    if (password == finded->second->getPassword()) {
      _loging_user = weak_ptr<User>(finded->second);
      return true;
    } else {
      cout << "????????????,?????????" << i << "?????????" << endl;
    }
  }
  return false;
}

bool LibMS::sing_up(SING_STYLE style) {
  int uid = get_uid();
  if (uid == 0) {
    cout << "?????????uid?????????" << endl;
    return false;
  }

  auto finded = _uid_map.find(uid);
  if (finded != _uid_map.end()) {
    cout << "????????????" << endl;
    return false;
  }

  if (style == SING_STYLE::READER) {
    string name;
    cout << "???????????????:";
    cin >> name;
    string place;
    cout << "???????????????:";
    cin >> place;
    string phone;
    cout << "?????????????????????:";
    cin >> phone;
    cin.get();
    char ch;
    cout << "??????/??????(1/2)";
    ch = getch();
    ch -= 48;
    if (ch != Reader::STUDENT && ch != Reader::TEACHER) {
      cout << "????????????" << endl;
      return false;
    }
    auto reader = std::make_shared<Reader>(uid, "", name, place, phone, ch);
    if (!Password::setNewPassword(*reader)) {
      cout << "????????????" << endl;
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
    cout << "????????????" << endl;
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
      if(_loging_user.lock()->getFlag() != User::USES_ADMIN)
      {
        cout << "????????????" << endl;
        getch();
        continue;
      }
      user_manage_scence();
      break;
    case '2':
      if(_loging_user.lock()->getFlag() != User::BOOK_ADMIN)
      {
        cout << "????????????" << endl;
        getch();
        continue;
      }  
       reader_manage_scence();
      break;
    case '3':
      if(_loging_user.lock()->getFlag() != User::BOOK_ADMIN)
      {
        cout << "????????????" << endl;
        getch();
        continue;
      }
      book_manage_scence();
      break;
    case '4':
      if(_loging_user.lock()->User::getFlag() != User::READER)
      {
        cout << "???????????????" << endl;
        getch();
        continue;
      }
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
        cout << "?????????uid?????????" << endl;
        getch();
        continue;
      }
      auto finded = _uid_map.find(uid);
      if (finded == _uid_map.end()) {
        cout << "??????????????????" << endl;
        continue;
      }
      user_info_change_scence(*finded->second);
    } break;
    case '3':
      // delete a user
      {

        int uid = get_uid();
        if (uid == 0) {
          cout << "?????????uid?????????" << endl;
          getch();
          continue;
        }
        auto finded = _uid_map.find(uid);
        if (finded == _uid_map.end()) {
          cout << "??????????????????" << endl;
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
        cout << "??????????????????uid" << endl;
        getch();
        continue;
      }
      auto finded = _rid_map.find(uid);
      if (finded == _rid_map.end()) {
        cout << "??????????????????" << endl;
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
          cout << "?????????uid?????????" << endl;
          getch();
          continue;
        }
        auto finded = _rid_map.find(uid);
        if (finded == _rid_map.end()) {
          cout << "???????????????" << endl;
          getch();
          continue;
        }
        _uid_map.erase(uid);
        _rid_map.erase(uid);
        _rname_map.erase(finded->second->getName());
        cout << "????????????" << endl;
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
        cout << "??????????????????????????????????????????" << endl;
        shared_ptr<Book> book = std::make_shared<Book>(Book::_book_tot + 1);
        cin >> *book;
        cin.get();
        _bid_map.insert({book->getBookId(), book});
        _bname_map.insert({book->getName(), weak_ptr<Book>(book)});
        _baut_map.insert({book->getAuthor(), weak_ptr<Book>(book)});
        _bpub_map.insert({book->getPub(), weak_ptr<Book>(book)});
        _book_cir_map.insert({book->getBookId(),std::make_shared<BookCirInfo>(1,0,0)});
        cout << "????????????" << endl;
        getch();
      }
      break;
    case '2': {
      cout << "?????????????????????bid" << endl;
      string bid = cin_string();
      auto finded = _bid_map.find(bid);
      if (finded == _bid_map.end()) {
        cout << "???????????????" << endl;
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
      {
        for (const auto &it : _book_cir_map) {
          cout << it.first << " ";
          cout << *it.second << endl;
        }
        getch();
      }
      break;
    case '5':
      return;
    }
  }
}
void LibMS::book_stream_scence() {
  while (true) {
    book_stream_menu();
    ofstream fout;
    fout.open(_data_path + CIR_LOG, std::ios_base::app);
    if(!fout.is_open())
    {
      cout << "file" << _data_path + CIR_LOG << " open fail" << endl;
      std::abort();
    }
    char ch = getch();
    switch (ch) {
    case '1':
      // borrow a book
      {
        string rid = cin_string("?????????bid");
        auto finded = _book_cir_map.find(rid);
        if(finded == _book_cir_map.end())
        {
          cout << "???????????????" << endl;
          getch();
          continue;
        }
        auto book_cir_info = finded->second;
        if(book_cir_info->_borrowed >= book_cir_info->_book_tot)
        {
          cout << "?????????????????????" << endl;
          getch();
          continue;
        }
        auto tmp = _rid_map.find(_loging_user.lock()->getId());
        if(tmp->second->getAbleBorrow() == 0)
        {
          cout << "??????????????????" << endl;
          getch();
          continue;
        }
        book_cir_info->_borrowed_tot++;
        book_cir_info->_borrowed++;
        
        cout << "---" << endl;
        _rid_map[_loging_user.lock()->getId()]->borrowedUp();
        fout << _loging_user.lock()->getId() << " " << rid << " ";
        Date().osoffornt(fout);
        fout << " " << "??????"<< endl;
        cout << "????????????" << endl;
        getch();
      }
      break;
    case '2':
      // return a book
      {
        string rid = cin_string("?????????bid");
        auto finded = _book_cir_map.find(rid);
        if(finded == _book_cir_map.end())
        {
          cout << "???????????????" << endl;
          getch();
          continue;
        }
        auto reader = _rid_map.find(_loging_user.lock()->getId());
        if(reader->second->getBorrowed() == 0)
        {
          cout << "?????????????????????" << endl;
          getch();
          continue;
        }
        finded->second->_borrowed--;
        reader->second->borrowedDown();
        fout << _loging_user.lock()->getId() << " " << rid <<" ";
        Date().osoffornt(fout);
        fout << " ??????" << endl;
        cout << "????????????" << endl;
        getch();
      }
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
      cout << "?????????uid?????????" << endl;
      getch();
      continue;
    }
    auto finded = _uid_map.find(uid);
    if (finded == _uid_map.end()) {
      cout << "??????????????????" << endl;
      getch();
      continue;
    }

    char ch = getch();
    switch (ch) {
    case '1':
      // change password
      if (Password::setNewPassword(*finded->second)) {
        cout << "?????????????????????" << endl;
        getch();
      }
    case '2':
      // change flag
      {
        cout << "user admin/book admin(1/2)";
        char ch = getch();
        ch -= 48;
        if (ch != User::USES_ADMIN && ch != User::BOOK_ADMIN) {
          cout << "????????????" << endl;
          getch();
          break;
        }
        finded->second->setFlag(ch);
        cout << "????????????" << endl;
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
      reader.setName(cin_string("??????????????????"));
      cout << "????????????" << endl;
      getch();
      break;
    case '2':
      // place
      {
        reader.setPlace(cin_string("?????????????????????:"));
        cout << "????????????" << endl;
        getch();
      }
      break;
    case '3':
      // phone
      reader.setCon(cin_string("?????????????????????????????????:"));
      cout << "????????????" << endl;
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
        string bid = cin_string("?????????bid");
        auto finded = _bid_map.find(bid);
        if (finded == _bid_map.end()) {
          cout << "???????????????" << endl;
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
        string name = cin_string("???????????????");
        auto range = _bname_map.equal_range(name);
        auto first = range.first, last = range.second;
        if (first == last) {
          cout << "???????????????" << endl;
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
        string aut = cin_string("???????????????");
        auto range = _baut_map.equal_range(aut);
        auto first = range.first, last = range.second;
        if (first == last) {

          cout << "???????????????" << endl;
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
        string pub = cin_string("??????????????????");
        auto range = _bpub_map.equal_range(pub);
        auto first = range.first, last = range.second;
        if (first == last) {
          cout << "???????????????" << endl;
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
      book.setName(cin_string("???????????????"));
      break;
    case '2':
      // author
      book.setAuthor(cin_string("???????????????"));
      break;
    case '3':
      // pub
      book.setPub(cin_string("??????????????????"));
      break;
    case '4':
      // book_tot
      {
        int tot;
        cout << "??????????????????" << endl;
        cin >> tot;
        cin.get();
        _book_cir_map[book.getBookId()]->_book_tot = tot;
      }
      break;
    case '5':
      return;
    }
    cout << "????????????" << endl;
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
        cout << "?????????uid?????????" << endl;
        getch();
        continue;
      }
      auto finded = _rid_map.find(uid);
      if (finded == _rid_map.end()) {
        cout << "????????????????????????" << endl;
        getch();
        continue;
      }
      cout << *finded->second << endl;
      getch();
    } break;
    case '2': {
      string name;
      cout << "???????????????" << endl;
      cin >> name;
      cin.get();
      auto finded_pair = _rname_map.equal_range(name);
      if (_rname_map.find(name) == _rname_map.end()) {
        cout << "????????????" << endl;
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