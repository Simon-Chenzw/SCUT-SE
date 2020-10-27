#include <iostream>
#include <queue>
using namespace std;

const int n = 10;
// int a[100] = {0, 6, 5, 2, 3, 9, 7, 10, 4, 8, 1};
int a[100] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

#define lson (i << 1)
#define rson (i << 1 | 1)

void preOrder(int i) {
    if (i > n) return;
    cout << a[i] << ' ';
    preOrder(lson);
    preOrder(rson);
}

void inOrder(int i) {
    if (i > n) return;
    inOrder(lson);
    cout << a[i] << ' ';
    inOrder(rson);
}

void pastOrder(int i) {
    if (i > n) return;
    pastOrder(lson);
    pastOrder(rson);
    cout << a[i] << ' ';
}

void levelOrder(int root) {
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        cout << tmp << ' ';
        if (tmp * 2 <= n) q.push(tmp * 2);
        if (tmp * 2 + 1 <= n) q.push(tmp * 2 + 1);
    }
}

int main() {
    cout << "preOrder   : ";
    preOrder(1);
    cout << endl;

    cout << "inOrder    : ";
    inOrder(1);
    cout << endl;

    cout << "pastOrder  : ";
    pastOrder(1);
    cout << endl;

    cout << "levelOrder : ";
    levelOrder(1);
    cout << endl;
}