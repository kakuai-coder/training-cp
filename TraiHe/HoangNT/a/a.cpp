/*
	Author: tinhnopro
	created: 2025.06.17 09:54:04
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

const int maxN = 5e5 + 5, mod = (int) 1e9 + 7; 

int n, m, x, y; 
vector<vector<int>> a, reva;
int cnt[maxN];
set<int> S;

int get_min() {
	return (*S.begin());
}

void get_rect(int i) {
	for (int u = i; u <= i + x - 1; ++u) {
		for (int v = 1; v <= y; ++v) {
			cnt[a[u][v]]++;
			if (cnt[a[u][v]] == 1) S.erase(a[u][v]);
		}
	}
}

void remove(int i, int j) {
	for (int u = i; u <= i + x - 1; ++u) {
		cnt[a[u][j]]--;
		if (cnt[a[u][j]] == 0) S.insert(a[u][j]);
	}
}

void add(int i, int j) {
	for (int u = i; u <= i + x - 1; ++u) {
		cnt[a[u][j]]++;
		// debug(u, i, j, a[u][j], cnt[a[u][j]]);
		if (cnt[a[u][j]] == 1) S.erase(a[u][j]);
		// debug(S);
	}
}

void down(int i, int l, int r) {
	for (int u = l; u <= r; ++u) {
		cnt[a[i][u]]--; 
		if (cnt[a[i][u]] == 0) S.insert(a[i][u]);
		
		if (i + x > n) continue;
		
		cnt[a[i + x][u]]++;
		
		if (cnt[a[i + x][u]] == 1) S.erase(a[i + x][u]);
	}
}
 
void tinhnop() {
	cin >> n >> m >> x >> y;
	a.resize(n + 2, vector<int>(m + 2, 0));
	reva.resize(m + 2, vector<int>(n + 2, 0));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
			reva[j][i] = a[i][j];
		}
	}

	if (x < y) {
		swap(m, n);
		swap(x, y);
		a = reva; 
	}

	for (int i = 1; i <= m * n + 1; ++i) {
		S.insert(i);
	}


	i64 ans = 1;
	int d = 0; 

	get_rect(1);
	ans = (1LL * ans * get_min()) % mod;
	for (int i = 1; i <= n - x + 1; ++i) {
		if (d) {
			for (int j = m - 1; j >= y; --j) {
				remove(i, j + 1);
				add(i, j - y + 1);
				ans = (1LL * ans * get_min()) % mod;
			}
		} else {
			for (int j = 2; j <= m - y + 1; ++j) {
				int nxt_j = j + y - 1; 
				remove(i, j - 1);
				add(i, nxt_j);
				ans = (1LL * ans * get_min()) % mod; 
			}
		}
		
		if (i < n - x + 1) {
			if (d) down(i, 1, y);
			else down(i, m - y + 1, m);
			ans = (1LL * ans * get_min()) % mod;
		}
		
		d = d ^ 1; 
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}