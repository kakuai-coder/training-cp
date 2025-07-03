/*
	Author: kakuai
	created: 2025.07.01 19:42:24
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5; 

struct edge_t {
	int u, v, w; 

	edge_t (int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
	edge_t() {
		u = v = w = 0;
	}
};

struct DisjointSet {
	int lab[maxN]; 

	DisjointSet() {
		memset(lab, -1, sizeof(lab));
	}

	int findPar(int u) {
		return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
	}

	bool joinSet(int u, int v) {
		u = findPar(u); 
		v = findPar(v); 
		
		if (u == v) return false; 

		if (lab[u] > lab[v]) swap(u, v);

		lab[u] += lab[v]; 
		lab[v] = u; 

		return true; 
	}
};

int n, m, x, p;
edge_t edges[maxN];
DisjointSet dsu; 

bool cmp(const edge_t &a, const edge_t &b) {
	return a.w < b.w; 
}

void kakuai() {
	cin >> n >> m >> x >> p;

	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w; 
		edges[i] = {u, v, w};
	}

	sort(edges + 1, edges + m + 1, cmp);

	vector<edge_t> mst;

	i64 W = 0, used = 0; 

	for (int i = 1; i <= m; ++i) {
		int u = edges[i].u; 
		int v = edges[i].v;
		int w = edges[i].w; 

		if (dsu.joinSet(u, v)) {
			mst.push_back(edges[i]);
			W += w; 
			used++;
		}
	}

	if (used < n - 1 || W > x) {
		cout << -1; 
		return ;
	}

	reverse(mst.begin(), mst.end()); 

	i64 sum = 0, cnt = 0; 

	for (edge_t &e : mst) {
		if (sum + W * p <= x) {
			// cout << sum << ' ' << W << ' ' << cnt << '\n';
			if (mst.size() - cnt == 0) cout << -1; 
			else cout << mst.size() - cnt; 
			return ; 
		}
		sum += e.w;
		W -= e.w;
		cnt++;
	}


	cout << -1; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a1"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}