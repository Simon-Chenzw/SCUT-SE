#include <cctype>
#include <iostream>
#include <string>
using namespace std;

const int maxn = 20;
class polynomial {
  public:
    int val[maxn];
    polynomial() {
        for (int i = 0; i < maxn; i++) val[i] = 0;
    }
    polynomial(const string& str) {
        for (int i = 0; i < maxn; i++) val[i] = 0;
        int base = 0, pow = 0;
        bool isBase = true, haveBase = false;
        string tmp = str + '+';
        for (auto& ch : tmp) {
            if (isdigit(ch)) {
                if (isBase) {
                    base = base * 10 + ch - '0';
                    haveBase = true;
                }
                else
                    pow = pow * 10 + ch - '0';
            }
            else if (ch == 'x') {
                if (isBase) {
                    isBase ^= 1;
                    pow = 1;
                }
                else
                    throw invalid_argument("wrong place of 'x'");
            }
            else if (ch == '^') {
                pow = 0;
            }
            else if (ch == '+') {
                if (haveBase)
                    val[pow] += base;
                else
                    val[pow]++;
                isBase = true;
                haveBase = false;
                base = 0;
                pow = 0;
            }
            else {
                throw invalid_argument("wrong char");
            }
        }
    };

    int& operator[](const int& pos) {
        return val[pos];
    }

    polynomial operator+(const polynomial& rhs) const {
        polynomial ret;
        for (int i = 0; i < maxn; i++) ret[i] = val[i] + rhs.val[i];
        return ret;
    }

    polynomial operator*(const polynomial& rhs) const {
        polynomial ret;
        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                if (i + j < maxn) {
                    ret[i + j] += val[i] * rhs.val[j];
                }
        return ret;
    }
};

int main() {
    string tmp;
    cin >> tmp;
    polynomial a(tmp);
    for (int i = 0; i < maxn; i++) cout << i << ' ' << tmp[i] << '\n';
}