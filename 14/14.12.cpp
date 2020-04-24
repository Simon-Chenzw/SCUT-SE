/**
 *  @brief:code of 14.12
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
using namespace std;

const string letters[10] = {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXYZ"};
int num[7] = {0};

void dfs(int dep, string& str, ofstream& fout) {
    if (dep == 7) {
        fout << str << '\n';
        return;
    }
    for (auto& p : letters[num[dep]]) {
        str[dep] = p;
        dfs(dep + 1, str, fout);
    }
}

int main() {
    int cnt = 0;
    while (cnt != 7) {
        if (cin.peek() >= '0' && cin.peek() <= '9')
            num[cnt++] = cin.get() - '0';
        else
            cin.ignore();
    }
    ofstream fout("output");
    string str = "0123456";
    dfs(0, str, fout);
}