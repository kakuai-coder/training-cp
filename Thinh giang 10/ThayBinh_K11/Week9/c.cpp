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

const int Mod = 1e9 + 7;
const int maxN = 5e5 + 5;

int n, m;
vector<array<int, 3> > edges;

int lab[maxN];

void init() {
	for (int i = 1; i <= n; ++i) {
		lab[i] = -1;
	}
}

int findPar(int u) {
	return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
}

bool unite(int u, int v) {
	u = findPar(u);
	v = findPar(v);

	if (u == v) return false;

	if (lab[u] > lab[v]) swap(u, v);

	lab[u] += lab[v];
	lab[v] = u;

	return true;
}


void kakuai(void) {
	// voi26 = winner
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({w, u, v});
	}

	sort(edges.begin(), edges.end());

	init();

	int64_t W = 0;
	int64_t cnt = 1;

	for (int i = 0; i < m; ) {
		int j;
		int num = 0, tot = 0;

		set<pair<int, int> > s;
		for (j = i; j < m && edges[i][0] == edges[j][0]; ++j) {
			int u = findPar(edges[j][1]);
			int v = findPar(edges[j][2]);

			if (u > v) swap(u, v);

			if (u != v) {
				s.insert({u, v});
				++tot;
			}
		}

		for(; i < j; i++) {
		  num += unite(edges[i][1], edges[i][2]);
		}

		W += 1LL * num * edges[i - 1][0];

		if(tot == 3) {
		  if(num == 1 || num == 2 && s.size() == 3) cnt = (cnt * 3) % Mod;
		  if(num == 2 && s.size() == 2) cnt = (cnt * 2) % Mod;
		}
		if(tot == 2 && num == 1) cnt = (cnt * 2) % Mod;
	}

	cout << W << ' ' << cnt << '\n';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "c"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
