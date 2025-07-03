/*
	Author: kakuai
	created: 2025.07.02 20:26:27
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

struct edge_t {
	int u, v, w; 

	edge_t(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
	edge_t() {
		u = v = w = 0;
	}

	bool operator < (const edge_t& other) const {
		return w < other.w; 
	}
};

int n;
vector<edge_t> edges; 
int lab[1001]; 

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

void kakuai() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		int w; cin >> w; 
		edges.emplace_back(0, i, w);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int x; cin >> x; 

			if (i != j) {
				edges.emplace_back(i, j, x);
			}
		}
	}

	sort(edges.begin(), edges.end());

	memset(lab, -1, sizeof(lab)); 

	i64 ans = 0; 

	for (auto &e : edges) {
		int u = e.u; 
		int v = e.v; 
		int w = e.w; 

		if (joinSet(u, v)) {
			ans += w;
		}
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry ""
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}