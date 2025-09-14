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
// > kakuai < <cherry> >> 30.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 1e3 + 5; 

int n, m, q;
int pos[MAXN];
bool can_vist[MAXN][MAXN], is_edges[MAXN][MAXN]; 
vector<int> adj[MAXN];
int t[MAXN];

void bfs(int s) {
	queue<int> q; 

	q.push(s); 

	can_vist[s][s] = 1; 

	while (!q.empty()) {
		int u = q.front(); 
		q.pop();


		for (int v : adj[u]) if (!can_vist[s][v]) {
			q.push(v);
			can_vist[s][v] = 1;
		}
	}
}

void kakuai(void) { 
	cin >> n >> m >> q; 
	for (int i = 1; i <= n; ++i) cin >> t[i]; 

	for (int i = 1; i <= n; ++i) pos[i] = i; 

	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		if (is_edges[u][v]) continue;
		adj[u].push_back(v); 
		is_edges[u][v] = 1; 
	}

	for (int i = 1; i <= n; ++i) bfs(i); 

	while(q--) {
		int op; 
		cin >> op;

		if (op == 1) {
			int u, v; 
			cin >> u >> v; 
			swap(t[pos[u]], t[pos[v]]);
			swap(pos[u], pos[v]); 
		} else {
			int u; 
			cin >> u; 
			int ans = 1e9 + 11;
			for (int i = 1; i <= n; ++i) if (i != pos[u] && can_vist[i][pos[u]]) minim(ans, t[i]);

			cout << (ans == 1e9 + 11 ? 0 : ans) << '\n';
		}
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	fio("manage");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
