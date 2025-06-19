// Author: tinhnopro (tinhngo)
#include<bits/stdc++.h>

#define name "1572A"
#define el '\n'
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define all(v) (v).begin(), (v).end()
#define szv(v) int((v).size())
#define sqr(x) 1ll * (x) * (x)
#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;

template<class T> using pairD = pair<T, T>;  

template<class T> using vector2d = vector<vector<T>>;

template<class X, class Y> bool maximize(X &a, Y b) { 
	return a < b ? a = b, 1 : 0; 
}

template<class X, class Y> bool minimize(X &a, Y b) { 
	return a > b ? a = b, 1 : 0; 
}

template<class T> T Abs(const T &x) {
	return x < 0 ? -x : x;
}	
//_______________________________________________________________________

const int MAXN = 5e5 + 11; // const int MAX = 1e6 + 11;
// const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; // const ll INFF = 1e18 + 11; 

int n;
vector<pairD<int> > adj[MAXN];
int color[MAXN];

bool is_cyclic(int u) {
	color[u] = 1;
	for (pairD<int> x : adj[u]) {
		if (color[x.fi] == 0) {
			if (is_cyclic(x.fi)) return true; 
		} else if (color[x.fi] == 1) {
			return true; 
		}
	} 
	color[u] = 2;
	return false;
}

vi topo, dp; 

void dfs(int u) {
	color[u] = 1; 
	for (pairD<int> x : adj[u]) if (!color[x.fi]) {
		dfs(x.fi);
	}
	topo.emplace_back(u);
}

void process(void) {
	cin >> n;
	FOR(i, 1, n) adj[i].clear();
	FOR(i, 1, n) {
		int k; cin >> k; 
		FOR(j, 1, k) {
			int x; cin >> x; 
			adj[i].push_back({x,  (x > i ? 1 : 0)});
		}
	}

	memset(color, 0, sizeof color); 
	FOR(i, 1, n) if (color[i] == 0) {
		if(is_cyclic(i)) {
			cout << -1 << el; 
			return ;
		}
	}

	topo.clear();
	dp.clear();
	memset(color, 0, sizeof color);
	FOR(i, 1, n) if (color[i] == 0) {
		dfs(i);
	}
	reverse(all(topo));
	dp.resize(n + 1, 0);
	
	int ans = 0;
	for (int u : topo) {
		for (pairD<int> x : adj[u]) {
			maximize(dp[x.fi], dp[u] + x.se); 
			maximize(ans, dp[x.fi]);
		}
	}

	cout << ans + 1 << el; 
}

int32_t main(void) {
	ios_base::sync_with_stdio(false); 
	cin.tie(nullptr);

	if (fopen(name".inp", "r")) {
		freopen(name".inp", "r", stdin);
		freopen(name".out", "w", stdout);
	}
	//___________________________________
	int t; cin >> t; while (t--)
	process();

	cerr << "\nRuntime: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s\n";
	return 0;
}
