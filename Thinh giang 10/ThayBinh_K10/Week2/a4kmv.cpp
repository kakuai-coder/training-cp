/*
	Author: tinhnopro
	created: 2025.04.09 08:57:00
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

#define ci const int 

const int N = 2e5 + 5;
const int LOG = log2(N);

int n, m;
vector < int > E[N];
int d[N], p[LOG + 1][N];

int a[N];

void dfs(ci &u, ci &par){
	d[u] = d[par] + 1;
	p[0][u] = par;

	for (int i : E[u])
		if (i != par){
			dfs(i, u);
		}
}

void build(){
	dfs(1, 0);

	for (int i = 1; i <= LOG; i ++)
		for (int j = 1; j <= n; j ++)
			p[i][j] = p[i - 1][p[i - 1][j]];
}

int lca(int &u, int &v){
	if (d[u] < d[v])
		swap(u, v);
	
	for (int i = LOG; i >= 0; i --)
		if (d[p[i][u]] >= d[v])
			u = p[i][u];
		
	if (u == v)
		return u;
	
	for (int i = LOG; i >= 0; i --){
		if (p[i][u] != p[i][v]){
			u = p[i][u];
			v = p[i][v];
		}
	}

	return p[0][u];
}

void dfs2(ci &u, ci &par){

	for (int i : E[u])
		if (i != par){
			dfs2(i, u);
			a[u] += a[i];
		}

}

void tinhnop() {
		cin >> n;

		int u, v;
		for (int i = 1; i < n; i ++){
			cin >> u >> v;
			E[u].push_back(v);
			E[v].push_back(u);
		}

		build();

		cin >> m;

		for (int i = 1; i <= m; i ++){
			cin >> u >> v;
			
			a[u] ++;
			a[v] ++;
			int l = lca(u, v);
			a[l] --;
			a[p[0][l]] --;
		}

		dfs2(1, 0);

		int cnt = 0;

		for (int i = 1; i <= n; i++)
			if (!a[i])
				cnt ++;
			
		cout << cnt;
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a4"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}