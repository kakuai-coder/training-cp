/*
Author: kakuai
created: 2.8.2025
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

const int maxN = 2e5 + 5;

int n, m, deg[maxN], order[maxN], ndeg[maxN];
bool vist[maxN];
vector<int> adj[maxN];

int lab[maxN];

void init() {
	for (int i = 1; i <= n; ++i) {
		lab[i] = -1;
	}
}

int findPar(int u) {
	return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
}

void unite(int u, int v) {
	u = findPar(u);
	v = findPar(v);

	if (u == v) return ;

	if (lab[u] > lab[v]) swap(u, v);

	lab[u] += lab[v];
	lab[v] = u;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}

	set<array<int, 2> > s;

	for (int i = 1; i <= n; ++i) {
		s.insert({deg[i], i});
	}

	int q = n, cnt = 1;

	while (q--) {
		auto top = *s.begin();
		int u = top[1];
		int degu = top[0];

		order[cnt] = u;
		ndeg[cnt] = degu;
		++cnt;
		vist[u] = 1;
		for (int v : adj[u]) if (!vist[v]) {
			s.erase({deg[v], v});
			deg[v]--;
			s.insert({deg[v], v});
		}

		s.erase({deg[u], u});
	}

	int64_t ans = 0;
	int mx = 1;

	memset(vist, 0, sizeof(vist));
	init();

	for (int i = n; i >= 1; --i) {
		int u = order[i];

		vist[u] = 1;

		for (int v : adj[u]) if (vist[v]) {
			unite(u, v);
			maximize(mx, -lab[findPar(u)]);
		}

		maximize(ans, 1LL * mx * ndeg[i]);
	}

	cout << ans;

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "b"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
