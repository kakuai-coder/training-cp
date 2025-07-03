/*
  Author: kakuai
  created: 2025.07.03 08:30:27
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

const int MaxN = 1e5 + 5;
const int Base1 = 1e5 + 3, Base2 = 1e5 + 7;
const i64 MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;

int n, m, a[MaxN], b[MaxN];
i64 pw1[MaxN], pw2[MaxN];
set<pair<i64, i64>> s;

bool check(int k) {
	i64 ha1 = 0, ha2 = 0, hb1 = 0, hb2 = 0;
	s.clear();

	for (int i = 1; i <= k; ++i) {
		ha1 = (ha1 + 1LL * a[i] * pw1[a[i]] % MOD1) % MOD1;
		ha2 = (ha2 + 1LL * a[i] * pw2[a[i]] % MOD2) % MOD2;

		hb1 = (hb1 + 1LL * b[i] * pw1[b[i]] % MOD1) % MOD1;
		hb2 = (hb2 + 1LL * b[i] * pw2[b[i]] % MOD2) % MOD2;
	}

	s.insert({ha1, ha2});
	if (ha1 == hb1 && ha2 == hb2) return true;

	for (int i = k + 1; i <= n; ++i) {
		ha1 = (ha1 - 1LL * a[i - k] * pw1[a[i - k]] % MOD1 + MOD1) % MOD1;
		ha1 = (ha1 + 1LL * a[i] * pw1[a[i]] % MOD1) % MOD1;

		ha2 = (ha2 - 1LL * a[i - k] * pw2[a[i - k]] % MOD2 + MOD2) % MOD2;
		ha2 = (ha2 + 1LL * a[i] * pw2[a[i]] % MOD2) % MOD2;

		s.insert({ha1, ha2});
	}

	for (int i = k + 1; i <= m; ++i) {
		hb1 = (hb1 - 1LL * b[i - k] * pw1[b[i - k]] % MOD1 + MOD1) % MOD1;
		hb1 = (hb1 + 1LL * b[i] * pw1[b[i]] % MOD1) % MOD1;

		hb2 = (hb2 - 1LL * b[i - k] * pw2[b[i - k]] % MOD2 + MOD2) % MOD2;
		hb2 = (hb2 + 1LL * b[i] * pw2[b[i]] % MOD2) % MOD2;

		if (s.count({hb1, hb2})) return true;
	}

	return false;
}

void kakuai() {
	cin >> n >> m;

	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];

	pw1[0] = pw2[0] = 1;
	for (int i = 1; i < MaxN; ++i) {
		pw1[i] = pw1[i - 1] * Base1 % MOD1;
		pw2[i] = pw2[i - 1] * Base2 % MOD2;
	}

	for (int k = min(m, n); k >= 1; --k) {
		if (check(k)) {
			cout << k;
			return;
		}
	}

	cout << -1;
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "psubseq"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	kakuai();

	cerr << "\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
