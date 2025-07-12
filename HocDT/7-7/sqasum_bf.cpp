/*
    Author: kakuai
    created: 2025.07.07 14:30:00 (revised)
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const i64 MOD = 1000000007;

struct Node {
    i64 cnt;   // số subsequences bao gồm rỗng
    i64 s0;    // tổng alt-sum A(x)
    i64 p;     // tổng sign (-1)^{|x|}
    i64 s1;    // tổng alt-sum * sign = sum A(x)*(-1)^{|x|}
    i64 w;     // tổng A(x)^2
};

int n, q;
vector<i64> a;
vector<Node> seg;

Node mergeNode(const Node &A, const Node &B) {
    if (A.cnt == 0) return B;
    if (B.cnt == 0) return A;
    Node C;
    C.cnt = A.cnt * B.cnt % MOD;
    C.s0  = (A.s0 * B.cnt + A.p * B.s0) % MOD;
    C.p   = A.p * B.p % MOD;
    C.s1  = (A.s1 * B.p + A.cnt * B.s1) % MOD;
    C.w   = (A.w * B.cnt + B.w * A.cnt + 2 * (A.s1 * B.s0 % MOD)) % MOD;
    return C;
}

void build(int idx, int l, int r) {
    if (l == r) {
        i64 v = a[l] % MOD;
        seg[idx] = {2, v, (1 - 1 + MOD) % MOD, (MOD - v) % MOD /* s1 = -v */, v * v % MOD};
        // p = 1 (empty) + (-1) (one-element) = 0
        seg[idx].p = 0;
    } else {
        int mid = (l + r) >> 1;
        build(idx<<1, l, mid);
        build(idx<<1|1, mid+1, r);
        seg[idx] = mergeNode(seg[idx<<1], seg[idx<<1|1]);
    }
}

void update(int idx, int l, int r, int pos, i64 v) {
    if (l == r) {
        v %= MOD;
        seg[idx] = {2, v, 0, (MOD - v) % MOD, v * v % MOD};
    } else {
        int mid = (l + r) >> 1;
        if (pos <= mid) update(idx<<1, l, mid, pos, v);
        else           update(idx<<1|1, mid+1, r, pos, v);
        seg[idx] = mergeNode(seg[idx<<1], seg[idx<<1|1]);
    }
}

Node query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return {0,0,1,0,0}; // cnt=0 marks empty
    if (ql <= l && r <= qr) return seg[idx];
    int mid = (l + r) >> 1;
    Node L = query(idx<<1, l, mid, ql, qr);
    Node R = query(idx<<1|1, mid+1, r, ql, qr);
    return mergeNode(L, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    a.assign(n+1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    seg.assign(4*n+4, {0,0,1,0,0});

    build(1, 1, n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i; i64 v;
            cin >> i >> v;
            update(1, 1, n, i, v);
        } else {
            int l, r;
            cin >> l >> r;
            Node res = query(1, 1, n, l, r);
            // res.w đã là tổng bình phương cho mọi dãy con (rỗng cho w=0)
            // chỉ cần in res.w
            cout << res.w << '\n';
        }
    }
    return 0;
}
