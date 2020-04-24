// @problem:13.17

#include <bits/stdc++.h>

using namespace std;

int main() {
    cout << setw(7) << "Dec" << setw(7) << "Oct" << setw(7) << "Hex" << setw(7) << "Char"
         << showbase << '\n';
    for (int i = 33; i <= 126; i++)
        cout << setw(7) << dec << i << setw(7) << oct << i << setw(7) << hex << i << setw(7)
             << char(i) << endl;
}
