/*
	Author: kakuai
	created: 2025.07.04 10:01:29
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

const int maxN = 1e5 + 200; 

int n, k; 
int a[maxN], b[maxN], c[maxN], d[maxN], dp[maxN];
vector<pair<int, int> > v[maxN];
int st[4 * maxN]; 

void upd(int id, int l, int r, int u, int v, int val) {
	if (l > v || r < u) return;
	if (l >= u && r <= v) {
		st[id] = max(st[id], val);
		return;
	}
	int mid = (l + r) / 2;
	upd(id * 2, l, mid, u, v, val);
	upd(id * 2 + 1, mid + 1, r, u, v, val);
	st[id] = max(st[id * 2], st[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0;
	if (l >= u && r <= v) return st[id];
	int mid = (l + r) / 2;
	return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}


void kakuai() {
	cin >> n >> k; 

	for (int i = 1; i <= k; ++i) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		v[a[i]].push_back({1, i});
		v[b[i] + 1].push_back({0, i});
	}

	for (int i = 0; i <= n + 1; ++i) {
		sort(v[i].begin(), v[i].end());

		for (auto &x : v[i]) {
			int type = x.first; 
			int pos = x.second; 

			if (type) dp[pos] = get(1, 0, n + 2, 0, c[pos] - 1) + 1;
			else upd(1, 0, n + 2, d[pos], d[pos], dp[pos]);
		}
	}

	int ans = 0; 

	for (int i = 1; i <= k; ++i) maximize(ans, dp[i]);

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "pinz"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}