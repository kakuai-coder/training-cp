/*
	Author: kakuai
	created: 2025.07.02 23:16:59
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

const int MaxN = 2e5 + 5; 
const int Log = 17; 

int n, q; 
vector<int> adj[MaxN];
int depth[MaxN], up[Log + 1][MaxN];

void dfs(int u, int par) {
	up[0][u] = par; 
	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	for (int v : adj[u]) if (v ^ par) {
		depth[v] = depth[u] + 1; 
		dfs(v, u);
	}
}

void kakuai() {
	cin >> n >> q; 

	for (int i = 2; i <= n; ++i) {
		int u; cin >> u; 
		adj[u].push_back(i); 
		adj[i].push_back(u);
	}

	dfs(1, 0);

	while (q--) {
		int x, k;
		cin >> x >> k;
		
		for (int i = 0; i <= Log; ++i) if ((k >> i) & 1) {
			x = up[i][x];
		}

		cout << (x == 0 ? -1 : x) << '\n';
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b3"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}