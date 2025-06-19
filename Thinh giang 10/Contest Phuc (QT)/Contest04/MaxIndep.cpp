/*
	Author: tinhnopro
	created: 31.03.2025 14:51:02
*/
#include <bits/stdc++.h>

#define CHERRY "MaxIndep"

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 

int n; 
vector<int> adj[maxN]; 
int dp[maxN][2]; 


void dfs(int u, int par) {
	dp[u][1] = 1; 

	for (int v : adj[u]) if (v != par) {
		dfs(v, u);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}

void solve() {
	cin >> n; 
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	dfs(1, 0); 

	cout << max(dp[1][1], dp[1][0]);

	return void(cout << '\n');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t;

	for (int i = 1; i <= t; ++i) {
		cerr << "Case #" << i << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}