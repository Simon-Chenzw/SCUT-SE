#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 100;
const int n = 11;
bool mp[maxn][maxn] = {
    {},                                      // 0
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},    // 1
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},    // 2
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},    // 3
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},    // 4
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},    // 5
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},    // 6
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},    // 7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    // 8
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},    // 9
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    // 10
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    // 11
    //  1  2  3  4  5  6  7  8  9 10 11
};    // picture 7-8

vector<int> ans;
int cnt[maxn], dep[maxn];

int main() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j]) cnt[j]++;

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!cnt[i]) {
            ans.push_back(i);
            dep[i] = 1;
            q.push(i);
        }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
            if (mp[u][i]) {
                cnt[i]--;
                if (!cnt[i]) {
                    ans.push_back(i);
                    dep[i] = dep[u] + 1;
                    q.push(i);
                }
            }
    }

    cout << '(';
    for (int i = 0; i < ans.size(); i++) {
        if (i && dep[ans[i]] != dep[ans[i - 1]])
            cout << ") (";
        else if (i)
            cout << ' ';
        cout << ans[i];
    }
    cout << ')' << endl;
}