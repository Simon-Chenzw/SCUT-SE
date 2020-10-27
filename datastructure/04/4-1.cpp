#include <iostream>
using namespace std;

const int maxn = 100;
bool used[maxn];
int vec[maxn];

bool check(int n) {
    for (int i = 0; i < n; i++) {
        int max = vec[i];
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[i]) {
                if (vec[j] > max)
                    return false;
                else
                    max = vec[j];
            }
        }
    }
    return true;
}

void dfs(int n, int dep, bool needlegal) {
    if (dep == n) {
        if (check(n) == needlegal) {
            for (int i = 0; i < n; i++) cout << vec[i];
            cout << endl;
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            vec[dep] = i;
            dfs(n, dep + 1, needlegal);
            used[i] = false;
            vec[dep] = 0;
        }
    }
}

int main() {
    cout << "legal\n";
    dfs(4, 0, true);
    cout << "illegal\n";
    dfs(4, 0, false);
}