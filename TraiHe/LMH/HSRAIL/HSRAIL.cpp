/*
	Author: kakuai
	created: 2025.06.24 08:28:07
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

void kakuai() {
	int n; 
	cin >> n; 
	vector<int> a(n + 1), l(n + 1, 0), r(n + 2, 0); 
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	for (int i = 1; i <= n; ++i) l[i] = max(a[i], l[i - 1] - 1);

	for (int i = n; i >= 1; --i) r[i] = max(a[i], r[i + 1] - 1); 

	int ans = 0;

	for (int i = 1; i <= n; ++i) {
		int h = max(l[i], r[i]); 

		ans += abs(h - a[i]);
	}

	cout << ans << '\n'; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "HSRAIL"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}