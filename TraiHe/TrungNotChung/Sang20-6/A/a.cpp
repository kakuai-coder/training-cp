/*
	Author: kakuai
	created: 2025.06.20 08:31:58
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5; 
const int LOG = 20; 

int n, q; 
i64 a[maxN], sum[maxN], mx[maxN][LOG + 1], mi[maxN][LOG + 1], X, Y;
pair<int, int> nxt[maxN][2];
pair<int, int> jump[maxN][2][LOG + 1];

void build_rmq() {
	for (int i = 0; i <= n; ++i) {
		mx[i][0] = mi[i][0] = sum[i];
	}

	for (int j = 1; j <= LOG; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
		}
	}
}

i64 get_max(int l, int r) {
	if (l > r) return 1e16;
	int lg = __lg(r - l + 1);
	return max(mx[l][lg], mx[r - (1 << lg) + 1][lg]);
}

i64 get_min(int l, int r) {
	if (l > r) return -1e16;
	int lg = __lg(r - l + 1);
	return min(mi[l][lg], mi[r - (1 << lg) + 1][lg]);
}

int nxt_X(int l, int k) {
	i64 d = X + sum[l - 1] - k; 

	int lo = l, hi = n, pos = n + 1; 

	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		// cerr << mid << ' ' << get_min(l, mid) << '\n'; 
		if (get_min(l, mid) < d) {
			pos = mid;
			hi = mid - 1; 
		} else lo = mid + 1; 
	}

	return pos; 
}

int nxt_Y(int l, int k) {
	i64 d = Y + sum[l - 1] - k; 

	int lo = l - 1, hi = n + 1; 

	while (hi - lo > 1) {
		int mid = (lo + hi) / 2; 
		if (get_max(l, mid) <= d) {
			lo = mid; 
		} else hi = mid; 
	}

	return hi; 
}


void kakuai() {
	cin >> n >> X >> Y; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		sum[i] = sum[i - 1] + a[i]; 
	}
	
	build_rmq();

 	for (int i = 1; i <= n; ++i) {
		nxt[i][0] = {nxt_X(i + 1, X), 0};
		if (minimize(nxt[i][0].first, nxt_Y(i + 1, X))) {
			nxt[i][0].second = 1; 
		}

		nxt[i][1] = {nxt_X(i + 1, Y), 0};
		if (minimize(nxt[i][1].first, nxt_Y(i + 1, Y))) {
			nxt[i][1].second = 1; 
		}

		// cout << nxt[i][1].first << ' ' << nxt[i][1].second << '\n';
	}

	nxt[n][0] = {n + 1, 0}; 
	nxt[n][1] = {n + 1, 1};
	
	for (int i = 1; i <= n; ++i) {
		jump[i][0][0] = nxt[i][0]; 
		jump[i][1][0] = nxt[i][1];
		// cout << nxt[i][0].first << ' ' << nxt[i][1].first << '\n';
	}


	for (int j = 1; j <= LOG; ++j) {
		for (int i = 1; i <= n; ++i) {
			for (int d = 0; d <= 1; ++d) {
				pair<int, int> k = jump[i][d][j - 1];
				jump[i][d][j] = jump[k.first][k.second][j - 1];
			}
		}
	}

	cin >> q; 
	while (q--) {
		int l, r, k; cin >> l >> r >> k;

		int idx = nxt_X(l, k); 
		int id = 0; 

		if (minimize(idx, nxt_Y(l, k))) id = 1; 

		// cout << id << ' ' << idx << '\n';

		if (idx - 1 >= r) {
			i64 s = k + sum[r] - sum[l - 1]; 
			if (s < X) s = X; 
			if (s > Y) s = Y; 
			cout << s << '\n'; 
			continue;
		}

		for (int i = LOG; i >= 0; --i) {
			pair<int, int> d = jump[idx][id][i];

			if (d.first <= r && d.first != 0) {
				// cout << d.first << ' ' << d.second << '\n';
				idx = d.first; 
				id = d.second;
			}
		}

		i64 ans = 0; 
		
		if (id == 0) {
			ans = X; 
		} else ans = Y;

		// cout << id << ' ' << idx << '\n';

		cout << ans + sum[r] - sum[idx] << '\n';
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