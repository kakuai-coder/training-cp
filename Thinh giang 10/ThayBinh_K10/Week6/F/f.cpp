/*
	Author: kakuai
	created: 2025.07.03 14:37:30
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

const int maxN = 2e5 + 5; 

int n, a[maxN], dpL[maxN], dpR[maxN], bit[maxN];
vector<int> compress; 

int get_id(int x) {
	return lower_bound(compress.begin(), compress.end(), x) - compress.begin() + 1; 
}

void update(int id, int val) {
	for (; id; id -= id & -id) bit[id] = max(bit[id], val);
}

int query(int x) {
	int res = 0; 
	for (; x < maxN; x += x & -x) res = max(res, bit[x]);

	return res; 
}

void kakuai() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) cin >> a[i];

	for (int i = 1; i <= n; ++i) {
		dpL[i] = 1; 
		if (i > 1 && a[i] > a[i - 1]) dpL[i] = dpL[i - 1] + 1; 
	} 

	for (int i = n; i >= 1; --i) {
		dpR[i] = 1; 
		if (i < n && a[i] < a[i + 1]) dpR[i] = dpR[i + 1] + 1;
	}

	int ans = 0; 

	for (int i = 1; i <= n; ++i) maximize(ans, dpL[i]);

	for (int i = 1; i <= n; ++i) compress.push_back(a[i]); 

	sort(compress.begin(), compress.end()); 

	compress.erase(unique(compress.begin(), compress.end()), compress.end());

	for (int i = 1; i <= n; ++i) a[i] = get_id(a[i]);

	for (int i = n; i >= 1; --i) {
		
		if (i < n) {
			maximize(ans, dpL[i] + query(a[i] + 1));
		}
		update(a[i], dpR[i]);
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "f"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}