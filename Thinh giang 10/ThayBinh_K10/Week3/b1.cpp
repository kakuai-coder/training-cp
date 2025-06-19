/*
	Author: tinhnopro
	created: 2025.04.16 14:12:11
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif

#define ii pair<int,int>
#define fi first 
#define se second
#define pb push_back
//_____________________________________________________________________________________________

#define int long long 

const int N = 225;

int d, p, c, f, s;

vector < ii > E[N];

int t[N];

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

double ti;

void dijkstra(){
	priority_queue <ii> pq;

	for (int i = 1; i <= d; i++)
		if (i != s)
			t[i] = -1e18;
	t[s] = d;
	pq.push({d, s});

	while (pq.size()){
		ii val = pq.top();
		pq.pop();

		int u = val.se;
		int du = val.fi;

		if (TIME - ti > 0.3){
			t[u] = 1e18;
			return;
		}

		if (du != t[u])
		continue;

		for (ii i : E[u]){
			int v = i.fi;
			int w = i.se;

			if (maximize(t[v], t[u] + d - w))
				pq.push({t[v], v});
		}
	}
}

void tinhnop() {
	cin >> d >> p >> c >> f >> s;

	for (int i = 1; i <= p; i ++){
		int u, v;
		cin >> u >> v;
		E[u].pb({v, 0});
	}

	for (int i = 1; i <= f; i ++){
		int u, v, c;
		cin >> u >> v >> c;
		E[u].pb({v, c});
	}

	ti = TIME;

	dijkstra();

	int ans = -1e18;

	for (int i = 1; i <= d; i ++)
		maximize(ans, t[i]);
	
	if (ans == 1e18)
		cout << -1;
	else
		cout << ans;
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b1"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}