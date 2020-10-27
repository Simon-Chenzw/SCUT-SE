/**
 *  @brief:code of 10.9
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
using namespace std;

class HugeInt {
  public:
    static const int digits = 30;    // maximum digits in a HugeInt

    HugeInt(long long = 0);
    HugeInt(const string&);

    HugeInt operator+(const HugeInt&) const;
    HugeInt operator-(const HugeInt&) const;
    HugeInt operator*(const HugeInt&)const;
    HugeInt operator/(const HugeInt&) const;

    int cmp(const HugeInt&) const;    // <=> operator
    bool operator==(const HugeInt&) const;
    bool operator!=(const HugeInt&) const;
    bool operator<(const HugeInt&) const;
    bool operator<=(const HugeInt&) const;
    bool operator>(const HugeInt&) const;
    bool operator>=(const HugeInt&) const;

    friend ostream& operator<<(ostream&, const HugeInt&);

  private:
    int integer[digits];

    HugeInt left_shift(int) const;
};

HugeInt::HugeInt(long long val) {
    for (int i = 0; i < digits; i++) integer[i] = 0;
    for (int i = digits - 1; i >= 0; i--) {
        integer[i] = val % 10;
        val /= 10;
    }
}

HugeInt::HugeInt(const string& number) {
    for (int i = 0; i < digits; i++) integer[i] = 0;
    for (int j = digits - number.size(), k = 0; j < digits; j++, k++)
        if (isdigit(number[k])) integer[j] = number[k] - '0';
}

HugeInt HugeInt::operator+(const HugeInt& val) const {
    HugeInt ans;
    for (int i = digits - 1; i >= 0; i--) {
        ans.integer[i] += integer[i] + val.integer[i];
        if (ans.integer[i] >= 10) {
            if (i == 0) throw overflow_error("add overflow");
            ans.integer[i - 1]++;
            ans.integer[i] -= 10;
        }
    }
    return ans;
}

HugeInt HugeInt::operator-(const HugeInt& val) const {
    HugeInt ans;
    for (int i = digits - 1; i >= 0; i--) {
        ans.integer[i] += integer[i] - val.integer[i];
        if (ans.integer[i] < 0) {
            if (i == 0) throw underflow_error("substract underflow");
            ans.integer[i - 1]--;
        }
    }
    return ans;
}

HugeInt HugeInt::operator*(const HugeInt& val) const {
    HugeInt ans;
    for (int i = 0; i < digits; i++)
        for (int j = 0; j < digits; j++)
            if (i + j - digits + 1 < 0 && integer[i] * val.integer[j] != 0)
                throw logic_error("div by zero");
            else
                ans.integer[i + j - digits + 1] += integer[i] * val.integer[j];
    for (int i = digits - 1; i >= 0; i--) {
        if (ans.integer[i] >= 10) {
            if (i == 0) throw overflow_error("add overflow");
            ans.integer[i - 1] += ans.integer[i] / 10;
            ans.integer[i] %= 10;
        }
    }
    return ans;
}

HugeInt HugeInt::operator/(const HugeInt& val) const {
    HugeInt ans, tmp = *this;
    int base = 0;
    int max_base = 0;
    while (max_base < digits && val.integer[max_base] == 0) max_base++;
    if (max_base == digits) throw logic_error("div by zero");
    while (base < max_base && tmp >= val.left_shift(base)) base++;
    while (base >= 0) {
        while (tmp >= val.left_shift(base)) {
            ans.integer[digits - base - 1]++;
            tmp = tmp - val.left_shift(base);
        }
        base--;
    }
    return ans;
}

int HugeInt::cmp(const HugeInt& val) const {
    for (int i = 0; i < digits; i++)
        if (integer[i] > val.integer[i])
            return 1;
        else if (integer[i] < val.integer[i])
            return -1;
    return 0;
}

bool HugeInt::operator==(const HugeInt& val) const {
    return cmp(val) == 0;
}
bool HugeInt::operator!=(const HugeInt& val) const {
    return cmp(val) != 0;
}
bool HugeInt::operator<(const HugeInt& val) const {
    return cmp(val) == -1;
}
bool HugeInt::operator<=(const HugeInt& val) const {
    return cmp(val) != 1;
}
bool HugeInt::operator>(const HugeInt& val) const {
    return cmp(val) == 1;
}
bool HugeInt::operator>=(const HugeInt& val) const {
    return cmp(val) != -1;
}

ostream& operator<<(ostream& cout, const HugeInt& val) {
    int p = 0;
    while (p < HugeInt::digits && val.integer[p] == 0) p++;
    if (p == HugeInt::digits) cout << 0;
    for (int i = p; i < HugeInt::digits; i++) cout << val.integer[i];
}

HugeInt HugeInt::left_shift(int base) const {
    HugeInt ans;
    for (int i = 0; i + base < digits; i++) ans.integer[i] = integer[i + base];
    return ans;
}