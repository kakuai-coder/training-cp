/*
Author: kakuai
created: 10.8.2025
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
int ssz(const T &a) {
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


void kakuai() {
	// voi26 = winner
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}

	int cur = 0;

	for (int i = 0; i < n; ++i) {
		if (a[i] > b[i]) cur += a[i] - b[i];
	}

	cout << cur + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry ""
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
