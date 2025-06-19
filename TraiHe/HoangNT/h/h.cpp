/*
	Author: tinhnopro
	created: 2025.06.18 15:46:47
*/
#include <bits/stdc++.h>

#define int long long 

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL
#define int long long 

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e6 + 5; 
const int mod = 1e9 + 7; 

int n, m, p; 
vector<int> adj[maxN];
vector<int> topo, d;
int used[maxN]; 
int vist[maxN], topoId[maxN];
int dp[maxN];
vector<int> v;

void dfs(int u) {
	vist[u] = 1; 
	for (int v : adj[u]) if (!vist[v]) {
		dfs(v);
	}

	topo.push_back(u);
}

bool cmp(int &a, int &b) {
	return topoId[a] < topoId[b];
}

void tinhnop() {
	cin >> n >> m >> p; 
	for (int i = 1; i <= p; ++i) {
		int x; cin >> x; 
		used[x] = 1; 
	}

	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v; 
		adj[u].push_back(v); 
	}

	dfs(1); 
	reverse(topo.begin(), topo.end());

	for (int i = 0; i < ssize(topo); ++i) {
		topoId[topo[i]] = i + 1;  
	}
	
	d.push_back(1); 

	for (int i = 1; i <= n; ++i) if (used[i] == 1) d.push_back(i); 
	d.push_back(n);

	int ans = 1;

	for (int i = 1; i < d.size(); ++i) {
		int u = d[i - 1];
		int v = d[i]; 

		if (topoId[u] > topoId[v]) {
			cout << 0; 
			return ; 
		}

		dp[u] = 1; 

		for (int t = topoId[u]; t <= topoId[v]; ++t) {
			int x = topo[t - 1];
			if (dp[x] == 0) continue;

			for (int w : adj[x]) {
				if (topoId[w] <= topoId[v]) {
					dp[w] += dp[x]; 
					if (dp[w] >= mod) dp[w] -= mod; 
				}	
			}
		}

		
		int ways = dp[v]; 
		ans = 1LL * ans * ways % mod; 

		for (int t = topoId[u]; t <= topoId[v]; ++t) {
			dp[topo[t - 1]] = 0; 
		}

		if (ways == 0) {
			cout << 0; 
			return ;
		}
	}

	cout << ans; 
}	

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "h"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}