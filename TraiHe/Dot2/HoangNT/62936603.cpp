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
// > kakuai < <cherry> >> 19.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 2e6 + 5; 
int n, a[MAXN], b[MAXN];

bool check(int64_t x) {
	int i = 1, j = 1; 
	while (i <= n) {
		int64_t power = x; 
		j = i; 

		while (j < n + i && power >= a[j]) {
			power += b[j];
			++j;
		}

		if (j >= i + n) return true;
		i = j + 1;
	}

	return false;
}

void kakuai(void) { 
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];

		a[i + n] = a[i];
	}

	for (int i = 1; i <= n; ++i) {
		cin >> b[i];

		b[i + n] = b[i];
	}

	int64_t lo = -1, hi = 1e15 + 11; 

	while (hi - lo > 1) {
		int64_t mid = (hi + lo) >> 1LL; 

		if (check(mid)) hi = mid; 
		else lo = mid;
	}

	cout << hi; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
