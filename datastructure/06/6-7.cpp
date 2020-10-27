#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class node {
  public:
    T val;
    node *lson, *rson;
    node(T _val): val(_val), lson(nullptr), rson(nullptr) {}
};

template <typename T>
class BinaryTree {
  public:
    using pointer = node<T>*;
    pointer root;

    BinaryTree(int n, int rt, int info[][2]): root(nullptr) {
        queue<pointer> q;
        q.push(root = new node<T>(rt));
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (info[tmp->val][0]) q.push(tmp->lson = new node<T>(info[tmp->val][0]));
            if (info[tmp->val][1]) q.push(tmp->rson = new node<T>(info[tmp->val][1]));
        }
    }

    // 6-7
    bool isComplete() const {
        queue<pointer> q;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (tmp->lson || tmp->rson) {
                if (tmp->lson && tmp->rson) {
                    q.push(tmp->lson);
                    q.push(tmp->rson);
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }

    // 6-8
    bool isSequence() const {
        queue<pointer> q;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (tmp->lson) {
                if (tmp->lson->val != tmp->val * 2)
                    return false;
                else
                    q.push(tmp->lson);
            }
            if (tmp->rson) {
                if (tmp->rson->val != tmp->val * 2 + 1)
                    return false;
                else
                    q.push(tmp->rson);
            }
        }
        return true;
    }

    // 6-9
    bool isHeightBalance() const {
        bool ret = true;
        heightBalance(root, ret);
        return ret;
    }

    static int heightBalance(const pointer& p, bool& isBalance) {
        if (!isBalance) return 0;
        int l = (p->lson ? heightBalance(p->lson, isBalance) : 0);
        int r = (p->rson ? heightBalance(p->rson, isBalance) : 0);
        isBalance &= (l == r || (l + 1) == r || (r + 1) == l);
        return max(l, r) + 1;
    }

    // 6-10
    int size() const {
        queue<pointer> q;
        int ret = 0;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            ret++;
            if (tmp->lson) q.push(tmp->lson);
            if (tmp->rson) q.push(tmp->rson);
        }
        return ret;
    }

    // 6-11
    int height() const {
        queue<pair<pointer, int>> q;
        int ret = 0;
        q.push({root, 1});
        while (!q.empty()) {
            pair<pointer, int> tmp = q.front();
            q.pop();
            ret = tmp.second;
            if (tmp.first->lson) q.push({tmp.first->lson, tmp.second + 1});
            if (tmp.first->rson) q.push({tmp.first->rson, tmp.second + 1});
        }
        return ret;
    }

    // 6-12
    int countLeaf() const {
        queue<pointer> q;
        int ret = 0;
        q.push(root);
        while (!q.empty()) {
            pointer tmp = q.front();
            q.pop();
            if (!tmp->lson && !tmp->rson) ret++;
            if (tmp->lson) q.push(tmp->lson);
            if (tmp->rson) q.push(tmp->rson);
        }
        return ret;
    }

    // 6-13
    BinaryTree(const BinaryTree& src, bool recursion = false): root(nullptr) {
        if (recursion) {
            copy(src.root, root);
        }
        else {
            queue<pointer const*> s;
            queue<pointer*> t;
            s.push(&(src.root));
            t.push(&root);
            while (!s.empty() && !t.empty()) {
                pointer const* sr = s.front();
                pointer* tg = t.front();
                s.pop();
                t.pop();
                *tg = new node<T>((*sr)->val);
                if ((*sr)->lson) {
                    s.push(&((*sr)->lson));
                    t.push(&((*tg)->lson));
                }
                if ((*sr)->rson) {
                    s.push(&((*sr)->rson));
                    t.push(&((*tg)->rson));
                }
            }
        }
    }

    static void copy(const pointer& src, pointer& tgt) {
        tgt = new node<T>(src->val);
        if (src->lson) copy(src->lson, tgt->lson);
        if (src->rson) copy(src->rson, tgt->rson);
    }

    // 6-16
    void printLeafPath() const {
        cout << "All leaf path:" << endl;
        vector<int> tmp;
        leafPath(root, tmp);
    }

    static void leafPath(const pointer& p, vector<int>& vec) {
        vec.push_back(p->val);
        if (p->lson || p->rson) {
            if (p->lson) leafPath(p->lson, vec);
            if (p->rson) leafPath(p->rson, vec);
        }
        else {
            for (auto& i : vec) cout << i << ' ';
            cout << endl;
        }
        vec.pop_back();
    }

    // 6-17
    string extPreOrder() const {
        string ret;
        extPre(root, ret);
        return ret;
    }

    static void extPre(const pointer& p, string& ret) {
        ret += (p ? to_string(p->val) : "*") + ' ';
        if (p) {
            extPre(p->lson, ret);
            extPre(p->rson, ret);
        }
    }
};

#define print(var) cout << #var << " = " << var << endl

int main() {
    int info[20][2] = {
        {0, 0},
        {2, 3},
        {4, 5},
        {6, 7},
        {8, 9},
        {10, 0},
    };
    BinaryTree<int> tree(10, 1, info);
    print(tree.isComplete());         // 6-7
    print(tree.isSequence());         // 6-8
    print(tree.isHeightBalance());    // 6-9
    print(tree.size());               // 6-10
    print(tree.height());             // 6-11
    print(tree.countLeaf());          // 6-12
    // 6-13
    BinaryTree<int> b(tree, false);
    print(b.size());
    BinaryTree<int> c(tree, true);
    print(c.size());
    tree.printLeafPath();         // 6-16
    print(tree.extPreOrder());    // 6-17
}