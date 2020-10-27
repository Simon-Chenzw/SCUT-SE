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
int S[maxn], E[maxn];
int cnt;

bool vis[maxn];
void dfs(int p) {
    vis[p] = true;
    S[p] = ++cnt;
    for (auto& q : line[p])
        if (!vis[q]) {
            fa[q] = p;
            son[p].push_back(q);
            dfs(q);
        }
    E[p] = ++cnt;
}

int main() {
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cout << i << " S=" << S[i] << " E=" << E[i] << " fa=" << fa[i] << " son=";
        for (auto& p : son[i]) cout << p << ' ';
        cout << endl;
    }
}