#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define BIT(x, i) ((x) & (1 << (i)))
#define MASK(x) (1 << (x))
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using iLL = pair<ll, int>;

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = 5e5 + 11, MAX = 1e6 + 11;
//const int MOD = 1e9 + 7;
const int INF = 1e9 + 11; const ll INFF = 1e18 + 11;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int n, m;

struct Node {
    int v, c, w;
    Node() {
        v = c = w = 0;
    }
    Node(int _v, int _w, int _c) {
        v = _v; c = _c; w =  _w;
    }
};

vector<Node> adj[MAXN];
ll inforPrefix[2][MAXN], inforSuffix[2][MAXN];
ll dis[2][MAXN];

void Dijsktra(int s, ll *d, ll *inforMax, ll *inforMin) {
    priority_queue<iLL, vector<iLL>, greater<iLL> > pq;
    FORE(i, 1, n) {
        d[i] = INFF;
        inforMin[i] = INFF;
    }
    d[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().se;
        ll d_u = pq.top().fi;
        pq.pop();
//        cerr << u << ": ";
        if (d_u > d[u]) continue;
        for (Node x : adj[u]) {
            int w = x.w, v = x.v, c = x.c;
            if (d[v] > d[u] + w) {
                inforMax[v] = max(inforMax[u], 1LL * c);
                inforMin[v] = min(inforMin[u], 1LL * c);
                pq.push({d[v] = d[u] + w, v});
            } else if (d[v] == d[u] + w) {
                minimize(inforMin[v], c);
                maximize(inforMax[v], c);
                minimize(inforMin[v], inforMin[u]);
                maximize(inforMax[v], inforMax[u]);
            }
        }
    }
}

void process(void) {
    cin >> n >> m;
    FORE(i, 1, m) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        adj[u].push_back(Node(v, w, c));
        adj[v].push_back(Node(u, w, c));
    }
    Dijsktra(1, dis[0], inforPrefix[0], inforPrefix[1]);
    Dijsktra(n, dis[1], inforSuffix[0], inforSuffix[1]);
    ll ans = 0;
    FORE(i, 1, n) {
         if (dis[0][i] + dis[1][i] == dis[0][n]) {
//            cout << inforPrefix[0][i] << " " << inforSuffix[0][i] << " " << inforPrefix[1][i] << " " << inforSuffix[1][i] << "\n";
            maximize(ans, inforPrefix[0][i] - inforSuffix[1][i]);
            maximize(ans, inforSuffix[0][i] - inforPrefix[1][i]);
        }
    }
    cout << ans;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	file("e");
//	int t; cin >> t; while(t--)
	process();
	return 0;
}
