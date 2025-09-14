#include <bits/stdc++.h>

using namespace std;

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int ssiz(const T &a) {
	return int(a.size());
}

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
	static_assert(D >= 1, "Error");
	template <typename... Args>
	Vec(int n = 0, Args... args)
		: vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};
template <typename T>
struct Vec<T, 1> : public vector<T> {
	Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 29.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int64_t INF = (int64_t)1e18 + 11; 

void kakuai(void) { 
	int n; 
	cin >> n; 

	vector<int> a(n + 2, 0); 
	vector< vector<int64_t> > dp(n + 2, vector<int64_t>(3, -INF));

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	dp[0][0] = 0;
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			maxim(dp[i][j], dp[i - 1][j]);
			if (j != 2) maxim(dp[i][j], dp[i - 1][j + 1] + a[i]);
			if (j != 0) maxim(dp[i][j], dp[i - 1][j - 1] - a[i]);
		}
	}

	int64_t ans = -INF;

	for (int j = 0; j < 3; ++j) maxim(ans, dp[n][j]);

	cout << ans; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	fio("cuutro");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
