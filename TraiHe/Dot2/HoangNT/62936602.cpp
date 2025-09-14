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


struct edge_t {
	int u, v;
	int64_t p, w;
 
	edge_t(int _u = 0, int _v = 0, int64_t _p = 0, int64_t _w = 0) : u(_u), v(_v), p(_p), w(_w) {}
 
	bool operator < (const edge_t& other) const {
		if (p == other.p) return w < other.w;
		return p < other.p;
	}
};
 
const int MAXN = 2e5 + 5;
const int64_t INF = (int64_t) 1e18 + 11;
 
int n, m;
vector<edge_t> edges;
vector<pair<int, int64_t> > g[MAXN];
int lab[MAXN];
int64_t dist[MAXN];
 
int find_root(int u) {
	return lab[u] < 0 ? u : lab[u] = find_root(lab[u]);
}
 
bool joint(int u, int v) {
	u = find_root(u);
	v = find_root(v);
 
	if (u == v) return false;
 
	if (lab[u] > lab[v]) swap(u, v);
 
	lab[u] += lab[v];
	lab[v] = u;

	return true;
}
 
void kakuai(void) {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		int64_t p, w;
		cin >> u >> v >> p >> w;
		edges.push_back({u, v, p, w});
	}
 
	sort(edges.begin(), edges.end());
 
	memset(lab, -1, sizeof(lab));
	
	// for (auto &e : edges) cerr << e.u << ' ' << e.v << '\n';

	int64_t ans = -1;
 
	for (auto &e : edges) {
		joint(e.u, e.v);
		if (find_root(1) == find_root(n)) {
			ans = e.p;
			break;
		}
 
	}
 
	for (auto &e : edges) {
		if (e.p > ans) break;
 
		g[e.u].push_back({e.v, e.w});
		g[e.v].push_back({e.u, e.w});
	}
 
	cout << ans << ' ';
 
	pqmin<pair<int64_t, int> > pq;
 
	for (int i = 1; i <= n; ++i) {
		dist[i] = INF;
	}
 
	dist[1] = 0;
 
	pq.push({dist[1], 1});
 
	while (!pq.empty()) {
		int u = pq.top().second;
		int64_t d_u = pq.top().first;
		pq.pop();
 
		if (d_u > dist[u]) continue;
 
		for (auto &x : g[u]) {
			int v = x.first;
			int64_t w = x.second;
 
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
 
	cout << dist[n];
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
