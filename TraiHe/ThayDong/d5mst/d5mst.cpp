/*
	Author: tinhnopro
	created: 2025.06.16 07:57:33
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 5e5 + 5; 

struct node_t {
	int id, l, r, c; 

	node_t() {
		id = l = r = c = 0; 
	}

	node_t(int _id, int _l, int _r, int _c) : id(_id), l(_l), r(_r), c(_c) {}
};

struct DisjiontSet {
	int lab[maxN];
	int last[maxN]; 

	DisjiontSet() {
		memset(lab, 0, sizeof(lab)); 
		memset(last, 0, sizeof(last));
	}

	void init(int i) {
		lab[i] = -1; 
		last[i] = i; 
	}

	int find_par(int u) {
		return lab[u] < 0 ? u : lab[u] = find_par(lab[u]);
	}

	bool merge(int u, int v) {
		u = find_par(u); 
		v = find_par(v); 

		if (u == v) return false; 

		if (lab[u] > lab[v]) swap(u, v); 

		lab[u] += lab[v]; 
		lab[v] = u; 
		maximize(last[u], last[v]);

		return true;
	}

	int jump(int x) {
		return last[find_par(x)];
	}
};

int n, s; 
vector<node_t> edges;
DisjiontSet dsu;
int nxt[maxN];

bool cmp(const node_t &a, const node_t &b) {
	return a.c < b.c; 
}

void tinhnop() {
	cin >> n >> s; 
	for (int i = 1; i <= s; ++i) {
		int l, r, c; 
		cin >> l >> r >> c; 
		edges.push_back({n + i, l, r, c});
		// cout << l << ' ' << r << ' ' << c << '\n';
	} 

	sort(edges.begin(), edges.end(), cmp);

	for (int i = 1; i <= n + s; ++i) dsu.init(i);


	i64 sum = 0;

	int cnt = 0;

	for (auto &e : edges) {
		int id = e.id; 
		int l = e.l; 
		int r = e.r; 
		int c = e.c; 

		sum += c; 
		cnt++;

		for (int i = dsu.jump(l); i < r; i = dsu.jump(i)) {
			if (dsu.merge(i, i + 1)) {
				sum += c;
				cnt++;
			}
		}
	}

	if (cnt != n + s - 1) cout << -1; 
	else cout << sum; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d5mst"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
