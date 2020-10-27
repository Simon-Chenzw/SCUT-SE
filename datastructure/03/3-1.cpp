#include <iostream>

// 假设数据类型就为整数，且由小到大

class linearList {
    int n = 0;
    int a[100] = {};

  public:
    void insert(int val) {
        for (int i = 0; i < n; i++) {
            if (a[i] > val) {
                int tmp = a[i];
                a[i] = val;
                val = tmp;
            }
        }
        a[n++] = val;
    }
};

class linkedList {
    class data {
      public:
        int val;
        data *pre, *nxt;
        data(int _val): val(_val), pre(nullptr), nxt(nullptr) {}
    };

    data* head = nullptr;

  public:
    void insert(int val) {
        if (head == nullptr) {
            head = new data(val);
        }
        else {
            data* p = head;
            while (p->val < val && p->nxt != nullptr) p = p->nxt;
            data* newp = new data(val);
            if (p->val < val) {
                p->nxt = newp;
                newp->pre = p;
            }
            else {
                newp->pre = p->pre;
                newp->nxt = p;
                p->pre->nxt = newp;
                p->pre = newp;
            }
        }
    }
};