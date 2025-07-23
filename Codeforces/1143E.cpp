/*
Author: kakuai
created: 2025.07.16
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int size32(const T &a) {
	return (int)a.size();
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
}  // namespace std

const int maxN = 2e5 + 5, Log = 20; 

int n, m, q, a[maxN], b[maxN], nxtpos[maxN], nxt[maxN], pos[maxN];
int jump[Log + 1][maxN], min_jump[Log + 1][maxN];

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m >> q; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	for (int i = 1; i <= m; ++i) {
		cin >> b[i];
	}
	
	for (int i = 1; i < n; ++i) {
		nxtpos[a[i]] = a[i + 1];
	}

	nxtpos[a[n]] = a[1];


	for (int i = m; i >= 1; --i) {
		int idx = nxtpos[b[i]]; 
		nxt[i] = (pos[idx] == 0 ? m + 1 : pos[idx]);

		pos[b[i]] = i; 
	}

	for (int i = 1; i <= m; ++i) jump[0][i] = nxt[i]; 
	jump[0][m + 1] = m + 1; 

	for (int j = 1; j <= Log; ++j) {
		for (int i = 1; i <= m; ++i) {
			jump[j][i] = jump[j - 1][jump[j - 1][i]];
		}
	}

	for (int i = 1; i <= m; ++i) {
		int k = n - 1; 
		int idx = i; 

		for (int j = 0; j <= Log; ++j) if ((k >> j) & 1) {
			idx = jump[j][idx];
		}
		if (idx == 0) idx = m + 1; 

		min_jump[0][i] = idx; 
	}

	for (int j = 1; j <= Log; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= m; ++i) {
			min_jump[j][i] = min(min_jump[j - 1][i], min_jump[j - 1][i + (1 << (j - 1))]);
		}
	}

	while (q--) {
		int l, r; 
		cin >> l >> r; 

		if (r - l + 1 < n) {
			cout << 0; 
			continue;
		}

		int id  = r - n + 1; 

		int k = __lg(id - l + 1); 

		int cur = min(min_jump[k][l], min_jump[k][id - (1 << k) + 1]);

		// cerr << cur << '\n';

		cout << (cur <= r);
	}
	
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry ""
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}