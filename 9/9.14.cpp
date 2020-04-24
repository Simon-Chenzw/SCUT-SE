// @author chenzhuowen
// @problem 9.14

#include <bits/stdc++.h>
using namespace std;

class HugeInteger {
  public:
    // constructor
    HugeInteger(int = 0);
    HugeInteger(string);

    // input/output
    void input();
    void output() const;

    // calc
    HugeInteger& add(HugeInteger);
    HugeInteger& substract(HugeInteger);

    // cmp func
    bool isEqualTo(HugeInteger) const;
    bool isNotEqualTo(HugeInteger) const;
    bool isGreaterThan(HugeInteger) const;
    bool isLessThan(HugeInteger) const;
    bool isGreaterThanOrEqualTo(HugeInteger) const;
    bool isLessThanOrEqualTo(HugeInteger) const;
    bool isZero() const;

    // operator
    int& operator[](const int&);

  private:
    int a[40] = {};
    bool negative = false;
    HugeInteger& opposite();
    int cmp(const HugeInteger&) const;
};

HugeInteger::HugeInteger(int val) {
    if (val < 0) {
        val *= -1;
        negative = true;
    }
    for (int i = 0; i < 40; i++) {
        a[i] = val % 10;
        val /= 10;
        if (!val) return;
    }
}

HugeInteger::HugeInteger(string str) {
    if (str.length() - (str[0] == '-' ? 1 : 0) > 40)
        throw range_error("to large for HugeInteger");
    negative = str[0] == '-';
    for (int i = 0; i < str.length() - (str[0] == '-' ? 1 : 0); i++)
        if (str[str.length() - i - 1] >= '0' &&
            str[str.length() - i - 1] <= '9')
            a[i] = str[str.length() - i - 1] - '0';
        else
            throw invalid_argument("it's not integer");
}

void HugeInteger::input() {
    string str;
    cin >> str;
    if (str.length() > 40) throw range_error("to large for HugeInteger");
    for (int i = 0; i < str.length(); i++)
        a[i] = str[str.length() - i - 1] - '0';
}

void HugeInteger::output() const {
    int cnt = 39;
    while (cnt >= 0 && a[cnt] == 0) cnt--;
    if (cnt < 0) {
        cout << '0';
        return;
    }
    if (negative) cout << '-';
    while (cnt >= 0) cout << a[cnt--];
}

HugeInteger& HugeInteger::add(HugeInteger val) {
    if (negative != val.negative) substract(val.opposite());
    for (int i = 0; i < 40; i++) {
        a[i] += val[i];
        if (a[i] >= 10) {
            if (i + 1 == 40) throw overflow_error("overflow");
            a[i + 1]++;
            a[i] -= 10;
        }
    }
    return *this;
}

HugeInteger& HugeInteger::substract(HugeInteger val) {
    if (negative != val.negative) add(val.opposite());
    if (val.isGreaterThan(*this))
        return *this = val.substract(*this).opposite();
    for (int i = 0; i < 40; i++) {
        a[i] -= val[i];
        if (a[i] < 0) {
            a[i + 1]--;
            a[i] += 10;
        }
    }
    return *this;
}

bool HugeInteger::isEqualTo(HugeInteger val) const {
    if (negative != val.negative) return false;
    return cmp(val) == 0;
}

bool HugeInteger::isNotEqualTo(HugeInteger val) const {
    if (negative != val.negative) return true;
    return cmp(val) != 0;
}

bool HugeInteger::isGreaterThan(HugeInteger val) const {
    if (negative != val.negative) return !negative;
    return cmp(val) * (negative ? -1 : 1) == 1;
}

bool HugeInteger::isLessThan(HugeInteger val) const {
    if (negative != val.negative) return negative;
    return cmp(val) * (negative ? -1 : 1) == -1;
}

bool HugeInteger::isGreaterThanOrEqualTo(HugeInteger val) const {
    if (negative != val.negative) return !negative;
    return cmp(val) * (negative ? -1 : 1) >= 0;
}

bool HugeInteger::isLessThanOrEqualTo(HugeInteger val) const {
    if (negative != val.negative) return negative;
    return cmp(val) * (negative ? -1 : 1) <= 0;
}

bool HugeInteger::isZero() const {
    for (int i = 0; i < 40; i++)
        if (a[i] != 0) return false;
    return true;
}

int& HugeInteger::operator[](const int& i) { return a[i]; }

HugeInteger& HugeInteger::opposite() {
    negative ^= true;
    return *this;
}

// return |*this| <=> |val|
int HugeInteger::cmp(const HugeInteger& val) const {
    for (int i = 0; i < 40; i++)
        if (a[i] > val.a[i])
            return 1;
        else if (a[i] < val.a[i])
            return -1;
    return 0;
}
