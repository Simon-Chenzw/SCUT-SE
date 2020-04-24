// @author chenzhuowen
// @problem 9.7

#include <bits/stdc++.h>
using namespace std;

class Time {
  public:
    explicit Time(int = 0, int = 0, int = 0);  // default constructor

    // set functions
    void setTime(int, int, int);  // set hour, minute, second
    void setHour(int);            // set hour (after validation)
    void setMinute(int);          // set minute (after validation)
    void setSecond(int);          // set second (after validation)

    // get functions
    unsigned int getHour() const;    // return hour
    unsigned int getMinute() const;  // return minute
    unsigned int getSecond() const;  // return second

    void printUniversal() const;  // output time in universal-time format
    void printStandard() const;   // output time in standard-time format

    void tick();  // increase one second

  private:
    unsigned int hour;    // 0--23 (24-hour clock format)
    unsigned int minute;  // 0--59
    unsigned int second;  // 0--59
};

// Time constructor initializes each data member
Time::Time(int hour, int minute, int second) {
    setTime(hour, minute, second);  // validate and set time
}

// set new Time value using universal time
void Time::setTime(int h, int m, int s) {
    setHour(h);    // set private field hour
    setMinute(m);  // set private field minute
    setSecond(s);  // set private field second
}

// set hour value
void Time::setHour(int h) {
    if (h >= 0 && h < 24)
        hour = h;
    else
        throw invalid_argument("hour must be 0-23");
}

// set minute value
void Time::setMinute(int m) {
    if (m >= 0 && m < 60)
        minute = m;
    else
        throw invalid_argument("minute must be 0-59");
}

// set second value
void Time::setSecond(int s) {
    if (s >= 0 && s < 60)
        second = s;
    else
        throw invalid_argument("second must be 0-59");
}

// return hour value
unsigned int Time::getHour() const { return hour; }

// return minute value
unsigned int Time::getMinute() const { return minute; }

// return second value
unsigned int Time::getSecond() const { return second; }

// print Time in universal-time format (HH:MM::SS)
void Time::printUniversal() const {
    cout << setfill('0') << setw(2) << getHour() << ":" << setw(2)
         << getMinute() << ":" << setw(2) << getSecond();
}

// print Time in standard-time format (HH:MM:SS AM or PM)
void Time::printStandard() const {
    cout << ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12) << ":"
         << setfill('0') << setw(2) << getMinute() << ":" << setw(2)
         << getSecond() << (hour < 12 ? " AM" : " PM");
}

// increase Time by one second
void Time::tick() {
    second++;
    if (second == 60) {
        second = 0;
        minute++;
    }
    if (minute == 60) {
        minute = 0;
        hour++;
    }
    if (hour == 24) hour = 0;
}

int main() {
    Time a(23, 59, 00);
    while (cin.get()) {
        a.tick();
        a.printStandard();
    }
}