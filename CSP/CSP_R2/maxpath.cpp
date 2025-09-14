/*
Author: kakuai
created: 30.7.2025
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

#define int long long

const int maxN = 1e5 + 5;

struct edge_t {
	int u, v, w;

	edge_t(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
};

int n, m;
vector<pair<int, int> > adj[maxN];
edge_t edges[maxN];

bool cmp(const edge_t &a, const edge_t &b) {
	return a.w > b.w;
}

int lab[maxN], spf[maxN];
int64_t ans[maxN], c[maxN];
unordered_map<int, int> cnt[maxN];
vector<int> me[maxN], f[maxN];


void init() {
	for (int i = 1; i <= n; ++i) {
		lab[i] = -1;
		ans[i] = c[i] = 0;
		me[i].push_back(i);

		for (int mask = 1; mask < (1 << size32(f[i])); ++mask) {
			int S = 1;
			for (int m = 0; m < size32(f[i]); ++m) if ((mask >> m) & 1) {
				S *= f[i][m];
			}

			cnt[i][S]++;
		}
	}
}

int findPar(int u) {
	return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
}

bool unite(int u, int v, int w) {
	u = findPar(u);
	v = findPar(v);

	if (u == v) return false;

	if (lab[u] > lab[v]) swap(u, v);

	lab[u] += lab[v];
	lab[v] = u;

	ans[u] += ans[v];
	c[u] += c[v];

	for (int &x : me[v]) {
		int s = size32(me[u]);
		int sz = size32(f[x]);

		for (int mask = 1; mask < (1 << sz); ++mask) {
			int c_bit = __builtin_popcount(mask);

			if (c_bit & 1) {
				int S = 1;
				for (int m = 0; m < sz; ++m) if ((mask >> m) & 1) {
					S *= f[x][m];
				}
				s -= cnt[u][S];
			} else {
				int S = 1;
				for (int m = 0; m < sz; ++m) if ((mask >> m) & 1) {
					S *= f[x][m];
				}

				s += cnt[u][S];
			}
		}

		ans[u] += 1LL * s * w;
		c[u] += s;
	}

	for (int &x : me[v]) me[u].push_back(x);
	for (auto &x : cnt[v]) cnt[u][x.first] += x.second;

	return true;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m;

	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].push_back({v, w});
		adj[v].push_back({u, w});

		edges[i] = edge_t(u, v, w);
	}

	for (int i = 2; i <= n; ++i) {
		spf[i] = i;
	}

	for (int i = 2; i * i <= n; ++i) if (spf[i] == i) {
		for (int j = i * i; j <= n; j += i) if (spf[j] == j) spf[j] = i;
	}

	for (int i = 1; i <= n; ++i) {
		int val = i;
		while (val > 1) {
			int j = spf[val];
			f[i].push_back(j);

			while (val % j == 0) val /= j;
		}
	}

	init();

	sort(edges + 1, edges + 1 + m, cmp);

	for (int i = 1; i <= m; ++i) {
		unite(edges[i].u, edges[i].v, edges[i].w);
	}

	double res = ans[findPar(1)];
	double countP = c[findPar(1)];

	cout << fixed << setprecision(2);

	cout << res / countP;

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "maxpath"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
