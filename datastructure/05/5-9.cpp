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
    void add(int i, int j, int val) {
        TTriTuple tmp {i, j, val};
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

void addto(TTriTupleArray& a, TTriTupleArray& b) {
    for (int i = 0; i < b.size; i++) {
        a.add(b.list[i].i, b.list[i].j, b.list[i].val);
    }
}

int main() {
    TTriTupleArray a, b;
    a.set(1, 1, 1);
    a.set(1, 3, 2);
    a.set(2, 5, 1);
    b.set(1, 1, 1);
    b.set(2, 2, 1);
    addto(a, b);
}