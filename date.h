#ifndef BS__DATE_H__
#define BS__DATE_H__
#include <ctime>
#include <memory>
#include <iostream>
#include <fstream>
#include <ostream>
using std::shared_ptr;
using std::ostream;
enum TIME_ZONE {UCT = 8};
class Date
{
public:
    explicit Date(char delimiter = '-') : _delimiter(delimiter)
    {
        time_t times = time(nullptr);
        _time = std::make_shared<tm>(std::localtime(&times));
    }
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
private:
    char _delimiter;
    shared_ptr<tm> _time;
};

ostream & operator<<(ostream & os, const Date & date);



#endif