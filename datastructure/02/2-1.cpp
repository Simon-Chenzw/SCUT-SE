#include <iomanip>
#include <iostream>
using namespace std;

int val[20][20];

int main() {
    const int size = 6;
    val[1][1] = 1;
    cout << setw(4) << val[1][1] << endl;
    for (int i = 2; i <= size; i++) {
        for (int j = 1; j <= i; j++) {
            val[i][j] = val[i - 1][j - 1] + val[i - 1][j];
            cout << setw(4) << val[i][j];
        }
        cout << endl;
    }
}