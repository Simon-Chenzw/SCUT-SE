#include <iostream>

// 假设数据类型就为整数，且由小到大

class linearList {
  public:
    int tot = 0;
    int val[100] = {};
    int& operator[](const int& pos) {
        return val[pos];
    }
};

linearList merge(linearList a, linearList b) {
    int p = 0, q = 0;
    linearList ret;
    while (p < a.tot && q < b.tot) {
        if (a[p] < b[q])
            ret[ret.tot++] = a[p++];
        else
            ret[ret.tot++] = b[q++];
    }
    while (p < a.tot) ret[ret.tot++] = a[p++];
    while (q < b.tot) ret[ret.tot++] = b[q++];
    return ret;
}

class linkedList {
  public:
    class data {
      public:
        int val;
        data *pre, *nxt;
        data(int _val): val(_val), pre(nullptr), nxt(nullptr) {}
    };

    data* head = nullptr;
};

void copy(linkedList::data* src, linkedList::data* tgt) {
    if (tgt == nullptr) {
        tgt = new linkedList::data(src->val);
    }
    else {
        tgt->nxt = new linkedList::data(src->val);
        tgt->nxt->pre = tgt;
        tgt = tgt->nxt;
    }
    src = src->nxt;
}

linkedList merge(linkedList a, linkedList b) {
    linkedList ret;
    linkedList::data *p = a.head, *q = b.head, *r = ret.head;
    while (p != nullptr && q != nullptr) {
        if (p->val < q->val)
            copy(p, r);
        else
            copy(q, r);
    }
    while (p != nullptr) copy(p, r);
    while (q != nullptr) copy(q, r);
    return ret;
}
