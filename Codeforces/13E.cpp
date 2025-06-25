/*
	Author: tinhnopro
	created: 02.01.2025 15:38:00
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK ""

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 
const int BLOCK = 350; 

int n, m; 
int a[maxN], nxt[maxN], cnt[maxN]; 

inline int getblock(const int& id) {
	return (id - 1) / BLOCK + 1; 
}

void upd(int idx) {
	if (idx + a[idx] > n || getblock(idx) != getblock(idx + a[idx])) 
		nxt[idx] = idx, cnt[idx] = 0; 
	else 
		nxt[idx] = nxt[idx + a[idx]], cnt[idx] = cnt[idx + a[idx]] + 1; 
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> n >> m; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	for (int i = n; i; --i) upd(i); 

	// for (int i = 1; i <= n; ++i) {
	// 	cerr << nxt[i] << ' ' << cnt[i] << '\n'; 
	// }

	while (m--) {
		int type; cin >> type; 
		if (type) {
			int x; 
			cin >> x; 
			int next_x = 0, c = 0; 
			for (; x <= n; next_x = nxt[x], x = next_x + a[next_x])
				c += cnt[x] + 1;
			
			cout << next_x << ' ' << c << '\n'; 
		} else {
			int x, y; 
			cin >> x >> y; 
			a[x] = y; 
			for (int i = x; i && getblock(x) == getblock(i); --i)
				upd(i); 
		}
	}
}