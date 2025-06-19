// tinhnopro 
#include <bits/stdc++.h>
using namespace std; 

#define hanh "Cave"

using i64 = long long;

const int mod = 1e9 + 7;
const int maxN = 1008; 
const int mx = 1e6 + 5; 

int n, m; 
char a[maxN][maxN];

int add(int a, int b) {
	a += b; 
	if (a >= mod) a -= mod; 
	return a; 
}

int mul(int a, int b) {
	i64 x = 1LL * a * b; 
	return x % mod; 
}

struct DSU {
	int lab[mx]; 

	void init() {
		memset(lab, -1, sizeof(lab));
	}

	int find_par(int u) {
		return lab[u] < 0 ? u : lab[u] = find_par(lab[u]);
	}

	void join(int u, int v) {
		u = find_par(u); 
		v = find_par(v);

		if (u == v) return ; 

		if (lab[u] > lab[v]) swap(u, v); 

		lab[u] += lab[v]; 

		lab[v] = u; 
	}
} dsu;

namespace Sub2 {

	bool ok(int i, int j) {
		return a[i][j] == '.';
	}

	int nodeId[maxN][maxN], dp[mx], par[mx];
	vector<int> adj[mx];

	void dfs(int u) {
		dp[u] = 1; 
		for (int v : adj[u]) {
			dfs(v); 
			dp[u] = mul(dp[u], add(dp[v], 1));
		}
	}

	void Main() {
		dsu.init();
		int numNode = 1; 
		for (int i = n - 1; i > 1; --i) {
			queue<int> q; 

			for (int j = 2; j < m; ++j) {
				if (ok(i, j) && ok(i + 1, j)) {
					nodeId[i][j] = nodeId[i + 1][j];
					q.push(j);
				}
			}

			while (!q.empty()) {
				int u = q.front(); 
				q.pop(); 

				for (int id : {-1, 1}) {
					int v = u + id; 
					
					if (ok(i, v) && nodeId[i][v] == 0) {
						nodeId[i][v] = nodeId[i][u]; 
						q.push(v); 
					}
				}
			}

			for (int j = 2; j < m; ++j) {
				if (ok(i, j) && ok(i, j + 1) && nodeId[i][j] != 0 && nodeId[i][j + 1] != 0) {
					dsu.join(nodeId[i][j], nodeId[i][j + 1]);
				}
			}

			for (int j = 2; j < m; ++j) {
				if (ok(i, j) && nodeId[i][j] != 0) {
					int u = dsu.find_par(nodeId[i][j]);

					if (par[u] == 0) {
						par[u] = numNode;
						numNode++; 
					} 

					par[nodeId[i][j]] = par[u]; 
					nodeId[i][j] = par[u]; 
				}
			}

			for (int j = 2; j < m; ++j) {
				if (ok(i, j) && nodeId[i][j] == 0) {
					nodeId[i][j] = numNode; 
					if (!ok(i, j + 1)) numNode++; 
				}
			}
		}

		numNode--; 

		for (int i = 1; i <= numNode; ++i) {
			if (par[i] != 0) adj[par[i]].push_back(i);
		}

		int res = 1; 

		for (int i = 1; i <= numNode; ++i) {
			if (par[i] == 0) {
				dfs(i); 
				res = mul(res, add(dp[i], 1));
			}
		}

		cout << res; 
	}	

	bool run() {

		return Main(), true;
	}
}



void Input() {
	cin >> n >> m; 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j]; 
		}
	}
}

void Main() {
	Sub2::run();
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 
	
	if (fopen(hanh".inp", "r")) {
		freopen(hanh".inp", "r", stdin); 
		freopen(hanh".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t; 
	for (int i = 1; i <= t; ++i) {
		Input();
		Main();
	}

	cerr << "\n[runtime]" << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";
	return 0; 
}