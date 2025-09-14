#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 31.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 1e5 + 5, LOG = 17; 
const int MAXV = 1e9 + 299; 
const int64_t INF = (int64_t)1e15 + 11; 

int n, q; 


struct edge_t {

	int a, b, v, s, c; 
	
	edge_t() {
		a = b = v = s = c = 0;
	}

	void input(void) {
		cin >> a >> b >> v >> c >> s; 
	}

	int other(int u) {
		return a ^ b ^ u; 
	}
};

struct query_t {
	int a, b, LCA;
	int64_t m;
	
	query_t() {
		a = b = m = LCA = 0; 
	}

	void input(void) {
		cin >> a >> b >> m; 
	}
};

struct update_t {
	int u, val;

	int64_t delta; 

	update_t() {
		u = val = 0;
		delta = 0; 
	}

	update_t(int _u, int _val, int64_t _delta) : u(_u), val(_val), delta(_delta) {}

	bool operator < (const update_t &other) const {
		return val < other.val; 
	}
};

struct FendwickTree {
	uint64_t bit[2 * MAXN]; 
	int sz; 

	FendwickTree() {
		sz = 0; 
	}

	FendwickTree(int _sz) : sz(_sz) {}

	void reset() {
		for (int i = 0; i <= sz; ++i) bit[i] = 0; 
	}

	void update(int u, int64_t val) {
		if (u == 0) return ; 
		for (; u <= sz; u += u & -u) bit[u] += val;
	}

	void updateRange(int u, int v, int64_t c) {
		update(u, c);
		update(v + 1, -c);
	}

	uint64_t getsum(int u) {
		uint64_t res = 0; 
		for (; u; u -= u & -u) res += bit[u];
		return res; 
	}
};

edge_t edges[MAXN];
query_t queries[MAXN];
vector<update_t> update; 
vector<int> g[MAXN];
int L[MAXN], R[MAXN], edgeId[MAXN], in[2 * MAXN], out[2 * MAXN];
int par[LOG + 1][MAXN], depth[MAXN];
int timer = 0;
FendwickTree bit; 

void dfs(int u) {
	in[u] = ++timer;


	for (int i : g[u]) {
		int v = edges[i].other(u);
		if (v == par[0][u]) continue;
		
		edgeId[v] = i; 
		par[0][v] = u; 
		depth[v] = depth[u] + 1; 
		dfs(v);
	}

	out[u] = timer;
}

int lca(int u, int v) {
	if (u == v) return u;
	if (depth[u] < depth[v]) swap(u, v);

	for (int i = LOG; ~i; --i) if (depth[par[i][u]] >= depth[v]) u = par[i][u];

	if (u == v) return u;

	for (int i = LOG; ~i; --i) if (par[i][u] != par[i][v]) {
		u = par[i][u];
		v = par[i][v];
	}

	return par[0][u]; 
}

void kakuai(void) { 
	cin >> n; 

	for (int i = 1; i < n; ++i) {
		edges[i].input(); 

		g[edges[i].a].push_back(i);
		g[edges[i].b].push_back(i);
	}

	dfs(1);
	depth[0] = -1; 
	for (int j = 1; j <= LOG; ++j) for (int u = 1; u <= n; ++u) par[j][u] = par[j - 1][par[j - 1][u]];
	bit.sz = 2 * n;

	cin >> q; 

	for (int i = 1; i <= q; ++i) {
		queries[i].input(); 
		queries[i].LCA = lca(queries[i].a, queries[i].b);
	}

	for (int i = 1; i <= q; ++i) {
		L[i] = 0; 
		R[i] = MAXV; 
	}

	for (int i = 2; i <= n; ++i) {
		int id = edgeId[i];
		update.push_back({i, edges[id].v + 1, edges[id].c});
		update.push_back({i, edges[id].s + 1, INF});
	}

	sort(update.begin(), update.end());

	
	while (true) {
		vector<array<int, 2> > checks; 
		for (int i = 1; i <= q; ++i) if (R[i] - L[i] > 1) {
			int mid = (L[i] + R[i]) >> 1; 
			checks.push_back({mid, i});
		}		

		if (checks.empty()) break;

		bit.reset();
		sort(checks.begin(), checks.end());
		
		int j = 0; 
		for (auto &chks : checks) {
			int curMid = chks[0], curId = chks[1];

			while (j < (int)update.size() && update[j].val <= curMid) {
				int tmp = update[j].u; 
				bit.updateRange(in[tmp], out[tmp], update[j].delta);
				++j;
			}

			uint64_t sumPath = bit.getsum(in[queries[curId].a]) + bit.getsum(in[queries[curId].b]) 
							- 2LL * bit.getsum(in[queries[curId].LCA]);

			if (sumPath <= queries[curId].m) L[curId] = curMid;
			else R[curId] = curMid;
		}
	}

	for (int i = 1; i <= q; ++i) cout << L[i] << '\n';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	fio("traffic");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
