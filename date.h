#ifndef BS__DATE_H__
#define BS__DATE_H__
#include <ctime>
#include <memory>
#include <iostream>
#include <fstream>
#include <ostream>
// using std::shared_ptr;
using std::ostream;
//北京时间
enum TIME_ZONE {UCT = 8};

/**
 * @brief 该类在构造的时候自动获取当前时间，包括年月日时分秒
 * 
 */
class Date
{
public:
    //该类为一次性类,time指针指向静态返回值
    //请现用现构造
    explicit Date(char delimiter = '-') : _delimiter(delimiter)
    {
        time_t times = time(nullptr);
        //return a static obi so don't use to delete
        _time = std::localtime(&times);
    }
    
    //不可进行额外操作
    Date(const Date &) = delete;
    Date & operator=(const Date &) = delete;

    int year() const
    {
        return 1900 + _time->tm_year;
    }
    int month() const
    {
        return 1 + _time->tm_mon;
    }
    int day() const
    {
        return _time->tm_mday;
    }
    int hour(TIME_ZONE zone = TIME_ZONE::UCT) const
    {
        return (_time->tm_hour + zone) % 24;
    }
    int minute() const
    {
        return _time->tm_min;
    }

    int second() const
    {
        return _time->tm_sec;
    } 
    void outpub_front(ostream & os) const
    {
        os << year() << _delimiter << month() << _delimiter << day();
    }

    void outpub_back(ostream & os) const 
    {
        os << hour() << _delimiter << minute() << _delimiter << second();
    }

    char getDelimiter() const
    {
        return _delimiter;
    }

    //将年月日以分隔符隔开打印到流os中
    void osoffornt(ostream & os)
    {
        os << year() << _delimiter << month() << _delimiter << day();
    }
private:
    char _delimiter;
    tm * _time;
};




#endif