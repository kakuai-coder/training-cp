/*
Author: kakuai
created: 2025.07.26
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int size32(const T &a) {
	return (int)a.size();
}

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
}  // namespace std

const int maxN = 4e5 + 5; 

int n, q, a[maxN];

struct Compress {
	vector<int> H; 
	
	
	void add(const int &x) {
		H.push_back(x);
	}

	void init() {
		sort(H.begin(), H.end()); 

		H.erase(unique(H.begin(), H.end()), H.end());
	}

	int get(const int &x) const {
		return lower_bound(H.begin(), H.end(), x) - H.begin() + 1; 
	}
} Z; 

struct PersistentSegTree {
	struct Node {
		int val, l, r; 
		Node() {
			val = 0; 
			l = r = -1; 
		}

		Node(int _val, int _l, int _r) : val(_val), l(_l), r(_r) {}
	};

	Node tree[maxN * 20];

	int root[maxN];

	int cnt_node = 0;

	int build(int l, int r) {
		int id = cnt_node++;
		if (l == r) {
			tree[id] = Node(0, -1, -1);
			return id; 
		}
		
		int m = (l + r) >> 1;
		tree[id].l = build(l, m);
		tree[id].r = build(m+1, r);
		

		return id;
	}

	int update(int prev, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return prev; 

		int id = cnt_node++; 

		tree[id] = tree[prev]; 

		if (l == r) {
			tree[id].val += val; 
			return id; 
		}

		int mid = (l + r) >> 1; 

		if (pos <= mid) {
			tree[id].l = update(tree[prev].l, l, mid, pos, val);
		} else {
			tree[id].r = update(tree[prev].r, mid + 1, r, pos, val);
		}

		tree[id].val = 0;

		if (tree[id].l != -1) tree[id].val += tree[tree[id].l].val;
		if (tree[id].r != -1) tree[id].val += tree[tree[id].r].val;

		return id; 
	}
	int query(int id, int l, int r, int u, int v) {
		if (v < l || r < u) return 0;
		
		if (u <= l && r <= v) return tree[id].val;
		
		int mid = (l + r) >> 1;

		return query(tree[id].l, l, mid, u, v) + query(tree[id].r, mid + 1, r, u, v);
	}
};
PersistentSegTree seg; 

vector<int> pos[maxN];


void kakuai(void) {
	// voi26 = winner
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		Z.add(a[i]);
	}

	Z.init();

	for (int i = 1; i <= n; ++i) a[i] = Z.get(a[i]);

	for (int i = 1; i <= n; ++i) pos[a[i]].push_back(i);
	

	seg.cnt_node = 0; 
	seg.root[0] = seg.build(1, n);

	int cur; 

	for (int i = 1; i <= n; ++i) {
		cur = seg.root[i];
		
		for (int &x : pos[i]) {
			cur = seg.update(cur, 1, n, x, 1);
		}

		seg.root[i + 1] = cur; 
	}

	int lo = 0, hi = n + 1, d, cnt, mid; 
	
	while (q--) {
		int l, r; 
		cin >> l >> r; 
		
		cnt  = n - (r - l + 1); 

		cnt = (cnt + 1) / 2; 

		lo = 0;
		hi = n + 1;

		while (hi - lo > 1) {
			mid = (lo + hi) >> 1; 

			d = seg.query(seg.root[mid + 1], 1, n, 1, l - 1) + seg.query(seg.root[mid + 1], 1, n, r + 1, n);

			if (d >= cnt) {
				hi = mid;
			} else lo = mid; 
		}

		cout << Z.H[hi - 1] << '\n';
	}
	
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "b"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}