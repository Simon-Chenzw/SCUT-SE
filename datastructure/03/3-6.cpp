#include <algorithm>
#include <iostream>
using namespace std;

// 假设数据类型就为整数

class linkedList {
  public:
    class data {
      public:
        int val;
        data* nxt;
        data(int _val): val(_val), nxt(nullptr) {}
    };

    data *head = nullptr, *tail = nullptr;
} list;

void reverse(linkedList& a) {
    auto q = list.head;
    decltype(q) p = nullptr, r = q->nxt;
    while (q) {
        q->nxt = p;
        p = q;
        q = r;
        if (r) r = r->nxt;
    }
    swap(a.head, a.tail);
}

int main() {
    int val;
    while (std::cin >> val) {
        if (list.head == nullptr) {
            list.head = new linkedList::data(val);
            list.tail = list.head;
        }
        else {
            list.tail->nxt = new linkedList::data(val);
            list.tail = list.tail->nxt;
        }
    }
    reverse(list);
    auto p = list.head;
    while (p != nullptr) {
        std::cout << p->val << '\n';
        p = p->nxt;
    }
}