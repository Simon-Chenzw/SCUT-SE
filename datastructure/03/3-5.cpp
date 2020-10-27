#include <iostream>

// 假设数据类型就为整数

class linkedList {
  public:
    class data {
      public:
        int val;
        data *pre, *nxt;
        data(int _val): val(_val), pre(nullptr), nxt(nullptr) {}
    };

    data *head = nullptr, *tail = nullptr;
} list;

int main() {
    int val;
    while (std::cin >> val) {
        if (list.head == nullptr) {
            list.head = new linkedList::data(val);
            list.tail = list.head;
        }
        else {
            list.tail->nxt = new linkedList::data(val);
            list.tail->nxt->pre = list.tail;
            list.tail = list.tail->nxt;
        }
    }
    auto p = list.head;
    while (p != nullptr) {
        std::cout << p->val << '\n';
        p = p->nxt;
    }
}