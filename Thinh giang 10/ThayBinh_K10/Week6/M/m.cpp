/*
	Author: kakuai
	created: 2025.07.03 17:03:19
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
int n, a[maxN], dpL[maxN], dpR[maxN];

struct Fenwick {
    int n;
    int f[maxN];
    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; ++i) f[i] = 0;
    }
    void update(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] = max(f[i], v);
    }
    int query(int i) {
        int res = 0;
        for (; i; i -= i & -i)
            res = max(res, f[i]);
        return res;
    }

		void update2(int i, int v) {
        for (; i; i -= i & -i)
            f[i] = max(f[i], v);
    }
    int query2(int i) {
        int res = 0;
        for (; i <= n; i += i & -i)
            res = max(res, f[i]);
        return res;
    }
} fen1, fen2;

void kakuai() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	vector<int> compress(a + 1, a + n + 1);
	sort(compress.begin(), compress.end());
	compress.erase(unique(compress.begin(), compress.end()), compress.end());
	int m = compress.size();

	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(compress.begin(), compress.end(), a[i]) - compress.begin() + 1;
	}

	fen1.init(n + 2); 

	for (int i = 1; i <= n; ++i) {
		dpL[i] = fen1.query2(a[i] + 1) + 1;
		fen1.update2(a[i], dpL[i]);
	}

	fen2.init(n + 2); 

	for (int i = n; i >= 1; --i) {
		dpR[i] = fen2.query2(a[i] + 1) + 1;
		fen2.update2(a[i], dpR[i]); 
	}

	int ans = 0; 

	for (int i = 1; i <= n; ++i) {
		maximize(ans, dpL[i] + dpR[i] - 1);
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "m"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}