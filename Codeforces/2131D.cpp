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

	if (n == 1) {
		cout << 0 << '\n';
		return ;
	}

	vector<int> deg(n + 1, 0), d(n + 1, 0);
	vector<pair<int, int> > edges;

	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		deg[u]++;
		deg[v]++;
		edges.emplace_back(u, v);
	}

	int cnt = 0, mx = 0;

	for (int i = 1; i <= n; ++i) if (deg[i] == 1) {
		d[i] = 1;
		cnt++;
	}

	vector<int> adj(n + 1, 0);

	for (auto &e : edges) {
		int u = e.first;
		int v = e.second;
		if (d[u]) ++adj[v];
		if (d[v]) ++adj[u];
	}

	for (int i = 1; i <= n; ++i) {
		maximize(mx, adj[i] + d[i]);
	}

	int ans = cnt - mx;
	maximize(ans, 0);

	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "D"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}


	int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
