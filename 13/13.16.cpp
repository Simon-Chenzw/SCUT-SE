// @problem:13.16

#include <bits/stdc++.h>

using namespace std;

class Complex {
    friend ostream& operator<<(ostream&, const Complex&);
    friend istream& operator>>(istream&, Complex&);

  private:
    int real;
    int imaginary;
};

ostream& operator<<(ostream& cout, const Complex& c) {
    if (c.real == 0 && c.imaginary == 0) {
        cout << '0';
        return cout;
    }
    if (c.real == 0) {
        cout << c.imaginary << 'i';
        return cout;
    }
    if (c.imaginary == 0) {
        cout << c.real;
        return cout;
    }
    cout << c.real << (c.imaginary < 0 ? " - " : " + ") << abs(c.imaginary) << 'i';
    return cout;
}

istream& operator>>(istream& cin, Complex& c) {
    int val;
    int k;
    cin >> val;
    if (cin.peek() == ' ') {
        c.real = val;
        cin.ignore();
        if (cin.peek() == '+')
            k = 1;
        else if (cin.peek() == '-')
            k = -1;
        else {
            cin.clear(ios::failbit);
            return cin;
        }
        cin.ignore();
        if (cin.peek() != ' ') {
            cin.clear(ios::failbit);
            return cin;
        }
        cin >> c.imaginary;
        c.imaginary *= k;
    }
    else if (cin.peek() == 'i') {
        cin.ignore();
        c.real = 0;
        c.imaginary = val;
    }
    else {
        c.real = val;
        c.imaginary = 0;
    }
    return cin;
}

int main() {
    Complex test;
    cin >> test;
    if (cin.fail())
        cout << "wrong format\n";
    else
        cout << test;
}