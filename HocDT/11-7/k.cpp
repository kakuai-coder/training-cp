/*
Author: kakuai
created: 2025.07.14
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

const int maxN = 1e6 + 5;  

int n, q, s; 
int a[maxN], lpf[maxN], pos[maxN];
vector<pair<int, int>> upd[maxN];

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

void kakuai(void) {
	// voi26 = winner
	cin >> n >> q >> s;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	vector<int> primes; 

	for (int i = 1; i < maxN; ++i) lpf[i] = i; 

	for (int i = 2; i * i < maxN; ++i) if (lpf[i] == i) {
		for (int j = i * i; j < maxN; j += i) if (lpf[j] == j) lpf[j] = i;
	}

	for (int i = 2; i < maxN; ++i) if (lpf[i] == i) { 
		pos[i] = primes.size();
		primes.push_back(i);
	}

	
	for (int i = 1; i <= n; ++i) {
		while (a[i] > 1) {
			int cnt = 0; 
			int x = lpf[a[i]];
			while (a[i] % x == 0) {
				a[i] /= x;
				cnt++;
			}
			
			upd[pos[x]].emplace_back(i, cnt);
		}
	}
	
	// cerr << "ok";
	
	seg.cnt_node = 0; 
	seg.root[0] = seg.build(1, n);

	for (int i = 0; i < size32(primes); ++i) {
		int cur = seg.root[i];

		for (auto &x : upd[i]) {
			cur = seg.update(cur, 1, n, x.first, x.second);
		}

		seg.root[i + 1] = cur; 
	}

	int64_t sum = 0;
	while (q--) {
		int x, y, z, t;
		cin >> x >> y >> z >> t;
		int l = min((x + sum * s) % n, (y + sum * s) % n) + 1;
		int r = max((x + sum * s) % n, (y + sum * s) % n) + 1;
		int u = min((z + sum * s) % 1000000, (t + sum * s) % 1000000) + 1;
		int v = max((z + sum * s) % 1000000, (t + sum * s) % 1000000) + 1;

		int id_l = lower_bound(primes.begin(), primes.end(), u) - primes.begin();
		int id_r = upper_bound(primes.begin(), primes.end(), v) - primes.begin();

		// cerr << id_l << ' ' << id_r << '\n';

		int ans = seg.query(seg.root[id_r], 1, n, l, r) - seg.query(seg.root[id_l], 1, n, l, r);
		cout << ans << '\n';
		sum += ans;
	}

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "k"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}