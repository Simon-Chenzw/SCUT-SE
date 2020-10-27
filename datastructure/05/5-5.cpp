#include <cstdlib>
#include <iostream>
using namespace std;

const int n = 3;
const int m = 5;

int a[20];
int b[20];
int c[20];

int loc(int i, int j) {
    return i * m + j;
}

int main() {
    for (int i = 0; i < 15; i++) a[i] = rand();
    for (int i = 0; i < 15; i++) b[i] = rand();
    // 采用二维数组的寻址公式访问元素
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++) c[loc(i, k)] += a[loc(i, j)] * b[loc(j, k)];
    // 直接推算要访问的元素的存储位置
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++) *(c + (i * m + k)) += *(a + (i * m + j)) * *(b + (j * m + k));
}