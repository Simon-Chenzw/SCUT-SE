/**
 *  @brief:code of 9.13
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
using namespace std;

class Rectangle {
  public:
    explicit Rectangle(double, double, double, double, double, double, double, double);

    // calc func
    double length() const;
    double width() const;
    double perimeter() const;
    double area() const;
    bool square() const;

    // print func
    void draw() const;
    void setFillCharacter(char);
    void setPerimeterCharacter(char);

  private:
    class pnt {
      public:
        double x, y;
        void set(double _x, double _y) {
            if (_x > 0.0 && _x < 20.0)
                x = _x;
            else
                throw invalid_argument("invalid x");
            if (_y > 0.0 && _y < 20.0)
                y = _y;
            else
                throw invalid_argument("invalid y");
        }
    };

    pnt a, b, c, d;    // note: a is opposite to c
    char fill, peri;
    double len, wid;

    // intermediate functions
    void calc();
    static double dis(pnt, pnt);    // calc |AB|
    bool inside_Rectangle(double, double) const;
    static double cross_product(pnt, pnt, pnt);    // calc (AB)x(AC)
};

Rectangle::Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    a.set(x1, y1);
    b.set(x2, y2);
    c.set(x3, y3);
    d.set(x4, y4);
    calc();
}

double Rectangle::length() const {
    return len;
}
double Rectangle::width() const {
    return wid;
}
double Rectangle::perimeter() const {
    return (len + wid) * 2;
}
double Rectangle::area() const {
    return len * wid;
}
bool Rectangle::square() const {
    return (len - wid) < 1e-9;
}

void Rectangle::draw() const {
    bool inside[30][30] = {};
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            if (inside_Rectangle(i, j)) inside[i][j] = true;
    static int f[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++)
            if (!inside[i][j])
                cout << fill;
            else {
                bool is_peri = false;
                for (int k = 0; k < 8; k++)
                    if (!inside[i + f[k][0]][j + f[k][1]]) {
                        is_peri = true;
                        break;
                    }
                if (is_peri)
                    cout << peri;
                else
                    cout << fill;
            }
        cout << '\n';
    }
    cout.flush();
}

void Rectangle::setFillCharacter(char _fill) {
    fill = _fill;
}
void Rectangle::setPerimeterCharacter(char _peri) {
    peri = _peri;
}

void Rectangle::calc() {
    double distance[6] = {dis(a, b), dis(a, c), dis(a, d), dis(b, c), dis(b, d), dis(c, d)};
    sort(distance, distance + 6);
    int tot = unique(distance, distance + 6) - distance;
    double diagonal;
    if (distance[0] == 0) throw invalid_argument("rectangle degenerated");
    assert(tot == 2 || tot == 3);
    if (tot == 3) {
        diagonal = distance[2];
        len = distance[1];
        wid = distance[0];
    }
    else {
        diagonal = distance[1];
        len = wid = distance[0];
    }
    if (dis(a, b) == diagonal) swap(b, c);
    if (dis(a, d) == diagonal) swap(d, c);
}

double Rectangle::dis(pnt a, pnt b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool Rectangle::inside_Rectangle(double x, double y) const {
    pnt tmp = {x, y};
    return (cross_product(a, b, tmp) * cross_product(c, d, tmp) >= 0
            && cross_product(a, d, tmp) * cross_product(c, b, tmp) >= 0);
}

double Rectangle::cross_product(pnt a, pnt b, pnt c) {
    return ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}