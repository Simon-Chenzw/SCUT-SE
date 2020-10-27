/**
 *  @brief:code of assignment3
 *  @file:MatrixMain.cpp
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
#include "Matrix.h"
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