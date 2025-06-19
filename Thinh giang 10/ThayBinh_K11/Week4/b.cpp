/*
	Author: tinhnopro
	created: 2025.04.25 14:16:19
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

const int maxN = 2e5 + 5; 

int n, a[maxN], v[maxN]; 
Compressor<int> com; 
i64 bit[maxN]; 

void update(int u, int val) {
	for (; u < maxN; u += u & -u) bit[u] += val; 
}

i64 query(int u) {
	i64 res = 0; 

	for (; u; u -= u & -u) res += bit[u]; 

	return res; 
}

void tinhnop() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> v[i] >> a[i]; 
		com.add(v[i]);
	}

	com.Compress();

	i64 sum = 0; 


	for (int i = 1; i <= n; ++i) {
		int idx = com.Get(v[i]);
		sum += a[i]; 
		update(idx, a[i]); 

		i64 d = sum / 2; 
		if (sum & 1) d++; 

		i64 l = 0, r = maxN - 1;
		while (l + 1 < r) {
			i64 mid = (l + r) >> 1;
			if (query(mid) < d) l = mid;
			else r = mid;  
		}

		cout << com.h[r - 1] << '\n';
	}

}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}