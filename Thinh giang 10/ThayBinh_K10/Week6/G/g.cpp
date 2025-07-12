/*
	Author: kakuai
	created: 2025.07.03 15:00:20
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

const int maxN = 1e5 + 5; 
int n, a[maxN], w[maxN], bit[maxN], dp[maxN], pre[maxN], idx[maxN];

void update(int id, int val, int from) {
	for (; id < maxN; id += id & -id) {
		if (bit[id] < val) {
			bit[id] = val;
			idx[id] = from;
		}
	}
}

pair<int, int> query(int x) {
	int res = 0, at = 0;
	for (; x; x -= x & -x) {
		if (bit[x] > res) {
			res = bit[x];
			at = idx[x];
		}
	}
	return {res, at};
}

void kakuai() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> w[i];

	int ans = 0, last = 0;

	for (int i = 1; i <= n; ++i) {
		pair<int, int> x = query(a[i] - 1);
		int mx = x.first; 
		int from = x.second;
		dp[i] = mx + w[i];
		pre[i] = from;
		update(a[i], dp[i], i);
		if (maximize(ans, dp[i])) last = i;
	}

	vector<int> res;
	while (last) {
		res.push_back(last);
		last = pre[last];
	}
	reverse(res.begin(), res.end());

	cout << ssize(res) << '\n';
	for (int i = 0; i < ssize(res); ++i)
		cout << res[i] << " ";
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "g"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}