/*
Author: kakuai
created: 31.7.2025
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


void kakuai(void) {
	// voi26 = winner
	string s;
	cin >> s;

	int n = size32(s);
	s = ' ' + s;

	vector<int> z(n + 1, 0);

	for (int i = 2, l = 1,r = 1; i <= n; ++i) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i - l + 1]);
		}

		while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;

		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}

	vector<int> ans;

	for (int i = 1; i < n; ++i) if (i + z[i + 1] == n) ans.push_back(i);

	ans.push_back(n);

	for (int &x : ans) cout << x << ' ';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "i"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
