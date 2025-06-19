#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7;
int add(int x, int y) {
    if ((x+=y)>=MOD)x-=MOD;
    return x;
}
int sub(int x, int y) {
    if ((x-=y)<0)x+=MOD;
    return x;
}
int mul(long long x, int y) {
    return x * y % MOD;
}

const int N = 2e5+7;
int n, q;

int sumsqr(int n) {
    long long x = 1LL * n * (n + 1) / 2;
    long long y = 2LL * n + 1;
    if (x % 3 == 0) x /= 3;
    else y /= 3;
    return mul(x%MOD,y%MOD);
}

int sumsqr(int l, int r) {
    return sub(sumsqr(r), sumsqr(l-1));
}

int sum(int n) {
    return 1LL * n * (n + 1) / 2 % MOD;
}

int sum(int l, int r) {
    return sub(sum(r), sum(l-1));
}

struct Node {
    int v[3];
    Node() {
        memset(v, 0, sizeof v);
    }
    Node(int x, int y, int z) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
    Node operator + (const Node& n) {
        return Node(add(v[0],n.v[0]),add(v[1],n.v[1]),add(v[2],n.v[2]));
    }
    void operator += (const Node& n) {
        *this = *this + n;
    }
    bool isEmpty() {
        for (int i = 0; i < 3; ++i) {
            if (v[i] != 0) return false;
        }
        return true;
    }
    void makeEmpty() {
        memset(v, 0, sizeof v);
    }
    int eval(int l, int r) {
        int d2 = mul(v[2], sumsqr(l, r));
        int d1 = mul(v[1], sum(l, r));
        int d0 = mul(v[0], r-l+1);
        return add(add(d2,d1),d0);
    }
    friend ostream& operator << (ostream& os, const Node& n) {
        os << "(" << n.v[2] << ", " << n.v[1] << ", " << n.v[0] << ")";
        return os;
    }
};

struct SegTree {
    int size;
    int node[N*4];
    Node lazy[N*4];
    void init(int n) {
        size = n;
    }
    void pushDown(int id, int l, int r) {
        if (!lazy[id].isEmpty()) {
            int m = l+r>>1;
            int x = m+1-l;
            lazy[id<<1] += lazy[id];
            // lazy[id<<1|1] += lazy[id] + Node(add(mul(lazy[id].v[1],x), mul(mul(x,x),lazy[id].v[2])), mul(mul(2,x),lazy[id].v[2]), 0);
            int v[3] = {0};
            v[2] = 0;
            v[1] = mul(mul(2,lazy[id].v[2]),x);
            v[0] = mul(mul(lazy[id].v[2], x),x);
            v[0] = add(v[0], mul(lazy[id].v[1], x));
            // cerr << " >> " << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
            lazy[id<<1|1] += lazy[id] + Node(v[0], v[1], v[2]);
            node[id<<1] = add(node[id<<1], lazy[id].eval(0, m-l));
            node[id<<1|1] = add(node[id<<1|1], lazy[id].eval(m+1-l, r-l));
            lazy[id].makeEmpty();
        }
    }
    void update(int id, int l, int r, int x, int y, int k, int a, int b, int c) {
        if (l>y||r<x) return;
        if (l>=x&&r<=y) {
            // lazy[id] += Node(mul(k+(l-x),k+(l-x)), mul(2,k+(l-x)), 1);
            int v[3] = {0};
            int newK = k + (l-x);
            v[2] = a;
            v[1] = add(mul(mul(2,a),newK), b);
            v[0] = mul(mul(a, newK), newK);
            v[0] = add(v[0], mul(b, newK));
            v[0] = add(v[0], c);
            Node newNode(v[0], v[1], v[2]);
            lazy[id] += newNode;
						// cout << newNode.eval(0, r - l) << '\n';
            node[id] = add(node[id], newNode.eval(0, r-l));
            return;
        }
        pushDown(id, l, r);
        int m = l+r>>1;
        update(id<<1,l,m,x,y,k,a,b,c);
        update(id<<1|1,m+1,r,x,y,k,a,b,c);
        node[id] = add(node[id<<1], node[id<<1|1]);
    }
    void update(int x, int y, int k, int a, int b, int c) {
        update(1,1,size,x,y,k,a,b,c);
    }
    int getsum(int id, int l, int r, int x, int y) {
        if (l>y||r<x) return 0;
        if (l>=x&&r<=y) return node[id];
        pushDown(id, l, r);
        int m = l+r>>1;
        return add(getsum(id<<1,l,m,x,y), getsum(id<<1|1,m+1,r,x,y));
    }
    int getsum(int x, int y) {
        return getsum(1,1,size,x,y);
    }
    void debug(int n = -1) {
        if (n == -1) n = size*4;
        for (int i = 1; i <= n; ++i) {
            cerr << i << " --> " << node[i] << " | " << lazy[i] << '\n';
        }
        cerr << '\n';
    }
} st;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("4.inp", "r", stdin);
    freopen("4.ans", "w", stdout);

    cin >> n >> q;

    st.init(n);

    int gval[3] = {0};

    while (q--) {
        int t;
        cin >> t;
        if (t==1) {
            int x, m, a, b, c;
            cin >> x >> m >> a >> b >> c;
            int start = 1;
            // cerr << " >1 " << x << ' ' << min(n, x+m-1) << ' ' << start << '\n';
            st.update(x, min(n, x+m-1), start, a, b, c);
            int rem = m - (n - x + 1);
            if (rem > 0) {
                start += n - x + 1;
                int num = rem / n;
                if (num > 0) {
                    // cerr << " >2 " << num << ' ' << start << '\n';
                    // gval[2] = add(gval[2], num);
                    // gval[1] = add(gval[1], add(mul(mul(2,num),start), mul(mul(num-1, num), n)));
                    // gval[0] = add(gval[0], add(add(mul(mul(start,start),num), mul(mul(mul(num-1,num),n),start)), mul(mul(n,n),sumsqr(1, num-1))));
                    gval[2] = add(gval[2], mul(num, a));
                    gval[1] = add(gval[1], mul(mul(mul(2,a),n),sum(1,num-1)));
                    gval[1] = add(gval[1], mul(add(mul(mul(2,a),start),b),num));
                    gval[0] = add(gval[0], mul(mul(mul(a,n),n),sumsqr(1,num-1)));
                    gval[0] = add(gval[0], mul(mul(add(mul(mul(2,a),start),b),n),sum(1,num-1)));
                    gval[0] = add(gval[0], mul(num,add(add(mul(mul(a,start),start),mul(b,start)),c)));
                }
                start += num * n;
                rem -= num * n;
                if (rem > 0) {
										// cout << rem << ' ' << start << ' ' << a << ' ' << b << ' ' << c;  
                    // cerr << " >3 " <<  1 << ' ' << rem << ' ' << start << '\n';
                    st.update(1, rem, start, a, b, c);
                }
            }
            // cerr << '\n';
        } else {
            int l, r;
            cin >> l >> r;
            int d0 = mul(gval[0], r - l + 1);
            int d1 = mul(gval[1], sum(l-1, r-1));
            int d2 = mul(gval[2], sumsqr(l-1, r-1));
            cerr << " >>> " << add(add(d0, d1), d2) << '\n';    
            cerr << " >> " << st.getsum(l, r) << '\n';
            int res = add(add(add(d0, d1), d2), st.getsum(l, r));
            cout << res << '\n';
        }
        // st.debug(8);
    }
    return 0;
}