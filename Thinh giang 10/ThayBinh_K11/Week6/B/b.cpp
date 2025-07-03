/*
	Author: kakuai
	created: 2025.07.01 13:49:36
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

const int maxN = 5e5 + 5; 

int n, a[maxN], in_deg[maxN], vist[maxN];
int cnt = 0; 

void dfs(int u, bool ok) {
	if (vist[u]) return ; 
	vist[u] = 1; 

	if (ok) cnt++;
 
	int v = a[u]; 

	in_deg[v]--;

	if (in_deg[v] == 0 || ok) {
		dfs(v, !ok);
	}

}

void kakuai() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		in_deg[a[i]]++;
	}

	for (int i = 1; i <= n; ++i) if (in_deg[i] == 0) dfs(i, 1);

	for (int i = 1; i <= n; ++i) dfs(i, 0); 

	cout << cnt; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}