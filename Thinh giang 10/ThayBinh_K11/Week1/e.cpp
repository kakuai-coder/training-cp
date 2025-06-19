/*
	Author: tinhnopro
	created: 04.04.2025 22:41:56
*/
#include <bits/stdc++.h>

#define CHERRY "e"

using namespace std;

using i64 = long long;

template<typename T> struct Compressor {
	vector<T> h; 

	void add(const T& x) {
		h.push_back(x);
	}

	void Compress() {
		sort(h.begin(), h.end()); 
		h.resize(unique(h.begin(), h.end()) - h.begin());
	}

	int Get(const T& x) {
		return lower_bound(h.begin(), h.end(), x) - h.begin() + 1; 
	}
};

const int maxN = 2009; 

struct Fendwicktree {
	int bit[maxN]; 

	Fendwicktree() {
		memset(bit, 0, sizeof(bit));
	}

	void reset() {
		memset(bit, 0, sizeof(bit));
	}

	void update(int u, int val) {
		for (; u < maxN; u += u & -u) bit[u] += val; 
	}

	int query(int u) {
		int res = 0; 
		for (; u; u -= u & -u) res += bit[u]; 
		return res;
	}
} fen[6];

Compressor<int> com; 
int a[maxN], n, q, dp[maxN][maxN][6]; 

void solve() {
	cin >> n >> q; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		com.add(a[i]);
	}

	com.Compress(); 

	for (int i = 1; i <= n; ++i) a[i] = com.Get(a[i]);

	// cerr << "ok";

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= 5; ++j) fen[j].reset(); 

		fen[1].update(a[i], 1);
		dp[i][i][1] = 1; 

		for (int j = i; j <= n; ++j) {
			for (int k = 2; k <= 5; ++k) {
				if (k & 1) {
					dp[i][j][k] = fen[k - 1].query(a[j] - 1);
				} else {
					dp[i][j][k] = fen[k - 1].query(n) - fen[k - 1].query(a[j]);
				}
				fen[k].update(a[j], dp[i][j][k]);
			}
		}
	}

	while (q--) {
		int L, R; cin >> L >> R; 
		cout << dp[L][R][5] << '\n';
	}

	return void(cout << '\n');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t;

	for (int i = 1; i <= t; ++i) {
		cerr << "Case #" << i << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}