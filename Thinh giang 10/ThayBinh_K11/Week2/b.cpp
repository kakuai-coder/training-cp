/*
	Author: tinhnopro
	created: 2025.04.13 14:25:46
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

const int maxN = 1e5 + 5; 
const int maxA = 1e6 + 6; 

int n, x, cnt[maxA];
i64 a[maxN]; 
vector<int> divs; 

void tinhnop() {
	cin >> n >> x; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		a[i] += a[i - 1];
	}

	divs.clear();

	for (int i = 1; i <= n; ++i) {
		if (x % i == 0) {
			divs.push_back(i);
		}
	}

	i64 res = 0;

	for (int sz : divs) {
		int k = x / sz; 
		for (int i = sz; i <= n; ++i) {
			if (a[i] - a[i - sz] <= k) {
				cnt[a[i] - a[i - sz]]++; 
			} 
		}

		for (int i = sz; i <= n; ++i) {
			if (a[i] - a[i - sz] <= k) {
				res += cnt[k - a[i] + a[i - sz]];
			} 
		}

		for (int i = sz; i <= n; ++i) {
			if (a[i] - a[i - sz] <= x / sz) {
				cnt[a[i] - a[i - sz]] = 0; 
			} 
		}
	}

	cout << res << '\n'; 
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

	int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}