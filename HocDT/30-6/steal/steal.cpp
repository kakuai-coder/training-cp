/*
	Author: kakuai
	created: 2025.06.30 15:38:01
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

vector<int> adj[maxN];
int s[maxN], a[maxN];
int n, k, ans;

void dfs1(int u, int par, int depth) {
	int flag = 0;
	
	for (int v : adj[u]) {
		if (v != par) {
			flag = 1;
			s[depth + 1] = v;
			dfs1(v, u, depth + 1);
		}
	}

	if (!flag) a[s[depth / 2 + depth % 2]] = 1;
}

void dfs2(int u, int par) {
	for (int v : adj[u]) {
		if (v != par) {
			if (a[v]) ++ans;
			else dfs2(v, u);
		}
	}
}

void kakuai() {
	cin >> n >> k;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1(k, 0, 0);
	dfs2(k, 0);
	cout << ans << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "steal"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}