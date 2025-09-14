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

const int BLOCK = 500, MOD = 1e9 + 7, MAXN = 2e5 + 5; 

int sum[BLOCK][MAXN];

void kakuai(void) { 
	int n; 
	cin >> n; 

	vector<int> d(n + 2, 0), x(n + 2, 0);

	for (int i = 1; i <= n; ++i) {
		cin >> d[i] >> x[i];
	}

	vector<int> dp(n + 2, 1);

	for (int i = n; i; --i) {
		if (i + d[i] <= n && x[i] > 0 && d[i] > 0) {
			if (1LL * d[i] * d[i] > n) {
				for (int j = i + d[i]; j <= min<int64_t>(i + 1LL * d[i] * x[i], n); j += d[i]) {
					dp[i] += dp[j];
					dp[i] %= MOD;
				}
			} else {
				int lim = min(x[i], (n - i) / d[i]);

				int last = i + lim * d[i];

				if (last + d[i] > n) dp[i] += sum[d[i]][i + d[i]];
				else dp[i] += (sum[d[i]][i + d[i]] - sum[d[i]][last + d[i]] + MOD) % MOD;
				dp[i] %= MOD;
			}
		}

		for (int j = 1; j * j <= n; ++j) {
			if (i + j > n) sum[j][i] = dp[i];
			else sum[j][i] = sum[j][i + j] + dp[i];
			sum[j][i] %= MOD;
		}
	}

	cout << dp[1];	
	
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	fio("cuuho");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
