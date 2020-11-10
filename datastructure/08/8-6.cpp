#include <cctype>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
using namespace std;

class Node {
  public:
    char name;
    list<Node*> sub;

    Node(): name(0) {}
    Node(char _name): name(_name) {}

    set<int> findDep(char ch) const {
        set<int> ret;
        bfsFind(ch, 1, ret);
        return ret;
    }

  private:
    void bfsFind(const char& ch, int base, set<int>& ret) const {
        if (name == ch) ret.insert(base);
        for (auto& it : sub) it->bfsFind(ch, base + 1, ret);
    }

  public:
    static Node create(const string& s) {
        stack<Node*> st;
        map<char, Node*> addr;
        for (auto& ch : s) {
            if (ch == ',' || ch == ')') {
                st.pop();
            }
            else if (isalpha(ch)) {
                auto it = addr.find(ch);
                if (it == addr.end()) {
                    it = addr.insert({ch, new Node(ch)}).first;
                    if (!st.empty()) st.top()->sub.push_back(it->second);
                    st.push(it->second);
                }
                else {
                    if (!st.empty()) st.top()->sub.push_back(it->second);
                    st.push(new Node);    // add empty one
                }
            }
        }
        while (st.size() > 1) st.pop();    //当没有广义表编号的时候
        return *st.top();
    }
};

ostream& operator<<(ostream& out, const set<int>& s) {
    bool first = true;
    for (auto& p : s) {
        if (first)
            first = false;
        else
            out << ' ';
        out << p;
    }
    return out;
}

int main() {
    auto list1 = Node::create("L(A(B(a, b)), C(B(a, b), c), D(c, d, e), E(e))");    // 图 8-1
    cout << "a: " << list1.findDep('a') << endl;
    cout << "c: " << list1.findDep('c') << endl;

    auto list2 = Node::create("L = A(a, B(c, C(a, b), d), E(e, F(f)))");    // 习题 8-3
    cout << "a: " << list2.findDep('a') << endl;
    cout << "C: " << list2.findDep('C') << endl;
}