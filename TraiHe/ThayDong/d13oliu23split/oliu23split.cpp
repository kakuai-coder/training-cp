/*
	Author: tinhnopro
	created: 2025.06.15 08:18:32
*/
#include <bits/stdc++.h>

using namespace std;


const int maxN = 1e6 + 5; 

int n, w[maxN], k, par[maxN];
int dp[maxN];
long long a[maxN];
vector<int> adj[maxN]; 
int topo[maxN];
int cnt = 0; 

void dfs_pre(int u, int p) {
	par[u] = p; 

	for (int v : adj[u]) if (v != p) {
		dfs_pre(v, u);
	}

	
	topo[cnt] = u; 
	cnt++;
}

void tinhnop() {
	cin >> n >> k; 
	for (int i = 1; i <= n; ++i) {
		cin >> w[i]; 
	}

	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u); 
	}

	long long  sumw = 0; 
	for (int i = 1; i <= n; ++i) sumw += w[i];

	dfs_pre(1, 0);

	long long l = 0, r = sumw / k + 1;
	
	bool ok;

	while (r - l > 1) {
		long long mid = (l + r) / 2; 
		for (int i = 1; i <= n; ++i) {
			dp[i] = 0; 
			a[i] = w[i];
		}

		ok = false;

		for (int i = 0, u; i < cnt; ++i) {
			u = topo[i]; 
			if (a[u] >= mid) {
				dp[u]++;
				a[u] = 0;
			}

			if (dp[u] >= k) {
				ok = true; 
				break;
			}

			dp[par[u]] += dp[u]; 
			a[par[u]] += a[u];
		}

		if (dp[1] >= k) ok = true; 

		if (ok) l = mid;
		else r = mid; 
	}


	cout << l; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();
	return 0;
}
