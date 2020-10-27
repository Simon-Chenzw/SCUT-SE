#include <iostream>
using namespace std;

bool used[100];

void dfs(int n, int m, int dep, int choice) {
    if (dep == n + 1) {
        if (choice == m) {
            for (int i = 1; i <= n; i++)
                if (used[i]) cout << i;
            cout << endl;
        }
        return;
    }
    used[dep] = true;
    dfs(n, m, dep + 1, choice + 1);
    used[dep] = false;
    dfs(n, m, dep + 1, choice);
}

int main() {
    int n = 4, k = 3;
    dfs(n, k, 1, 0);
}