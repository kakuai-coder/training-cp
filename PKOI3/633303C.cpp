#include <bits/stdc++.h>

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define all(v) v.begin(), v.end()
#define debug(x) cerr << #x << ": " << x << "\n"

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int siz(const T &a) {
	return a.size();
}

// > kakuai < <cherry> >> 06.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5;

int n, q; 
int a[MAXN];
vector<int> g[MAXN];

int num[MAXN], tail[MAXN], ord[2 * MAXN], timer = 0, lg2[2 * MAXN], rmq[2 * MAXN][21];

void dfs(int u, int pre) {
    num[u] = timer;
    ord[timer++] = u; 
    for (auto &v : g[u]) if(v ^ pre) {
        dfs(v, u);
        ord[timer++] = u; 
    }
    tail[u] = timer;
}   

int comp(int u, int v) {
    return num[u] < num[v] ? u : v;
}

void build_lcaO1(int S) {
    timer = 0;
    dfs(S, 0);
    lg2[1] = 0;
    for (int i = 2; i <= timer + 8; ++i) lg2[i] = lg2[i / 2] + 1; 
    for (int i = 0; i < timer; ++i) {
        rmq[i][0] = ord[i];
    }
    for (int k = 1; (1 << (k)) <= timer; ++k) {
        for (int i = 0; i + (1 << (k)) - 1 < timer; ++i)
            rmq[i][k] = comp(rmq[i][k - 1], rmq[i + (1 << (k - 1))][k - 1]);
    }
}

int getLCA(int u, int v) {
    int l = min(num[u], num[v]), r = max(num[u], num[v]);
    int k = lg2[r - l + 1];
    return comp(rmq[l][k], rmq[r - (1 << (k)) + 1][k]);
}

set<int> s[MAXN];

struct FendwickTree {
	int bit[2 * MAXN];

	FendwickTree() {
		memset(bit, 0, sizeof(bit));
	}

	void update(int u, int val) {
		++u;
		for (; u <= timer; u += u & -u) bit[u] += val;
	}

	int get(int l, int r) const {
		r++; 
		int res = 0; 

		for (; r; r -= r & -r) res += bit[r]; 
		for (; l; l -= l & -l) res -= bit[l];

		return res; 
	}
} fw;

void add(int v, int c) {
	if (c == 0) return ;
	auto y = s[c].lower_bound(num[v]);
	auto x = prev(y);

	int lca = getLCA(ord[*x], ord[*y]) ^ getLCA(ord[*x], v) ^ getLCA(v, ord[*y]);

	fw.update(num[v], 1);
	fw.update(num[lca], -1);

	s[c].insert(num[v]);
}

void del(int v, int c) {
	if (c == 0) return ;
    s[c].erase(num[v]);

	auto y = s[c].lower_bound(num[v]);
	auto x = prev(y);

	int lca = getLCA(ord[*x], ord[*y]) ^ getLCA(ord[*x], v) ^ getLCA(v, ord[*y]);

	fw.update(num[v], -1);
	fw.update(num[lca], 1);
}

void kakuai(void) { 
	cin >> n >> q; 
	for (int i = 1; i <= n; ++i) cin >> a[i];

	fw = FendwickTree();
	
	g[n + 1].push_back(1); 
	g[n + 1].push_back(n + 2);

	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		g[u].push_back(v); 
		g[v].push_back(u);
	}

	build_lcaO1(n + 1);

	for (int i = 1; i <= n; ++i) s[i].insert(num[n + 1]), s[i].insert(num[n + 2]);

	for (int i = 1; i <= n; ++i) add(i, a[i]); 

	// cout << fw.get(num[n + 1], tail[n + 1]) << '\n';

	int ans = 0; 

	while (q--) {
		int op; cin >> op; 

		if (op == 1) {
			int v, x; 
			cin >> v >> x; 
			del(v, a[v]);

			a[v] = x; 

			add(v, a[v]);
		} else {
			int v; 
			cin >> v; 

			ans = fw.get(num[v], tail[v]);
			cout << ans << '\n';
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

#define cherry ""
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	int T = 1;
	// cin >> T;
	while (T--) {
		kakuai();
		// cout << '\n';
	}
}