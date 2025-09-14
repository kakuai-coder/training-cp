/*
Author: kakuai
created: 9.8.2025
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

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

const int MaxN = 1e6 + 6;

int n, m;
vector<pair<int, int> > edges;
int lab[MaxN];

int find_root(int u) {
	return lab[u] < 0 ? u : lab[u] = find_root(lab[u]);
}

bool unite(int u, int v) {
	u = find_root(u);
	v = find_root(v);

	if (u == v) return false;

	if (lab[u] > lab[v]) swap(u, v);

	lab[u] += lab[v];

	lab[v] = u;

	return u;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		u++;
		v++;
		edges.emplace_back(u, v);
	}

	int cnt = 0, idx = 0;

	memset(lab, -1, sizeof(lab));

	for (auto &e : edges) {
		if (unite(e.first, e.second)) cnt++;
		idx++;

		if (cnt == n - 1) {
			cout << idx;
			return ;
		}

	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "g"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
