/**
 *  @brief:code of assignment4
 *  @file:main.cpp
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
#include "zoo.h"
using namespace std;

int main() {
    srand(clock());
    Zoo zoo;
    while (!zoo.is_close()) {
        zoo.run_one_day();
        cout << endl;
    }
    zoo.print_close_info();
}