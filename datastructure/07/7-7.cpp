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
int dep[maxn];

bool vis[maxn];
void dfs(int p) {
    vis[p] = true;
    for (auto& q : line[p])
        if (!vis[q]) {
            dep[q] = dep[p] + 1;
            fa[q] = p;
            son[p].push_back(q);
            dfs(q);
        }
}

int main() {
    int start = 1;
    dep[start] = 1;
    dfs(start);
    for (int i = 1; i <= n; i++) {
        cout << i << " dep=" << dep[i] << " fa=" << fa[i] << " son=";
        for (auto& p : son[i]) cout << p << ' ';
        cout << endl;
    }
}