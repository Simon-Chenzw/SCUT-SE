/**
 *  @brief:code of 10.8
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
using namespace std;

class Complex {
  public:
    Complex(double = 0.0, double = 0.0);
    Complex operator+(const Complex&) const;
    Complex operator-(const Complex&) const;
    Complex operator*(const Complex&)const;
    bool operator==(const Complex&) const;
    bool operator!=(const Complex&) const;
    friend ostream& operator<<(ostream&, const Complex&);
    friend istream& operator>>(istream&, Complex&);

  private:
    double real;
    double imaginary;
};

Complex::Complex(double realPart, double imaginaryPart): real(realPart), imaginary(imaginaryPart) {}

Complex Complex::operator+(const Complex& val) const {
    return Complex(real + val.real, imaginary + val.imaginary);
}

Complex Complex::operator-(const Complex& val) const {
    return Complex(real - val.real, imaginary - val.imaginary);
}

Complex Complex::operator*(const Complex& val) const {
    return Complex(real * val.real + imaginary * val.imaginary, real * val.imaginary + imaginary * val.real);
}

bool Complex::operator==(const Complex& right) const {
    return right.real == real && right.imaginary == imaginary;
}

bool Complex::operator!=(const Complex& right) const {
    return right.real != real || right.imaginary != imaginary;
}

ostream& operator<<(ostream& cout, const Complex& com) {
    cout << "(" << com.real << ", " << com.imaginary << ")";
    return cout;
}

istream& operator>>(istream& cin, Complex& com) {
    cin.ignore();
    cin >> com.real;
    cin.ignore(2);
    cin >> com.imaginary;
    cin.ignore();
    return cin;
}
