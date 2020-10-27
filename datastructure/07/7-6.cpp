#include <iostream>
#include <queue>
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

int start = 1;
queue<int> q;

int main() {
    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& v : line[u])
            if (!vis[v]) {
                vis[v] = true;
                fa[v] = u;
                son[u].push_back(v);
                q.push(v);
            }
    }

    for (int i = 1; i <= n; i++) {
        cout << i << " fa=" << fa[i] << " son=";
        for (auto& p : son[i]) cout << p << ' ';
        cout << endl;
    }
}