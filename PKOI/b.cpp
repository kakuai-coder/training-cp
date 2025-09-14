#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cnt[3];   // cnt[0]=#(<x), cnt[1]=#(=x), cnt[2]=#(>x)
    int lazy;     // 0 = none, 1 = sort asc, 2 = sort desc
    Node() {
        cnt[0]=cnt[1]=cnt[2]=0;
        lazy = 0;
    }
};

vector<Node> st;
int n, q;
int x;

// merge hai node con
Node merge(const Node &L, const Node &R) {
    Node p;
    for(int i=0;i<3;i++) p.cnt[i] = L.cnt[i] + R.cnt[i];
    return p;
}

// đẩy lazy xuống 2 con
void apply(int p, int l, int r, int typ) {
    // giữ nguyên số lượng, chỉ đánh dấu kiểu sort
    st[p].lazy = typ;
}

void push(int p, int l, int r) {
    if (st[p].lazy == 0 || l == r) return;
    int mid = (l + r) >> 1;
    int lenL = mid - l + 1;
    int lenR = r - mid;
    int typ = st[p].lazy;
    int a = st[p].cnt[0], b = st[p].cnt[1], c = st[p].cnt[2];

    // tính phân bổ cho con trái
    int c0L, c1L, c2L;
    if (typ == 1) {
        // asc: <x rồi =x rồi >x
        c0L = min(a, lenL);
        c1L = min(b, lenL - c0L);
        c2L = lenL - c0L - c1L;
    } else {
        // desc: >x rồi =x rồi <x
        c2L = min(c, lenL);
        c1L = min(b, lenL - c2L);
        c0L = lenL - c2L - c1L;
    }
    // con phải lấy phần còn lại
    int c0R = a - c0L;
    int c1R = b - c1L;
    int c2R = c - c2L;

    // gán cho 2 con
    int Lp = p<<1, Rp = p<<1|1;
    st[Lp].cnt[0]=c0L; st[Lp].cnt[1]=c1L; st[Lp].cnt[2]=c2L; st[Lp].lazy = typ;
    st[Rp].cnt[0]=c0R; st[Rp].cnt[1]=c1R; st[Rp].cnt[2]=c2R; st[Rp].lazy = typ;

    // clear lazy của p
    st[p].lazy = 0;
}

void build(int p, int l, int r, const vector<int> &a) {
    if (l == r) {
        st[p].cnt[0] = (a[l] < x);
        st[p].cnt[1] = (a[l] == x);
        st[p].cnt[2] = (a[l] > x);
    } else {
        int mid = (l + r) >> 1;
        build(p<<1, l, mid, a);
        build(p<<1|1, mid+1, r, a);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
}

// cập nhật sort [L,R] kiểu typ (1=asc,2=desc)
void update(int p, int l, int r, int L, int R, int typ) {
    if (R < l || r < L) return;
    if (L <= l && r <= R) {
        // tại p đã có đủ cnts, chỉ cần đánh dấu lazy
        apply(p, l, r, typ);
        return;
    }
    push(p, l, r);
    int mid = (l + r) >> 1;
    update(p<<1, l, mid, L, R, typ);
    update(p<<1|1, mid+1, r, L, R, typ);
    st[p] = merge(st[p<<1], st[p<<1|1]);
}

// tìm vị trí i sao cho ở lá i có cnt[1]==1
int findPos(int p, int l, int r) {
    if (l == r) return l;
    push(p, l, r);
    int mid = (l + r) >> 1;
    if (st[p<<1].cnt[1] > 0) return findPos(p<<1, l, mid);
    else return findPos(p<<1|1, mid+1, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> x;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    st.assign(4*(n+5), Node());
    build(1,1,n,a);

    while(q--){
        int typ, l, r;
        cin >> typ >> l >> r;
        update(1,1,n,l,r, typ);
    }

    int ans = findPos(1,1,n);
    cout << ans << "\n";
    return 0;
}
