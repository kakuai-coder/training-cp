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

const int INF = 1e18 + 11; 
vector<int> a; 
int n;

int get(int i, int k) {
	return k == 0 ? a[i] : a[n - i + 1];
}

void process(void) {
	cin >> n;
	a.clear();
	a.resize(n + 2);
	for (int i = 1; i <= n; ++i) cin >> a[i];

	vec<int, 2> dp(n + 2, 2, INF);

	dp[1][0] = dp[1][1] = 0; 
	for (int i = 2; i <= (n + 1) / 2; ++i) {
		for (int j : {0, 1}) {
			for (int j2 : {0, 1}) {
				minimize(dp[i][j], dp[i - 1][j2] + 
					(get(i, j) == get(i - 1, j2)) + (get(i, j ^ 1) == get(i - 1, j2 ^ 1)));
			}
		}
	}

	int ans = min(dp[(n + 1) / 2][0], dp[(n + 1) / 2][1]);

	if(!(n & 1)) {
		ans += a[n / 2] == a[(n / 2) + 1];
	}

	cout << ans << '\n';
}

int32_t main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	#define name "d"
	if (fopen(name".inp", "r")) {
		freopen(name".inp", "r", stdin);
		freopen(name".out", "w", stdout);
	}

	int t; cin >> t; while (t--)
	process();

	cerr << "\nRuntime: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s. Code by Tinhnopro\n";
	return 0;
}
