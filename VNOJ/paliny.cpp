/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-21
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
	#include "D:\Tinhnopro\header\debug.h"
#else
	#define debug(...)
#endif // LOCAL

#define ssz(s) ((int) (s).size())
#define ALL(v) (v).begin(), (v).end()

using int64 = long long;

struct Poly_hash {
	static const int64 base = 311;
	static const int64 mod = (int64_t) 1e9 + 7;

	vector<int64> pref, suff, pw;
	int sz;

	Poly_hash() {
		pref.clear();
		suff.clear();
		pw.clear();
		sz = 0;
	}

	void init(const char *s, int _sz) {
		sz = _sz;

		pref.resize(sz + 2);
		suff.resize(sz + 2);
		pw.resize(sz + 2);

		pw[0] = 1;

		for (int i = 1; i <= sz; ++i) {
			pw[i] = pw[i - 1] * base % mod;
			pref[i] = (pref[i - 1] * base % mod + s[i] + 1) % mod;
			suff[i] = (suff[i - 1] * base % mod + s[sz - i + 1] + 1) % mod;
		}
	}

	int64 get(int l, int r) const {
		return (pref[r] - pref[l - 1] * pw[r - l + 1] % mod + mod * mod) % mod;
	}

	int64 getrev(int l, int r) const {
		return (suff[sz - l + 1] - suff[sz - r] * pw[r - l + 1] % mod + mod * mod) % mod;
	}

	bool isPalin(int l, int r) {
		return get(l, r) == getrev(l, r);
	}
} Hash;

const int maxN = 5e4 + 11;

int n;
char a[maxN];


bool check(int len) {
	for (int i = 1; i <= n - len + 1; ++i) {
		if (Hash.isPalin(i, i + len - 1)) return true;
	}
	return false;
}

void maximize(int &a, int b) {
	if (a < b) a = b;
}

void tinhnop() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	Hash.init(a, n);

	int ans = 0;

	int lo = 2, hi = n - n % 2;
	while (hi - lo > 0) {
		int mid = (lo + hi) >> 1;
		if (mid & 1) mid++;
		if (check(mid)) lo = mid;
		else hi = mid - 2;
	}

	maximize(ans, lo);

	lo = 1, hi = n - (n % 2 == 0);
	while (hi - lo > 0) {
		int mid = (lo + hi) >> 1;
		if (!(mid & 1)) mid++;
		if (check(mid)) lo = mid;
		else hi = mid - 2;
	}

	maximize(ans, lo);

	cout << ans;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	tinhnop();

//	cerr << "\n[time] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";
}
