// @problem:13.15

#include <bits/stdc++.h>

using namespace std;

class Point {
    friend ostream& operator<<(ostream&, const Point&);
    friend istream& operator>>(istream&, Point&);

  private:
    int xCoordinate;
    int yCoordinate;
};

ostream& operator<<(ostream& cout, const Point& p) {
    cout << '(' << p.xCoordinate << ',' << p.yCoordinate << ')';
    return cout;
}

istream& operator>>(istream& cin, Point& p) {
    if (cin.peek() != '(') {
        cin.clear(ios::failbit);
        return cin;
    }
    else
        cin.ignore();
    cin >> p.xCoordinate;
    if (cin.peek() != ',') {
        cin.clear(ios::failbit);
        return cin;
    }
    else
        cin.ignore();
    cin >> p.yCoordinate;
    if (cin.peek() != ')') {
        cin.clear(ios::failbit);
        return cin;
    }
    else
        cin.ignore();
    return cin;
}

int main() {
    Point test;
    cin >> test;
    if (cin.fail())
        cout << "wrong format\n";
    else
        cout << test;
}