/*
	Author: tinhnopro
	created: 24.03.2025 14:49:13
*/
#include <bits/stdc++.h>

#define CHERRY "4"

using namespace std;

using i64 = long long;

const int maxN = 2e5 + 5;
const int MOD = 1e9 + 7;

namespace FixMod {
	int add(int x, int y) {
		x += y; 
		if (x >= MOD) x -= MOD; 
		return x; 
	}

	int sub(int x, int y) {
		x -= y; 
		if (x < 0) x += MOD;
		return x;  
	}

	int mul(i64 x, int y) {
		if (x < 0) x += MOD; 
		if (y < 0) y += MOD; 
		i64 k = x * y; 
		return k % MOD; 
	}

	int sumsqr(int x) {
		long long x1 = 1LL * x * (x + 1) / 2; 
		long long x2 = 2LL * x + 1; 
		if (x1 % 3 == 0) x1 /= 3; 
		else x2 /= 3; 

		return mul(x1, x2);
	}

	int sumsqr(int l, int r) {
		return sub(sumsqr(r), sumsqr(l - 1));
	}

	int sum(int n) {
		long long x1 = 1LL * n * (n + 1) / 2; 
		return x1 % MOD;
	}

	int sum(int l, int r) {
		return sub(sum(r), sum(l - 1)); 
	}
};

using namespace FixMod;

struct Node {
	int val, lazy[3]; 

	Node() {
		val = 0; 
		memset(lazy, 0, sizeof(lazy));
	}

	void reset() {
		memset(lazy, 0, sizeof(lazy));
	}

	bool isEmpty() {
		for (int i = 0; i < 3; ++i) {
			if (lazy[i] != 0) return false; 
		}

		return true; 
	}

	int getval(int l, int r) {
		int d0 = mul(lazy[0], sumsqr(l, r)); 
		int d1 = mul(lazy[1], sum(l, r));
		int d2 = mul(lazy[2], r - l + 1);

		return add(d0, add(d1, d2));
	}

	Node operator +(const Node &other) const {
		Node a = *this; 
		a.lazy[0] = add(a.lazy[0], other.lazy[0]);
		a.lazy[1] = add(a.lazy[1], other.lazy[1]);
		a.lazy[2] = add(a.lazy[2], other.lazy[2]);
		return a;
	}

	Node(int _val, int x, int y, int z) : val(_val) {
		lazy[0] = x; 
		lazy[1] = y; 
		lazy[2] = z; 
	} 
};

Node st[4 * maxN]; 

void down(int& id, int& l, int& r, int& mid) {
	if (st[id].isEmpty()) return ; 

	int x = mid + 1 - l;

	Node tmp; 
	tmp.lazy[0] = st[id].lazy[0]; 
	tmp.lazy[1] = add(st[id].lazy[1], mul(x, mul(st[id].lazy[0], 2)));
	tmp.lazy[2] = mul(mul(st[id].lazy[0], x), x);
	tmp.lazy[2] = add(tmp.lazy[2], mul(st[id].lazy[1], x)); 	
	tmp.lazy[2] = add(tmp.lazy[2], st[id].lazy[2]);
	
	st[id << 1] = st[id << 1] + st[id];
	st[id << 1 | 1] = st[id << 1 | 1] + tmp; 

	st[id << 1].val = add(st[id << 1].val, st[id].getval(0, mid - l));
	st[id << 1 | 1].val = add(st[id << 1 | 1].val, st[id].getval(mid + 1 - l, r - l));

	st[id].reset();
}

void update(int id, int l, int r, int u, int v, int k, int x, int y, int z) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {
		int newK = k + l - u;
		Node tmp; 
		tmp.lazy[0] = x; 
		tmp.lazy[1] = add(y, mul(mul(x, 2), newK));
		tmp.lazy[2] = mul(mul(x, newK), newK);
		tmp.lazy[2] = add(tmp.lazy[2], mul(y, newK));
		tmp.lazy[2] = add(tmp.lazy[2], z);

		// cout << tmp.getval(0, r - l) << "\n";

		st[id] = st[id] + tmp; 
		st[id].val = add(st[id].val, tmp.getval(0, r - l));

		return ; 
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid);

	update(id << 1, l, mid, u, v, k, x, y, z); 
	update(id << 1 | 1, mid + 1, r, u, v, k, x, y, z); 

	st[id].val = add(st[id << 1].val, st[id << 1 | 1].val);
}

int sum(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0; 
	if (u <= l && r <= v) {
		return st[id].val;
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid); 

	return add(sum(id << 1, l, mid, u, v), sum(id << 1 | 1, mid + 1, r, u, v));
}


int n, q; 
int gval[3];

void solve() {
	cin >> n >> q; 
	
	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x, m, a, b, c; 
			cin >> x >> m >> a >> b >> c; 

			int d = 1; 
			update(1, 1, n, x, min(n, x + m - 1), d, a, b, c);


			int rem = m - (n - x + 1); 

			if (rem > 0) {
				d += n - x + 1; 
				int num = rem / n; 

				if (num > 0) {
					gval[0] = add(gval[0], mul(num, a));
					gval[1] = add(gval[1], mul(add(mul(2LL, mul(a, d - 1)), b), num));
					gval[1] = add(gval[1], mul(mul(2LL, mul(a, n)),  sum(1, num - 1)));
					gval[2] = add(gval[2], mul(mul(a, mul(n, n)), sumsqr(1, num - 1)));
					gval[2] = add(gval[2], mul(n, mul(sum(1, num - 1), add(mul(2LL, mul(a, d - 1)), b))));
					gval[2] = add(gval[2], mul(num,add(add(mul(mul(a,d - 1),d - 1),mul(b, d - 1)),c)));
				}

				d += num * n; 
				rem -= num * n; 
				if (rem > 0) {
					// cout << rem << ' ' << d << ' ' << a << ' ' << b << ' ' << c << '\n';
					update(1, 1, n, 1, rem, d, a, b, c);
				}
			} 
			
		} else {
			int l, r; 
			cin >> l >> r; 

			int val = Node(0, gval[0], gval[1], gval[2]).getval(l, r);

			// cerr << val << ' ' << sum(1, 1, n, l, r) << '\n';

			cout << add(val, sum(1, 1, n, l, r)) << '\n';
		}
	}

	return void(cout << '\n');
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	unsigned testcases = 1; 
	// cin >> testcases;

	for (unsigned test = 1; test <= testcases; ++test) {
		cerr << "Case #" << test << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}