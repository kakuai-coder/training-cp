/*
	Author: tinhnopro
	created: 2025.06.16 10:08:44
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

#define int long long 

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int INF = 1e18 + 11;

int n, q; 

int w[2009][2009];

bool inMST[2009];     
int minEdge[2009];    

int prim() {
    fill(inMST, inMST + n + 1, false);
    fill(minEdge, minEdge + n + 1, INF);
    minEdge[1] = 0;

    int totalWeight = 0;

    for (int i = 1; i <= n; ++i) {
        int u = -1;
        for (int v = 1; v <= n; ++v) {
            if (!inMST[v] && (u == -1 || minEdge[v] < minEdge[u])) {
                u = v;
            }
        }

        if (minEdge[u] == INF) return -1; 

        totalWeight += minEdge[u];
        inMST[u] = true;

        for (int v = 1; v <= n; ++v) {
            if (w[u][v] != INF && !inMST[v]) {
                minEdge[v] = min(minEdge[v], w[u][v]);
            }
        }
    }

    return totalWeight;
}

void tinhnop() {
	cin >> n >> q; 
	

	
	while (q--) {
		int x, y, u, v, c; 
		cin >> x >> y >> u >> v >> c; 
		for (int i = x; i <= y; ++i) {
			for (int j = u; j <= v; ++j) {
				w[i][j] = w[j][i] += c;
			}
		}
	}

	cout << prim();
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "mst"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}