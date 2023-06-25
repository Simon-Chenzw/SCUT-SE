#include <bits/stdc++.h>
using namespace std;

struct Line {
    int x, y;
    int cross(const Line& rhs) const {
        return x * rhs.y - rhs.x * y;
    }
};

struct Point {
    int a, b;
    Line operator-(const Point& rhs) const {
        return Line {a - rhs.a, b - rhs.b};
    }
};

// vec 为按顺序的顶点

bool isConvex(vector<Point> vec) {
    vector<Line> ls;
    for (int i = 0; i + 1 < vec.size(); i++) ls.push_back(vec[i + 1] - vec[i]);
    ls.push_back(vec.front() - vec.back());
    int example = ls.front().cross(ls.back());
    for (int i = 0; i + 1 < ls.size(); i++)
        if (ls[i + 1].cross(ls[i]) * example <= 0) return false;
    return true;
}