/*
	Author: kakuai
	created: 2025.07.08 16:20:08
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

int n, a[maxN], b[maxN]; 
vector<int> adj[maxN];
i64 dp[2][maxN]; 

void dfs(int u, int par) {
	i64 sum1 = 0, cnt = 0; 
	vector<i64> d;

	for (int v : adj[u]) if (v != par) {
		dfs(v, u); 
		sum1 += dp[1][v];
		d.push_back(dp[0][v] - dp[1][v]);
		++cnt; 
	}

	sort(d.begin(), d.end());

	i64 cur = a[u] + sum1;

	if (b[u] <= cnt) {
		i64 sum = 0, cur0 = (i64) 1e18 + 11; 

		for (int i = 0; i < b[u]; ++i) sum += d[i];
		
		for (int i = b[u]; i < cnt; ++i) {
			minimize(cur0, sum1 + sum);
			sum += d[i];	
		}
		minimize(cur0, sum1 + sum);

		minimize(cur, cur0);
		// cerr << 0 << u << ' ' << cur << ' ' << cur0 << '\n';
	}
	
	dp[0][u] = cur;
	
	
	cur = a[u] + sum1; 
	
	int need = max(0, b[u] - 1); 
	
	if (need <= cnt) {
		i64 sum = 0, cur1 = (i64) 1e18 + 11; 
		
		for (int i = 0; i < need; ++i) sum += d[i]; 
		
		for (int i = need; i < cnt; ++i) {
			minimize(cur1, sum1 + sum);
			sum += d[i];
		}

		minimize(cur1, sum1 + sum);
		
		minimize(cur, cur1);
		// cerr << 1 << u << ' ' << cur << ' ' << cur1 << '\n';
	}
	
	dp[1][u] = cur;
}

void kakuai() {
	cin >> n; 
	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
	}

	dfs(1, 0); 

	cout << dp[0][1];
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "rtree5"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}