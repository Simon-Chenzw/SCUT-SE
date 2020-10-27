#include <iostream>
#include <vector>
using namespace std;

const int maxn = 100;
const int n = 6;
vector<int> line[maxn] = {
    {},           // 0
    {2, 5},       // 1
    {4},          // 2
    {},           // 3
    {1},          // 4
    {3, 4, 6},    // 5
    {},           // 6
};                // picture 7-7

int fa[maxn];
vector<int> son[maxn];

bool vis[maxn];
void dfs(int p) {
    int hasSon = false;
    cout << '(' << p;
    vis[p] = true;
    for (auto& q : line[p])
        if (!vis[q]) {
            hasSon = true;
            fa[q] = p;
            son[p].push_back(q);
            dfs(q);
        }
    if (!hasSon) cout << ' ';
    cout << p << ')';
}

int main() {
    dfs(1);
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << " fa=" << fa[i] << " son=";
        for (auto& p : son[i]) cout << p << ' ';
        cout << endl;
    }
}