#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 02.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 1e3 + 5, MOD = 1e9 + 7; 

int n, k;
vector<pair<int, int> > seg;  

namespace Subtask1 {
	bool check(void) {
		if (n > 16) return false; 
		return true; 
	}

	void solve(void) {
		int ans = 0; 
		sort(seg.begin(), seg.end());
		for (int mask = 1; mask < (1 << n); ++mask) {
			vector<pair<int, int> > tmp; 
			for (int j = 0; j < n; ++j) if ((mask >> j) & 1) {
				tmp.push_back(seg[j]);
			}

			int maxR = 0, cnt = 0; 

			for (auto &x : tmp) {
				if (x.first > maxR) cnt++;
				maxim(maxR, x.second);
			}

			int res = 1; 

			for (int i = 1; i <= k; ++i) {
				res = res * cnt; 
				res %= MOD; 
			}

			ans += res; 
			ans %= MOD; 
		}

		cout << ans; 
	}
}

void kakuai(void) { 
	cin >> n >> k; 

	for (int i = 1; i <= n; ++i) {
		int l, r; 
		cin >> l >> r; 
		seg.emplace_back(l, r);
	}

	Subtask1::solve();
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	fio("sensors");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
