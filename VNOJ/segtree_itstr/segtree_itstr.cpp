#include <bits/stdc++.h>

#define TASK "segtree_itstr"

using namespace std;

using i64 = long long;

const int mod = 1007050321;
const int maxN = 1e5 + 5;

string s;
int n, q;
int pw2[maxN];

int mul(int a, int b) {
	i64 x = 1LL * a * b; 
	return x % mod; 
}

struct Node {
	i64 val; 
	int len; 

	Node(i64 _val = 0, int _len = 0) : val(_val), len(_len) {} 

	Node operator + (const Node& other) const {
		Node ret; 
		ret.len = len + other.len; 
		ret.val = (mul(val, pw2[other.len]) + other.val) % mod; 
		return ret;
	}
};



Node st[4 * maxN]; 

void build(int id, int l, int r) {
	if (l == r) {
		st[id].val = s[l] - '0';
		st[id].len = 1; 
		return ; 
	}

	int mid = (l + r) >> 1; 
	build(id << 1, l, mid); 
	build(id << 1 | 1, mid + 1, r); 

	st[id] = st[id << 1] + st[id << 1 | 1]; 
}

void update(int id, int l, int r, int pos) {
	if (l > pos || r < pos) return ; 
	if (l == r) {
		st[id].val = st[id].len = 0;
		return ; 
	}

	int mid = (l + r) >> 1; 
	update(id << 1, l, mid, pos); 
	update(id << 1 | 1, mid + 1, r, pos);

	st[id] = st[id << 1] + st[id << 1 | 1]; 
}

int walk(int id, int l, int r, int pos) {
	if (l == r) return l; 

	int mid = (l + r) >> 1; 
	if (pos <= st[id << 1].len) return walk(id << 1, l, mid, pos); 
	else return walk(id << 1 | 1, mid + 1, r, pos - st[id << 1].len);
}

Node query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) {
		return Node();
	}
	if (u <= l && r <= v) {
		return st[id];
	}

	int mid = (l + r) >> 1; 

	return query(id << 1, l, mid, u, v) + query(id << 1 | 1, mid + 1, r, u, v);
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK ".inp", "r")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	cin >> s >> q;

	n = (int)s.size();
	s = ' ' + s;

	pw2[0] = 1; 
	for (int i = 1; i <= n; ++i)
		pw2[i] = 1LL * pw2[i - 1] * 2 % mod; 
	build(1, 1, n);

	while (q--) {
		char op;
		cin >> op;
		if (op == '-') {
			int P;
			cin >> P;
			P = walk(1, 1, n, P);
			update(1, 1, n, P);

		} else {
			int l, r;
			cin >> l >> r;
			l = walk(1, 1, n, l);
			r = walk(1, 1, n, r); 
			cout << query(1, 1, n, l, r).val << '\n';
		}
	}
}