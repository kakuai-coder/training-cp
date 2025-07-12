/*
	Author: kakuai
	created: 2025.07.03 14:14:40
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int MaxN = 2e5 + 5; 

int n, q, a[MaxN], bit[MaxN];

void update(int id, int val) {
	for (; id <= n; id += id & -id) bit[id] += val;
}

int query(int x) {
	int res = 0; 
	for (; x; x -= x & -x) res += bit[x];

	return res; 
}

void kakuai() {
	cin >> n >> q; 
	for (int i = 1; i <= n; ++i) cin >> a[i]; 

	for (int i = 1; i <= n; ++i) update(i, a[i]);

	while (q--) {
		int op, x, y; 
		cin >> op >> x >> y; 

		if (op == 1) {
			update(x, - a[x] + y);
			a[x] = y; 
		} else {
			cout << query(y) - query(x - 1) << '\n';
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}