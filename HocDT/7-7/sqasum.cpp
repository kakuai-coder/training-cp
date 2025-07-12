/*
	Author: kakuai
	created: 2025.07.07 15:04:18
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 5e5 + 5;
const int Mod = 1e9 + 7;  

int n, q; 
int a[maxN];

struct Node {
	int cnt, sum, rsum, sign, tot;

	Node(int _cnt, int _sum, int _rsum, int _sign, int _tot) : cnt(_cnt), sum(_sum), rsum(_rsum), sign(_sign), tot(_tot) {}
	Node() {
		cnt = sum = rsum = sign = tot = 0; 
	}
} st[4 * maxN];

Node merge(const Node &a, const Node &b) {
	Node res; 

	if (a.cnt == 0) return b; 
	if (b.cnt == 0) return a; 

	res.cnt = a.cnt * b.cnt % Mod; 
	res.sum = (a.sum * b.cnt % Mod + b.sum * a.sign % Mod) % Mod;
	res.sign = a.sign * b.sign % Mod;
	res.rsum = (a.rsum * b.sign % Mod + b.rsum * a.cnt % Mod) % Mod;
	res.tot = (a.tot * b.cnt % Mod + b.tot * a.cnt % Mod + 2 * a.rsum * b.sum % Mod) % Mod;

	return res; 
}

void update(int id, int l, int r, int pos, int val) {
	if (l > pos || pos > r) return ;
	if (l == r) {
		st[id] = {2, val, (-val + Mod) % Mod, 0, val * val % Mod};

		return ; 
	}

	int mid = (l + r) >> 1; 
	update(id << 1, l, mid, pos, val);
	update(id << 1 | 1, mid + 1, r, pos, val);

	st[id] = merge(st[id << 1], st[id << 1 | 1]);
}

Node query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return {0, 0, 0, 1, 0};

	if (u <= l && r <= v) return st[id]; 

	int mid = (l + r) >> 1; 

	return merge(query(id << 1, l, mid, u, v), query(id << 1 | 1, mid + 1, r, u, v));
}


void kakuai() {
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	for (int i = 1; i <= n; ++i) update(1, 1, n, i, a[i]);

	while (q--) {
		int op, x, y; 
		cin >> op >> x >> y; 

		if (op == 1) {
			update(1, 1, n, x, y);
		} else {
			cout << query(1, 1, n, x, y).tot << '\n';
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "sqasum"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}