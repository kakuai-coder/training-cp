#include <bits/stdc++.h>

#define TASK "segtree_itladder"
#define int long long

using namespace std;

const int maxN = 1e5 + 5;
const int mod = 1e9 + 7;

void add(int& a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int mul(int a, int b) {
	long long x = 1LL * a * b;
	return x % mod;
}

int sum(int l, int r) {
	int R = (1LL * r * (r + 1) / 2) % mod;
	int L = (1LL * (l - 1) * l / 2) % mod;
	R = (R - L + mod) % mod;
	return R;
}

struct Node {
	int mul, add, val;

	Node() : mul(0), add(0), val(0) {}
	Node(int _mul, int _add, int _val) : mul(_mul), add(_add), val(_val) {}
};

Node st[4 * maxN];


void down(const int& id, const int& l, const int& r, const int& mid) {

	add(st[id << 1].add, st[id].add);
	add(st[id << 1 | 1].add, st[id].add);

	add(st[id << 1].mul, st[id].mul);
	add(st[id << 1 | 1].mul, st[id].mul);

	add(st[id << 1].val, mul(mid - l + 1, st[id].add));
	add(st[id << 1 | 1].val, mul(r - mid, st[id].add));

	add(st[id << 1].val, mul(sum(l, mid), st[id].mul));
	add(st[id << 1 | 1].val, mul(sum(mid + 1, r), st[id].mul));

	st[id].mul = st[id].add = 0;
}

void update(int id, int l, int r, int u, int v, int a, int b) {
	if (l > v || r < u) return ;
	if (u <= l && r <= v) {
		add(st[id].add, (b - mul(a, u) + mod) % mod);
		add(st[id].mul, a);
		add(st[id].val, mul(sum(l, r), a));
		add(st[id].val, mul(r - l + 1, (b - mul(a, u) + mod) % mod));
		return ;
	}

	int mid = (l + r) >> 1;

	down(id, l, r, mid);

	update(id << 1, l, mid, u, v, a, b);
	update(id << 1 | 1, mid + 1, r, u, v, a, b);

	st[id].val = st[id << 1].val + st[id << 1 | 1].val;
	st[id].val %= mod;
}

int query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0 % mod;
	if (u <= l && r <= v) {
		return st[id].val % mod;
	}

	int mid = (l + r) >> 1;
	down(id, l, r, mid);

	return ( query(id << 1, l, mid, u, v) +
					query(id << 1 | 1, mid + 1, r, u, v)) % mod;
}

int n, q;


int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> n >> q;

	while (q--) {
		int type; cin >> type;

		if (type == 1) {
			int l, r, a, b;
			cin >> l >> r >> a >> b;
			update(1, 1, n, l, r, a, b);
		} else {
			int l, r; cin >> l >> r;
			cout << query(1, 1, n, l, r) << '\n';
		}
	}
}
