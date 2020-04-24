//! @file:MatrixMain.cpp

#include "Matrix.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    Matrix a(1, 1, 1, 0), b;
    cin >> b;
    cout << a + a + b;
    a *= a;
    a *= a;
    a *= a;
    a *= a;
    cout << a;
    cout << 9 * b << b * 10;
}