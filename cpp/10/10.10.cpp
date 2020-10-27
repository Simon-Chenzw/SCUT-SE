/**
 *  @brief:code of 10.10
 *  @author:Simon_Chen
 */

#include <bits/stdc++.h>
using namespace std;

class RationalNumber {
  public:
    RationalNumber(int = 0, int = 1);

    RationalNumber operator+(const RationalNumber&) const;
    RationalNumber operator-(const RationalNumber&) const;
    RationalNumber operator*(const RationalNumber&)const;
    RationalNumber operator/(const RationalNumber&) const;

    bool operator==(const RationalNumber&) const;
    bool operator!=(const RationalNumber&) const;
    bool operator<(const RationalNumber&) const;
    bool operator<=(const RationalNumber&) const;
    bool operator>(const RationalNumber&) const;
    bool operator>=(const RationalNumber&) const;

    //   private:
    int p, q;    // p/q
    static int gcd(int a, int b);
};

RationalNumber::RationalNumber(int m, int n): p(m), q(n) {
    if (q == 0) throw logic_error("denominator is zero");
    int tmp = 1;
    if (q < 0) tmp = -1;
    tmp *= gcd(p, q);
    p /= tmp;
    q /= tmp;
}

RationalNumber RationalNumber::operator+(const RationalNumber& val) const {
    return RationalNumber(p * val.q + q * val.p, q * val.q);
}

RationalNumber RationalNumber::operator-(const RationalNumber& val) const {
    return RationalNumber(p * val.q - q * val.p, q * val.q);
}

RationalNumber RationalNumber::operator*(const RationalNumber& val) const {
    return RationalNumber(p * val.p, q * val.q);
}

RationalNumber RationalNumber::operator/(const RationalNumber& val) const {
    return RationalNumber(p * val.q, q * val.p);
}

bool RationalNumber::operator==(const RationalNumber& val) const {
    return (p * val.q == q * val.p);
}

bool RationalNumber::operator!=(const RationalNumber& val) const {
    return (p * val.q != q * val.p);
}

bool RationalNumber::operator<(const RationalNumber& val) const {
    return (p * val.q < q * val.p);
}

bool RationalNumber::operator<=(const RationalNumber& val) const {
    return (p * val.q <= q * val.p);
}

bool RationalNumber::operator>(const RationalNumber& val) const {
    return (p * val.q > q * val.p);
}

bool RationalNumber::operator>=(const RationalNumber& val) const {
    return (p * val.q >= q * val.p);
}

int RationalNumber::gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}
