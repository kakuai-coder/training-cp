/*
	Author: tinhnopro
	created: 2025.06.14 22:21:34
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

#define MASK(i) (1LL << (i))
#define ONBIT(n , i) (n | MASK(i))
#define OFFBIT(n , i) (n ^ MASK(i))
#define BIT(n , i) ((n >> (i)) & 1LL)
#define LOG2(n) (63 - __builtin_clzll(n))
#define CNTBIT(n) __builtin_popcountll(n)

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 105; 

int n, m; 
vector<int> a[maxN];
int used[maxN];

vector<int> adj[maxN];
int vist[maxN], d[maxN];

int ans = 0; 
bool cyc = false;

void dfs(int x) {
	vist[x] = 1; 
	for (int v : adj[x]) if (!vist[v]) {
		dfs(v);
	} else if (vist[v] == 1) cyc = true; 

	vist[x] = 2;
}

int calc(int x) {
	if (~d[x]) return d[x]; 

	int cur = 0; 

	for (int v : adj[x]) {
		maximize(cur, calc(v) + 1);
	}

	maximize(ans, cur);

	return d[x] = cur;  
}

namespace sub2 {
	int k[20];
	int job[20];
	const int INF = 1e9 + 829;
	int dp[MASK(20) + 5];
	int x;
	
	void solve() {
		for(int i = 0 ; i < n ; i ++){
			cin >> k[i];
			int bit = 0;
			for(int j = 1 ; j <= k[i] ; j ++){
				cin >> x;
				bit = ONBIT(bit , x - 1);
			}
			job[i] = bit;
		}

		for(int mask = 0 ; mask < MASK(n) ; mask ++){
			dp[mask] = INF;
		}

		dp[0] = 0;

		for(int mask = 0 ; mask < MASK(n) ; mask ++){
			if (dp[mask] == INF) continue;
			int can = 0;
			for(int i = 0 ; i < n ; i ++){
				if (! BIT(mask , i)){
					if ((mask & job[i]) == job[i]){
						can = ONBIT(can , i);
					}
				}
			}
			if (can != 0){
				if (CNTBIT(can) <= m){
					dp[mask | can] = min(dp[mask | can] , dp[mask] + 1);
				} else {
					for(int submask = can ; submask ; submask = (submask - 1) & can){
						if (CNTBIT(submask) == m){
							dp[mask | submask] = min(dp[mask | submask] , dp[mask] + 1);
						}
					}
				}
			}	
		}
		if (dp[MASK(n) - 1] == INF) cout << -1;
		else cout << dp[MASK(n) - 1];
	}
}

void tinhnop() {
	cin >> n >> m; 
	
	if (n > m){
		sub2::solve();
		return ;
	}

	for (int i = 1; i <= n; ++i) {
		int k; 
		cin >> k;  
		for (int j = 1; j <= k; ++j) {
			int x; cin >> x; 
			a[i].push_back(x);
			adj[x].push_back(i); 
		}
	}
	
	for (int i = 1; i <= n; ++i) if (!vist[i]) {
		dfs(i);
	}

	if (cyc) {
		cout << -1;
		return ; 
	}
		memset(d, -1, sizeof(d));

	for (int i = 1; i <= n; ++i) if (a[i].empty()) calc(i); 

	cout << ans + 1; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "jobshop"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}