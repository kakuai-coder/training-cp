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
// > kakuai < <cherry> >> 20.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 3e5 + 5;
const int64_t INF = (int64_t)1e18 + 11; 

int n, k, a[MAXN]; 
int64_t pref[MAXN], min_pref[MAXN], min_suff[MAXN], sum[MAXN], max_sumpref[MAXN], max_sumsuff[MAXN];

void kakuai(void) { 
	cin >> n >> k; 
	
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		pref[i] = pref[i - 1] + a[i];

	}

	if (k == 2) {
		int64_t ans = 0; 

		for (int i = 1; i < n; ++i) {
			int64_t Left = pref[i];
			int64_t Right = pref[n] - pref[i];

			maxim(ans, llabs(Right - Left));
		}

		cout << ans << '\n'; 
		return ;
	}

	int len = n - k + 1; 

	min_pref[0] = INF; 

	for (int i = 1; i <= n; ++i) 
		min_pref[i] = min<int64_t>(min_pref[i - 1], a[i]);

	min_suff[n + 1] = INF; 

	for (int i = n; i; --i) 
		min_suff[i] = min<int64_t>(min_suff[i + 1], a[i]);

	for (int i = 1; i <= n - len + 1; ++i) {
		sum[i] = pref[i + len - 1] - pref[i - 1];
		max_sumpref[i] = max(max_sumpref[i - 1], sum[i]);
	}

	for (int i = n - len + 1; i >= 1; --i)
		max_sumsuff[i] = max(max_sumsuff[i + 1], sum[i]);

	int64_t ans = 0; 

	for (int cut = 1; cut < n; ++cut) {
		int64_t bestL = 0, bestR = 0; 

		if (cut < len) bestL = pref[cut];
		else bestL = max_sumpref[cut - len + 1];

		if (cut > n - len) bestR = pref[n] - pref[cut];
		else bestR = max_sumsuff[cut + 1];

		int minR = min_suff[cut + 1]; 
		int minL = min_pref[cut]; 

		maxim(ans, llabs(bestL - minR));
		maxim(ans, llabs(bestR - minL));
	}

	cout << ans; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
