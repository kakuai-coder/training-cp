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

const int MAXN = 5e5 + 5; 
int t, n, a[MAXN], cnt[MAXN];

bool check(int len, int& ansL, int& ansR) {
	int bad = 0; 

	for (int i = 0; i <= t; ++i) cnt[i] = 0;

	for (int i = len + 1; i <= n; ++i) {
		cnt[a[i]]++;
		if (cnt[a[i]] == 2) bad++;  
	}

	if (bad == 0) {
		ansL = 1; 
		ansR = len;
		return true;
	}

	for (int i = 2; i <= n - len + 1; ++i) {
		int j = i + len - 1;
		
		cnt[a[i - 1]]++;
		if (cnt[a[i - 1]] == 2) bad++;

		cnt[a[j]]--;
		if (cnt[a[j]] == 1) bad--;
		
		if (bad == 0) {
			ansL = i, ansR = j;
			return true;
		}
	}

	return false; 
}

void kakuai(void) { 
	cin >> t >> n;
	
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	int lo = 0, hi = n + 1;
	int bestL = -1, bestR = -1;

	while (hi - lo > 1) {
		int mid = (lo + hi) >> 1;
		if (check(mid, bestL, bestR)) hi = mid; 
		else lo = mid; 
	}

	cout << bestL - 1 << ' ' << bestR - 1; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
