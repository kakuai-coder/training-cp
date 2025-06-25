/*
	Author: kakuai
	created: 2025.06.22 21:54:31
*/
#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e5 + 5; 
const int maxK = 1e3 + 5; 
const int inf = 1e9 + 11; 

int n, k;
vector<int> adj[maxN]; 
int dp[maxN][maxK], sz[maxN], w[maxN];

void dfs(int u, int par) {
	for (int i = 0; i <= k; ++i) dp[u][i] = -inf;
	dp[u][0] = 0; 
	sz[u] = 1; 
	
	for (int v : adj[u]) if (v != par) {
		dfs(v, u); 
		
		for (int cntu = sz[u]; ~cntu; --cntu) {
			for (int cntv = 0; cntv <= sz[v]; ++cntv) {
				if (cntu + cntv > k) continue;
				
				dp[u][cntu + cntv] = max(dp[u][cntu + cntv], dp[u][cntu] + dp[v][cntv]);
			}
		}
		
		sz[u] += sz[v]; 
		sz[u] = min(sz[u], k);
	}
	dp[u][1] = max(dp[u][1], w[u]);
}

int root;

void kakuai() { 
	cin >> n >> k; 

	root = -1; 
	
	for (int i = 1, par; i <= n; ++i) {
		cin >> par >> w[i];
		
		if (par == 0) root = i; 
		else {
			adj[par].push_back(i); 
			adj[i].push_back(par);
		}
	}
	
	dfs(root, 0);
	
	cout << max(0, dp[root][k]) << '\n';
	for (int i = 1; i <= n; ++i) adj[i].clear();
}

//_____________________________________________________________________________________________
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();
}