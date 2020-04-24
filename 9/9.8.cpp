// @author chenzhuowen
// @problem 9.8

#include <bits/stdc++.h>
using namespace std;

class Date {
  public:
    explicit Date(int = 1, int = 1, int = 2000);  // default constructor
    void print() const;                           // print Date
    void nextDay();                               // increase Date by one day
  private:
    unsigned int month;
    unsigned int day;
    unsigned int year;
    unsigned int max_day() const;  // return max day in this month
};

// Date constructor
Date::Date(int m, int d, int y)
    : month(m)
    , day(d)
    , year(y) {
    if (year <= 0) throw invalid_argument("invalid argument year");
    if (month <= 0 || month > 12)
        throw invalid_argument("invalid argument month");
    if (day <= 0 || day > max_day())
        throw invalid_argument("invalid argument day");
}

// print Date in the format mm/dd/yyyy
void Date::print() const { cout << month << '/' << day << '/' << year; }

// increase Date by one second
void Date::nextDay() {
    day++;
    if (day > max_day()) {
        day = 1;
        month++;
    }
    if (month > 12) {
        month = 1;
        year++;
    }
}

// return max day in this month
unsigned int Date::max_day() const {
    static const unsigned int days[13] = {0,  31, 28, 31, 30, 31, 30,
                                          31, 31, 30, 31, 30, 31};
    if (month != 2) return days[month];
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return days[2] + 1;
    else
        return days[2];
}