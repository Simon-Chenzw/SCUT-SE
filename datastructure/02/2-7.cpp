#include <iostream>
using namespace std;

const int maxn = 100;
int a[maxn], dp[maxn], pre[maxn];

void print(int ord, char ch) {
    if (ord) {
        print(pre[ord], ' ');
        cout << a[ord] << ch;
    }
}

int main() {
    int n, ans = 0, p = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++)
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
        if (dp[i] > ans) {
            ans = dp[i];
            p = i;
        }
    }
    cout << ans << endl;
    print(p, '\n');
}