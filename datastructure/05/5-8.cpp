#include <cmath>
#include <iostream>
using namespace std;

int calc(int n, int loc, int& i, int& j) {
    i = 1;
    while (i * (i + 1) <= 2 * loc) i++;
    j = loc - (i - 1) * i / 2 + 1;
}

int main() {
    int n, loc;
    while (cout << "N, Loc: ", cin >> n >> loc) {
        int i, j;
        calc(n, loc, i, j);
        cout << i << ' ' << j << endl;
    }
}