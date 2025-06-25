/*
	Author: kakuai
	created: 2025.06.24 08:43:24
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

int n, m, a[maxN], b[maxN];

void kakuai() {
	cin >> n >> m; 
	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	for (int i = 1; i <= n; ++i) cin >> b[i]; 

	for (int i = 1; i <= m; ++i) {
		int x, y; 
		cin >> x >> y; 
		
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "pentime"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}