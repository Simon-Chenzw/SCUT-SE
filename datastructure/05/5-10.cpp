#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 100;

class TTriTuple {
  public:
    int i, j, val;
    bool operator==(const TTriTuple& rhs) const {
        return i == rhs.i && j == rhs.j;
    }
    bool operator<(const TTriTuple& rhs) const {
        return i != rhs.i ? i < rhs.i : j < rhs.j;
    }
    bool operator>(const TTriTuple& rhs) const {
        return i != rhs.i ? i > rhs.i : j > rhs.j;
    }
    TTriTuple operator+(const TTriTuple& rhs) const {
        return {i, j, val + rhs.val};
    }
    TTriTuple& operator+=(const TTriTuple& rhs) {
        val += rhs.val;
        return *this;
    }
    TTriTuple operator*(const TTriTuple& rhs) const {
        return {i, rhs.j, val * rhs.val};
    }
};

class TTriTupleArray {
  public:
    int size;
    TTriTuple list[maxn];
    TTriTuple& get(int i, int j) {
        TTriTuple tmp {i, j, 0};
        for (int i = 0; i < size; i++) {
            if (list[i] == tmp)
                return list[i];
            else if (list[i] > tmp)
                break;
        }
        return *(TTriTuple*)nullptr;
    }
    void set(int i, int j, int val) {
        TTriTuple tmp {i, j, val};
        for (int i = 0; i < size; i++) {
            if (list[i] == tmp) {
                list[i] = tmp;
                return;
            }
            else if (list[i] > tmp)
                swap(list[i], tmp);
        }
        list[size++] = tmp;
    }
    void add(const TTriTuple& val) {
        auto tmp = val;
        for (int i = 0; i < size; i++) {
            if (list[i] == tmp) {
                list[i] += tmp;
                return;
            }
            else if (list[i] > tmp)
                swap(list[i], tmp);
        }
        list[size++] = tmp;
    }
};

const int n = 10;

TTriTupleArray multi(TTriTupleArray& a, TTriTupleArray& b) {
    TTriTupleArray ans;
    for (int i = 0; i < a.size; i++)
        for (int j = 0; j < b.size; j++)
            if (a.list[i].j == b.list[j].i) ans.add(a.list[i] * b.list[j]);
    return ans;
}

int main() {
    TTriTupleArray a, b;
    a.set(1, 1, 1);
    a.set(1, 3, 2);
    a.set(2, 5, 1);
    b.set(1, 1, 1);
    b.set(2, 2, 1);
    auto c = multi(a, b);
}