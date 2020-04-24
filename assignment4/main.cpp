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