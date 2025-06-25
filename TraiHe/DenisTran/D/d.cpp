/*
	Author: kakuai
	created: 2025.06.23 14:20:50
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

const int maxN = 2e5 + 5; 

int n, k, a[maxN];
vector<int> adj[maxN];
map<int, int> dp[maxN], g; 

int gcd(int a, int b) {
	int r; 
	while (b) {
		r = a % b; 
		a = b; 
		b = r; 
	}

	return a; 
}

void dfs(int u, int par) {
	dp[u][a[u]] = 0;

	for (int v : adj[u]) if (v != par) {
		dfs(v, u); 

		g = dp[u];

		for (auto &x : g) {
			for (auto &y : dp[v]) {
				int t = gcd(x.first, y.first);
				if (dp[u].find(t) == dp[u].end()) {
					dp[u][t] = x.second + y.second; 
				} else dp[u][t] = min(dp[u][t], x.second + y.second);
			}
		}
	}

	if (u != 1) {
		g = dp[u]; 
		for (auto &x : g) {
			int t = x.first * x.first;
			if (dp[u].find(t) == dp[u].end())
				dp[u][t] = dp[u][x.first] + 1; 
			else dp[u][t] = min(dp[u][t], dp[u][x.first] + 1);
		}
	}
}

void kakuai() {
	cin >> n >> k; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	dfs(1, 0);

	int ans = 0; 

	for (auto &x : dp[1]) if (x.second <= k) maximize(ans, x.first * a[1] * x.second); 

	cout << ans; 
}

//_________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}