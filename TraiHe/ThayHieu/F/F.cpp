/*
	Author: kakuai
	created: 2025.06.22 17:13:17
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

const int maxN = 1e3 + 5; 

int n, m;
vector<int> adj[maxN], down[maxN], unfinshed;
int isPath[maxN][maxN];
int dp[maxN][1 << 12], w[11][11]; 

void dfs(int u, int par = -1) {
	for (int v : adj[u]) if (v != par) {
		dfs(v, u);
		dp[u][0] += dp[v][0]; 
	}

	unfinshed.clear();
	unfinshed.push_back(u);

	for (int v : adj[u]) if (v != par) {
		bool ok = false; 
		for (int x : down[v]) if (isPath[u][x]) {
			dp[u][0]++; 
			ok = true; 
			break; 
		}

		if (!ok) unfinshed.push_back(v);
	}

	int k = ssize(unfinshed); 

	memset(w, 0, sizeof(w));

	for (int i = 1; i < k; ++i) {
		for (int j = i + 1; j < k; ++j) {
			for (int x : down[unfinshed[i]]) {
				for (int y : down[unfinshed[j]]) if (isPath[x][y]) {
					w[i][j] = 1; 
					break; 
				}
				if (w[i][j] == 1) break; 
			}
		}
	}

	for (int mask = 1; mask < (1 << k); ++mask) {
		for (int i = 1; i < k; ++i) if ((mask >> i) & 1) {
			for (int j = i + 1; j < k; ++j) if ((mask >> j) & 1) {
				maximize(dp[u][mask], dp[u][mask ^ (1 << i) ^ (1 << j)] + w[i][j]);
			}
		}
	}

	dp[u][0] += dp[u][(1 << k) - 1];
	
	down[u].push_back(u); 

	int full = (1 << k) - 1;

	for (int i = 1; i < k; ++i) if (dp[u][full] == dp[u][full ^ (1 << i)]) {
		for (int x : down[unfinshed[i]]) down[u].push_back(x);
	}
}

void kakuai() {
	cin >> n >> m; 
	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		isPath[u][v] = isPath[v][u] = 1;
	}

	dfs(1);
	cout << dp[1][0];
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "f"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}