// @file: Date.h

#ifndef DATE_H
#define DATE_H

#include <array>
#include <iostream>

class Date {
    friend std::ostream& operator<<(std::ostream&, const Date&);

  public:
    Date(int m = 1, int d = 1, int y = 1900);
    void setDate(int, int, int);
    Date& operator++();
    Date operator++(int);
    Date& operator+=(unsigned int);
    static bool leapYear(int);
    bool endOfMonth(int) const;
    int getMonth() const;

  private:
    unsigned int month;
    unsigned int day;
    unsigned int year;

    static const std::array<unsigned int, 13> days;
    void helpIncrement();
};

#endif