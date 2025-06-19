/*
	Author: tinhnopro
	created: 2025.06.17 14:05:08
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

const int maxN = 2e5 + 5; 

int n, a[maxN];
int pos[maxN], sum[maxN];

i64 res = 0;

void calc(int x) {
	for (int i = pos[x]; i <= n; ++i) if (sum[i] == sum[pos[x] - 1]) {
		res++;
	} 
}

void tinhnop() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		pos[a[i]] = i;  
	}

	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1];
		if (a[i] == 1) continue;
		sum[i]++;
	}

	calc(1);


	for (int d = 2; d <= n; d++) {
		for (int i = pos[d - 1]; i <= n; ++i) sum[i]--;
		for (int i = pos[d]; i <= n; ++i) sum[i]--;

		calc(d);
	}

	cout << res; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}