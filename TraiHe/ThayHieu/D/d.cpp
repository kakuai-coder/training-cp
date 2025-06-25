/*
	Author: kakuai
	created: 2025.06.22 14:42:37
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

int n, m, c[maxN], l[maxN], len[maxN], sum[maxN]; 

vector<int> adj[maxN];
priority_queue<int> pq[maxN];

void dfs(int u, int par = -1) {
	sum[u] = c[u]; 
	pq[u].push(c[u]);
	for (int v : adj[u]) if (v != par) {
		dfs(v, u); 

		if (pq[u].size() < pq[v].size()) {
			swap(pq[u], pq[v]);
			swap(sum[u], sum[v]);
		}

		while (pq[v].size()) {
			int val = pq[v].top(); 
			sum[u] += val; 
			pq[u].push(val);
			pq[v].pop();
		}

		while (sum[u] > m) {
			int val = pq[u].top(); 
			sum[u] -= val; 
			pq[u].pop();
		}
	}

	len[u] = pq[u].size(); 
}

void kakuai() {
	cin >> n >> m;

	int root = -1; 

	for (int i = 1; i <= n; ++i) {
		int b; 
		cin >> b >> c[i] >> l[i];
		
		if (b == 0) root = i; 
		else {
			adj[b].push_back(i); 
			adj[i].push_back(b); 
		}
	}

	dfs(root); 

	i64 ans = 0; 

	for (int i = 1; i <= n; ++i) maximize(ans, 1LL * len[i] * l[i]); 

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