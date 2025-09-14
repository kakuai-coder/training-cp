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

const int maxN = 1e6 + 5;
const int64_t inf = (int64_t) 1e18 + 11;

int n, m, q, s, t;
vector<pair<int, int> > g[maxN], revg[maxN];
int topoId[maxN], vist[maxN];
int64_t ds[maxN], dt[maxN], ans[maxN];
vector<int> topo;
vector<array<int64_t, 3> > edges, segments;
vector<int64_t> sweep[maxN];

void dfs(int u) {
	vist[u] = 1;
	for (auto &x : g[u]) if (!vist[x.first]) dfs(x.first);

	topo.push_back(u);
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m >> s >> t;

	int cur = n + 1;

	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;

		g[u].push_back({cur, w});
		g[cur].push_back({v, 0});

		revg[v].push_back({cur, 0});
		revg[cur].push_back({u, w});

		edges.push_back({u, cur, w});
		edges.push_back({cur, v, 0});

		cur++;
	}

	n += m;

	pqmin<pair<int64_t, int> > pq;

	for (int i = 1; i <= n; ++i) {
		ds[i] = inf;
	}

	ds[s] = 0;
	pq.push({0, s});

	while (!pq.empty()) {
		int u = pq.top().second;
		int64_t d_u = pq.top().first;
		pq.pop();

		if (d_u > ds[u]) continue;

		for (auto &x : g[u]) {
			int v = x.first;
			int w = x.second;

			if (ds[v] > ds[u] + w) {
				ds[v] = ds[u] + w;
				pq.push({ds[v], v});
			}
		}
	}

	while (!pq.empty()) pq.pop();

	for (int i = 1; i <= n; ++i) {
		dt[i] = inf;
	}
	dt[t] = 0;
	pq.push({0, t});

	while (!pq.empty()) {
		int u = pq.top().second;
		int64_t d_u = pq.top().first;
		pq.pop();

		if (d_u > dt[u]) continue;

		for (auto &x : revg[u]) {
			int v = x.first;
			int w = x.second;

			if (dt[v] > dt[u] + w) {
				dt[v] = dt[u] + w;
				pq.push({dt[v], v});
			}
		}
	}

	dfs(s);

	reverse(topo.begin(), topo.end());

	for (int i = 0; i < size32(topo); ++i) {
		topoId[topo[i]] = i + 1;
	}

	for (auto &e : edges) {
		int u = e[0];
		int v = e[1];
		int w = e[2];

		segments.push_back({u, v, ds[u] + w + dt[v]});
		sweep[topoId[v]].push_back(ds[u] + w + dt[v]);
	}

	cin >> q;

	vector<pair<int, int> > ask;

	for (int i = 1; i <= q; ++i) {
		char op;
		cin >> op;

		if (op == 'V') {
			int x;
			cin >> x;
			ask.push_back({x, i});
		} else {
			int x;
			cin >> x;
			ask.push_back({n - m + x, i});
		}
	}

	sort(ask.begin(), ask.end(), [&] (const pair<int, int> &a, const pair<int, int> &b){
		return topoId[a.first] < topoId[b.first];
	});

	sort(segments.begin(), segments.end(), [&] (const array<int64_t, 3> &a, const array<int64_t, 3> &b){
		return topoId[a[0]] < topoId[b[0]];
	});

	multiset<int64_t> S;

	int i = 0, j = 1;

	for (auto &as : ask) {
		int x = as.first;
		int id = as.second;

		while (i < size32(segments) && topoId[segments[i][0]] < topoId[x]) {
			S.insert(segments[i][2]);
			i++;
		}

		while (j <= topoId[x]) {
			for (int64_t &val : sweep[j]) {
				S.erase(S.find(val));
			}
			j++;
		}

		ans[id] = (S.empty() ? - 1 : *(S.begin()));
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "e"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
