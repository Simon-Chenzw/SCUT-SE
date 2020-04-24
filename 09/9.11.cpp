// @author chenzhuowen
// @problem 9.11

#include <bits/stdc++.h>
using namespace std;

class Rectangle {
  public:
    explicit Rectangle(double = 1.0, double = 1.0);

    // set func
    void setLength(double);
    void setWidth(double);

    // get func
    double getLenth() const;
    double getWidth() const;

    // calc func
    double perimeter() const;
    double area() const;

  private:
    double length;
    double width;
};

Rectangle::Rectangle(double length, double width) {
    setLength(length);
    setWidth(width);
}

void Rectangle::setLength(double l) {
    if (l > 0.0 && l < 20.0)
        length = l;
    else
        throw invalid_argument("invalid length");
}

void Rectangle::setWidth(double w) {
    if (w > 0.0 && w < 20.0)
        width = w;
    else
        throw invalid_argument("invalid width");
}

double Rectangle::getLenth() const { return length; }

double Rectangle::getWidth() const { return width; }

double Rectangle::perimeter() const { return (length + width) * 2; }

double Rectangle::area() const { return length * width; }