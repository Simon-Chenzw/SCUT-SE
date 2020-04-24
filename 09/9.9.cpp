// @author chenzhuowen
// @problem 9.9

#include <bits/stdc++.h>
using namespace std;

class DateAndTime {
  public:
    explicit DateAndTime(int = 1,
                         int = 1,
                         int = 2000,
                         int = 0,
                         int = 0,
                         int = 0);  // default constructor

    // set functions
    void setDate(int, int, int);  // set month day year
    void setTime(int, int, int);  // set hour, minute, second
    void setHour(int);            // set hour (after validation)
    void setMinute(int);          // set minute (after validation)
    void setSecond(int);          // set second (after validation)

    // get functions
    unsigned int getHour() const;    // return hour
    unsigned int getMinute() const;  // return minute
    unsigned int getSecond() const;  // return second

    void print() const;           // print DateAndTime
    void printUniversal() const;  // output time in universal-time format
    void printStandard() const;   // output time in standard-time format

    void tick();     // increase one second
    void nextDay();  // increase DateAndTime by one day

  private:
    unsigned int hour;    // 0--23 (24-hour clock format)
    unsigned int minute;  // 0--59
    unsigned int second;  // 0--59
    unsigned int month;
    unsigned int day;
    unsigned int year;
    unsigned int max_day() const;  // return max day in this month
};

// DateAndTime constructor initializes each data member
DateAndTime::DateAndTime(int month,
                         int day,
                         int year,
                         int hour,
                         int minute,
                         int second) {
    setTime(hour, minute, second);  // validate and set time
    setDate(month, day, year);
}

// set new Date
void DateAndTime::setDate(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
    if (year <= 0) throw invalid_argument("invalid argument year");
    if (month <= 0 || month > 12)
        throw invalid_argument("invalid argument month");
    if (day <= 0 || day > max_day())
        throw invalid_argument("invalid argument day");
}

// set new Time value using universal time
void DateAndTime::setTime(int h, int m, int s) {
    setHour(h);    // set private field hour
    setMinute(m);  // set private field minute
    setSecond(s);  // set private field second
}

// set hour value
void DateAndTime::setHour(int h) {
    if (h >= 0 && h < 24)
        hour = h;
    else
        throw invalid_argument("hour must be 0-23");
}

// set minute value
void DateAndTime::setMinute(int m) {
    if (m >= 0 && m < 60)
        minute = m;
    else
        throw invalid_argument("minute must be 0-59");
}

// set second value
void DateAndTime::setSecond(int s) {
    if (s >= 0 && s < 60)
        second = s;
    else
        throw invalid_argument("second must be 0-59");
}

// return hour value
unsigned int DateAndTime::getHour() const { return hour; }

// return minute value
unsigned int DateAndTime::getMinute() const { return minute; }

// return second value
unsigned int DateAndTime::getSecond() const { return second; }

// print Datein the format mm/dd/yyyy
void DateAndTime::print() const { cout << month << '/' << day << '/' << year; }

// print DateAndTime in universal-time format (mm/dd/yyyy HH:MM::SS)
void DateAndTime::printUniversal() const {
    print();
    cout << ' ' << setfill('0') << setw(2) << getHour() << ":" << setw(2)
         << getMinute() << ":" << setw(2) << getSecond();
}

// print DateAndTime in standard-time format (mm/dd/yyyy HH:MM:SS AM or PM)
void DateAndTime::printStandard() const {
    print();
    cout << ' ' << ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12)
         << ":" << setfill('0') << setw(2) << getMinute() << ":" << setw(2)
         << getSecond() << (hour < 12 ? " AM" : " PM");
}

// increase DateAndTime by one second
void DateAndTime::tick() {
    second++;
    if (second == 60) {
        second = 0;
        minute++;
    }
    if (minute == 60) {
        minute = 0;
        hour++;
    }
    if (hour == 24) {
        hour = 0;
        nextDay();
    }
}

// increase DateAndTime by one second
void DateAndTime::nextDay() {
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
unsigned int DateAndTime::max_day() const {
    static const unsigned int days[13] = {0,  31, 28, 31, 30, 31, 30,
                                          31, 31, 30, 31, 30, 31};
    if (month != 2) return days[month];
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return days[2] + 1;
    else
        return days[2];
}