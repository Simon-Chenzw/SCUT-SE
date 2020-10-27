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

int dep[maxn];
queue<int> q;
int start = 1;

int main() {
    dep[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int& v : line[u])
            if (!dep[v]) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
    }

    for (int i = 1; i <= n; i++) cout << i << " dep=" << dep[i] << endl;
}