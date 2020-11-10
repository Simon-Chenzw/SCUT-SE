#include <cctype>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
using namespace std;

class Node {
  public:
    char name;
    list<Node*> sub;

    Node(): name(0) {}
    Node(char _name): name(_name) {}

    string bfs() const {
        string ret = "";
        queue<const Node*> q;
        set<char> vis;
        q.push(this);
        vis.insert(name);
        while (!q.empty()) {
            auto tmp = q.front();
            q.pop();
            if (!ret.empty()) ret.push_back(' ');
            ret.push_back(tmp->name);
            for (auto& it : tmp->sub)
                if (!vis.count(it->name)) {
                    q.push(it);
                    vis.insert(it->name);
                }
        }
        return ret;
    }

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

int main() {
    auto list1 = Node::create("L(A(B(a, b)), C(B(a, b), c), D(c, d, e), E(e))");    // 图 8-1
    cout << list1.bfs() << endl;
    auto list2 = Node::create("L = A(a, B(c, C(a, b), d), E(e, F(f)))");    // 习题 8-3
    cout << list2.bfs() << endl;
}