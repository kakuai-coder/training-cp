#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }

template <typename T>
bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }

template <typename T>
int size32(const T &a) { return (int)a.size(); }

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
    static_assert(D >= 1, "Error");
    template <typename... Args>
    Vec(int n = 0, Args... args)
        : vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};

template <typename T>
struct Vec<T, 1> : public vector<T> {
    Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};

}

static const int B = 17;

struct Node {
    Node* child[2];
    int cnt;
    i64 bitCnt[B+1];
    Node() : cnt(0) {
        child[0] = child[1] = nullptr;
        memset(bitCnt, 0, sizeof(bitCnt));
    }
};

Node* root;
i64 lazy_xor;

void ins(int x) {
    Node* p = root;
    p->cnt++;
    for (int j = 0; j <= B; ++j)
        if (x >> j & 1) p->bitCnt[j]++;
    for (int i = B; i >= 0; --i) {
        int c = (x >> i) & 1;
        if (!p->child[c]) p->child[c] = new Node();
        p = p->child[c];
        p->cnt++;
        for (int j = 0; j <= B; ++j)
            if (x >> j & 1) p->bitCnt[j]++;
    }
}

void del(int x) {
    Node* p = root;
    p->cnt--;
    for (int j = 0; j <= B; ++j)
        if (x >> j & 1) p->bitCnt[j]--;
    for (int i = B; i >= 0; --i) {
        int c = (x >> i) & 1;
        Node* nxt = p->child[c];
        nxt->cnt--;
        for (int j = 0; j <= B; ++j)
            if (x >> j & 1) nxt->bitCnt[j]--;
        if (nxt->cnt == 0) {
            p->child[c] = nullptr;
            return;
        }
        p = nxt;
    }
}

bool exist(int x) {
    Node* p = root;
    for (int i = B; i >= 0; --i) {
        int c = (x >> i) & 1;
        if (!p->child[c]) return false;
        p = p->child[c];
    }
    return p->cnt > 0;
}

int64_t sum_xor(int k) {
    i64 res = 0;
    Node* p = root;
    int prefix = 0;
    for (int i = B; i >= 0 && p && k > 0; --i) {
        int d = (lazy_xor >> i) & 1;
        Node* left = p->child[d];
        int cnt0 = left ? left->cnt : 0;
        if (k <= cnt0) {
            p = left;
            prefix = (prefix << 1) | d;
        } else {
            if (left) {
                for (int j = 0; j <= B; ++j) {
                    i64 ones = ((lazy_xor >> j) & 1)
                        ? (left->cnt - left->bitCnt[j])
                        : left->bitCnt[j];
                    res += ones << j;
                }
            }
            k -= cnt0;
            int c = d ^ 1;
            p = p->child[c];
            prefix = (prefix << 1) | c;
        }
    }
    if (p && k > 0) {
        int val = prefix;
        res += (i64)k * (val ^ lazy_xor);
    }
    return res;
}

void kakuai(void) {
    root = new Node();
    lazy_xor = 0;
    int q;
    cin >> q;
    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 0) ins(x ^ lazy_xor);
        else if (t == 1) {
            x ^= lazy_xor;
            if (exist(x)) del(x);
        } else if (t == 2) {
            lazy_xor ^= x;
        } else {
            cout << sum_xor(x) << '\n';
        }
    }
}

int32_t main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    kakuai();
    return 0;
}
