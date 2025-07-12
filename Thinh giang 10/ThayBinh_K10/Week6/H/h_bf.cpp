#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FOR(i, a, b) for(int i = a; i <= b; i ++)
#define FORD(i, b, a) for(int i = b; i >= a; i --)
#define MASK(o) (1ll << (o))
#define __builtin_popcount __builtin_popcountll
#define C_BIT(mask) __builtin_popcount(mask)
#define BIT(mask, i) ((mask) & (1ll << (i)))
#define ONBIT(mask, i) ((mask) | (1ll << (i)))
#define ii pair<int, int>
#define fi first
#define se second
#define pb push_back

const int maxN = 2e5 + 5;

int A[maxN];
int W[maxN];
int n;
int dp[maxN];

struct Node {
    int l, r, val;
};

int maxi(int x, int y) {
    if (dp[x] > dp[y])
        return x;
    if (x > y && dp[x] == dp[y])
        return x;
    return y;
}

struct Segment_tree {
    Node ST[maxN * 4];

    void build(int id, int l, int r) {
        ST[id].l = l;
        ST[id].r = r;
        ST[id].val = 0;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }

    void update(int id, int p, int v) {
        if (ST[id].l == p && ST[id].r == p) {
            ST[id].val = max(v, ST[id].val);
            return;
        }
        if (ST[id].l > p || ST[id].r < p)
            return;
        update(id << 1, p, v);
        update(id << 1 | 1, p, v);
        ST[id].val = max(ST[id << 1].val, ST[id << 1 | 1].val);
    }

    int get(int id, int u, int v) {
        if (u <= ST[id].l && ST[id].r <= v)
            return ST[id].val;
        if (u > ST[id].r || ST[id].l > v)
            return 0;
        return max(get(id << 1, u, v), get(id << 1 | 1, u, v));
    }
} Seg1, Seg2;

int as[maxN];
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

	#define cherry "h"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

    cin >> n;
    FOR(i, 1, n)
        cin >> A[i];
    FOR(i, 1, n)
        cin >> W[i];
    vector<int> s;
    FOR(i,1 , n)
        s.pb(A[i]);
    sort(s.begin(), s.end());
    FOR(i, 1, n)
        A[i] = lower_bound(s.begin(), s.end(), A[i]) - s.begin() + 1;

    Seg1.build(1, 1, 1e5 + 3);

    FORD(i, n, 1) {
        dp[i] = Seg1.get(1, A[i] + 1, 1e5 + 3) + W[i];
        Seg1.update(1, A[i], dp[i]);

				cout << dp[i] << ' ';
    }

    Seg2.build(1, 1, 1e5 + 3);

    int res = 0;

    FORD(i, n, 1) {
        int as = Seg2.get(1, 1, A[i] - 1);
        res = max(res, dp[i] + as);
        //cout << i << " " << dp[i] << " " << as << "\n";
        Seg2.update(1, A[i], as + W[i]);
    }

    cout << res;
    return 0;
}