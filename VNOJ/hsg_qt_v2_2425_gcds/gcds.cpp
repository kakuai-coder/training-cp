/*
Author: kakuai
created: 1.8.2025
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

const int maxN = 5e5 + 5;
const int Mod = 1e9 + 7;
const int CMod = 100;

int n, q, a[maxN];
vector<pair<int, int> > divs[maxN];
int sumdiv[maxN];
int64_t ans = 0;

int Get(int x) {
	int64_t res = 0;
	int cnt = 0;
	for (auto &d : divs[x]) {
		res += (1LL * d.second * sumdiv[d.first]) % Mod;
		++cnt;
		if (cnt == CMod) {
			cnt = 0;
			if (res >= Mod) res -= Mod;
		}
	}

	res %= Mod;

	return res;
}

void add(int x) {
	ans += Get(x);
	if (ans >= Mod) ans -= Mod;

	for (auto &d : divs[x]) {
		sumdiv[d.first] += d.second;
		if (sumdiv[d.first] >= Mod) sumdiv[d.first] -= Mod;
	}
}

void Replace(int x, int y) {

	for (auto &d : divs[a[x]]) {
		sumdiv[d.first] -= d.second;
		if (sumdiv[d.first] < 0) sumdiv[d.first] += Mod;
	}

	ans -= Get(a[x]);
	if (ans < 0) {
		ans += Mod;
	}

	a[x] = y;
	add(a[x]);
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> q;

	for (int i = 1; i < maxN; ++i) {
		for (int j = i; j < maxN; j += i) divs[j].emplace_back(i, j / i);
	}


	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		add(a[i]);
	}


	cout << ans << '\n';


	while (q--) {
		int x, y;
		cin >> x >> y;
		Replace(x, y);

		cout << ans << '\n';
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "gcds"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
