/*
	Author: tinhnopro
	created: 2025.06.16 09:24:24
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

const int maxN = 1e6 + 5; 

int n, a[maxN], d[maxN]; 
vector<int> divs[maxN]; 

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

struct edge_t {
	int u, v, w; 
	edge_t(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

DisjiontSet dsu;
int used[maxN];

bool cmp(const edge_t &a, const edge_t &b) {
	return a.w < b.w; 
}

void tinhnop() {
	cin >> n; 

	int mx = 0; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		maximize(mx, a[i]);
	}

	for (int i = 1; i <= mx; ++i) {
		for (int j = i; j <= mx; j += i) divs[j].push_back(i);
	}

	i64 sum = 0; 

	for (int i = 1; i <= n; ++i) dsu.init(i);


	vector<edge_t> edges; 

	for (int i = 1; i <= n; ++i) {
		for (int j : divs[a[i]]) if (used[j]) {
			edges.push_back({i, used[j], 123456 - j});
		}

		for (int j : divs[a[i]]) if (used[j] == 0) used[j] = i;
	}

	sort(edges.begin(), edges.end(), cmp);

	for (auto &e : edges) {
		if (dsu.merge(e.u, e.v)) {
			sum += e.w; 
		}
	}

	cout << sum; 
	
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "gstree"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}