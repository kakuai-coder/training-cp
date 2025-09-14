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
// > kakuai < <cherry> >> 27.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5; 

int n, q, cnt[MAXN], a[MAXN];

void kakuai(void) { 
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) cin >> a[i]; 

	while (q--) {
		int l, r; 
		cin >> l >> r; 
		cnt[l]++; 
		cnt[r + 1]--; 
	}

	for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];

	sort(a + 1, a + n + 1); 
	sort(cnt + 1, cnt + n + 1); 

	int64_t ans = 0; 

	for (int i = 1; i <= n; ++i) ans += 1LL * a[i] * cnt[i];

	cout << ans; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	fio("maxsum");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
