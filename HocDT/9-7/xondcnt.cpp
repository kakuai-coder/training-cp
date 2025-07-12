/*
	Author: kakuai
	created: 2025.07.09 14:06:35
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
const int Log = 17; 

int n, a[maxN], st[Log + 1][maxN], pref_xor[maxN]; 
vector<pair<int, int> > v; 

void build() {
	for (int i = 1; i <= n; ++i) st[0][i] = a[i]; 

	for (int j = 1; j <= Log; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[j][i] = st[j - 1][i] & st[j - 1][i + (1 << (j - 1))];
		}
	}
}

int Get(int l, int r) {
	int k = __lg(r - l + 1);
	return st[k][l] & st[k][r - (1 << k) + 1];
}

void kakuai() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		pref_xor[i] = pref_xor[i - 1] ^ a[i]; 
	}

	for (int i = 1; i <= n; ++i) v.push_back({pref_xor[i], i});

	sort(v.begin(), v.end(), [&](auto &a, auto &b){
		if (a.first == b.first) return a.second < b.second; 
		return a.first < b.first; 
	}); 

	build();
	i64 ans = 0; 

	for (int i = 1; i <= n; ++i) {
		int j = i; 
		while (j <= n) {
			int val = Get(i, j);
			int lo = j, hi = n; 
			while (hi - lo > 1) {
				int mid = (lo + hi) >> 1; 
				// cerr << Get(i, mid) << ' ' << val << '\n';
				if (Get(i, mid) == val) {
					lo = mid;
				} else hi = mid;
			}


			val ^= pref_xor[i - 1]; 
			int l = lower_bound(v.begin(), v.end(), make_pair(val, j)) - v.begin();
			int r = upper_bound(v.begin(), v.end(), make_pair(val, lo)) - v.begin() - 1; 

			ans += r - l + 1; 
			j = lo + 1; 
		}
	}

	cout << ans; 

}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "xondcnt"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}