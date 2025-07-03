/*
	Author: kakuai
	created: 2025.07.02 22:34:00
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
const int LOG = 16;

int n, q; 
vector<int> adj[maxN];
int depth[maxN], up[LOG + 1][maxN];
int timeIn[maxN], timeOut[maxN], timer = 0;

void dfs(int u, int par) {
	up[0][u] = par; 
	timeIn[u] = ++timer;

	for (int v : adj[u]) if (v != par) {
		depth[v] = depth[u] + 1; 
		dfs(v, u); 
	}

	timeOut[u] = timer; 
}

bool isAnc(int u, int v) {
	return timeIn[u] <= timeIn[v] && timeOut[u] >= timeOut[v];
}

void kakuai() {
	cin >> n >> q; 
	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 1);

	for (int u = 1; u <= n; ++u) {
		for (int i = 1; i <= LOG; ++i) up[i][u] = up[i - 1][up[i - 1][u]];
	}


	while (q--) {
		int u, v; 
		cin >> u >> v; 
		if (isAnc(u, v)) {
			int k = depth[v] - depth[u] - 1; 

			if (k == 0) {
				cout << v << '\n';
				continue;
			}

			for (int i = 0; i <= LOG; ++i) if ((k >> i) & 1) {
				v = up[i][v];
			}

			cout << v << '\n';
		} else {
			cout << up[0][u] << '\n';
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	// cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}