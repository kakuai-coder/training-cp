/*
	Author: tinhnopro
	created: 2025.06.17 22:29:35
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
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5; 
const int BLOCK = 320; 

int n, k, a[maxN];
int x[maxN];
int head[maxN], pos[maxN];

i64 s[BLOCK][maxN];
int blockID[maxN];
vector<int> v[BLOCK], v2[BLOCK]; 

void add(int blockID, int i) {

	for (int idx = 0; idx < ssize(v2[blockID]); ++idx) s[blockID][idx % k] = 0;

	v2[blockID].push_back(i);

	sort(v2[blockID].begin(), v2[blockID].end());

	for (int idx = 0; idx < ssize(v2[blockID]); ++idx) {
		s[blockID][idx % k] += x[v2[blockID][idx]];
	}
}


void tinhnop() {
	cin >> n >> k; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		x[i] = a[i];
	}

	sort(x + 1, x + n + 1);
	
	for (int i = 1; i <= n; ++i) {
		pos[i] = lower_bound(x + 1, x + n + 1, a[i]) - x; 
	}

	for (int i = 1; i <= n; ++i) {
		blockID[i] = (i - 1) / BLOCK; 
	}
	
	for (int i = 1; i <= n; ++i) {
		add(blockID[pos[i]], pos[i]);

		i64 res = 0; 
		int cur = 0;
		
		for (int idx = 0; idx <= blockID[n]; ++idx) {
			i64 d = k - cur;
			d += 1LL * 1e9 * k;
			d %= k;
			res += s[idx][d];
			cur += v2[idx].size();
		}

		cout << res << '\n'; 
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "c"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}