/*
	Author: Tinhnopro (Tinh nop)
	From: CHV Phu Tho
 */
#include<bits/stdc++.h>

namespace std {
	// optimize min max
	template<typename T1, typename T2> bool maximize(T1 &a, T2 b) { return a < b ? a = b, 1 : 0; }
	template<typename T1, typename T2> bool minimize(T1 &a, T2 b) { return a > b ? a = b, 1 : 0; }
	// vector
	template<typename T, int D> struct vec : public vector<vec<T, D - 1>> {
		static_assert(D >= 1, "Init error");
		template<typename... Args>
			vec(int n = 0, Args... args) : vector<vec<T, D - 1>>(n, vec<T, D - 1>(args...)) {}
	};
	template<typename T> struct vec<T, 1> : public vector<T> {
		vec(int n = 0, T val = T()) : vector<T>(n, val) {}
		template<typename InputIt>
			vec(InputIt first, InputIt last) : vector<T>(first, last) {}
	};
	// size
	template<typename T> int Size(const T &a) {  return a.size(); }
}
using namespace std;


void process(void) {
	int n, k; cin >> n >> k;
	vec<int, 2> a(k + 1, n + 1, 0), pos(k + 1, n + 1, 0);
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) cin >> a[i][j], pos[i][a[i][j]] = j;
	} 
	vector<int> dp(n + 1, 1);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			int x; 
			for (x = 2; x <= k && pos[x][a[1][j]] < pos[x][a[1][i]]; ++x);
			if (x == k + 1) maximize(dp[i], dp[j] + 1);
		}
		maximize(ans, dp[i]);
	}
	cout << ans << '\n';
}	

int32_t main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	#define name "463D"
	if (fopen(name".inp", "r")) {
		freopen(name".inp", "r", stdin);
		freopen(name".out", "w", stdout);
	}

	// int t; cin >> t; while (t--)
	process();

	cerr << "\nRuntime: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s. Code by Tinhnopro\n";
	return 0;
}
