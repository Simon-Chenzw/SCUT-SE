#include <iostream>
using namespace std;

bool used[100];
int ans[100];

void dfs(int n, int m, int dep) {
    if (dep == m) {
        for (int i = 0; i < m; i++) cout << ans[i];
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++)
        if (!used[i]) {
            used[i] = true;
            ans[dep] = i;
            dfs(n, m, dep + 1);
            used[i] = false;
            ans[dep] = 0;
        }
}

int main() {
    int n = 4, k = 3;
    dfs(n, k, 0);
}