// kakuai ^><^ || cherry  
#include <bits/stdc++.h>
#define task "a"

using namespace std;

const int MAXN = 3e5 + 5; 

int n, q;
char a[MAXN];

struct Node {
	int l, r, val; 

	Node() {
		l = r = -1; 
		val = 0;
	}

	Node(int _l, int _r, int _val) : l(_l), r(_r), val(_val) {}

	void merge(const Node &L, const Node &R) {
		this->val = L.val | R.val;
	}
};

Node seg[4 * MAXN];

int c2bit(char x) {
	if (x >= 'a' && x <= 'z') return 1;
	if (x >= 'A' && x <= 'Z') return 2; 
	if (x >= '0' && x <= '9') return 4; 

	return 0;
}

void build(int id, int l, int r) {
	if (l == r) {
		seg[id] = Node(l, l, c2bit(a[l]));
		return ;
	}

	int mid = (l + r) >> 1; 

	build(id << 1, l, mid); 
	build(id << 1 | 1, mid + 1, r); 

	seg[id].l = l; 
	seg[id].r = r; 

	seg[id].merge(seg[id << 1], seg[id << 1 | 1]);
}

void update(int id, int pos, int val) {
	if (seg[id].l > pos || seg[id].r < pos) return ; 
	if (seg[id].l == seg[id].r) {
		seg[id].val = val; 
		return ; 
	}

	update(id << 1, pos, val); 
	update(id << 1 | 1, pos, val);

	seg[id].merge(seg[id << 1], seg[id << 1 | 1]);
}

int query(int id, int l, int r) {
	if (seg[id].l > r || seg[id].r < l) return 0; 

	if (l <= seg[id].l && seg[id].r <= r) return seg[id].val;

	return query(id << 1, l, r) | query(id << 1 | 1, l, r);
}

void solve(void) { 
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	build(1, 1, n);

	while (q--) {
		int op, l, r; 
		cin >> op >> l >> r; 

		if (op == 1) {
			swap(a[l], a[r]);
			update(1, l, c2bit(a[l]));
			update(1, r, c2bit(a[r]));
		} else {
			if (r - l + 1 < 6) {
				cout << "0\n";
				continue;
			} 

			int x = query(1, l, r); 

			cout << (x == 7) << '\n';
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(task ".inp", "r")) {
		freopen(task ".inp", "r", stdin);
		freopen(task ".out", "w", stdout);
	}

	int t = 1; // cin >> t;
	while (t--) {
		solve(); // cout << '\n';
	}
}