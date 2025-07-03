/*
	Author: kakuai
	created: 2025.07.02 14:27:42
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
int n, a[maxN]; 

void kakuai() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	int res = 0; 

	for (int i = 1; i <= n; ++i) {
		int mx = a[i], mx2 = a[i + 1]; 
		maximize(res, mx ^ mx2); 
		for (int j = i + 2; j <= n; ++j) {
			int tmp = mx; 
			maximize(mx, a[i]);
			if (mx == a[i]) {
				mx2 = tmp; 
			} else maximize(mx2, a[i]);

			maximize(res, mx ^ mx2);
		}
	}

	cout << res; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "xorsecond"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}