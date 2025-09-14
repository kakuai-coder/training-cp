// kakuai ^><^ || cherry  
#include <bits/stdc++.h>
#define task "esque"

using namespace std;

string L, R;

const int MOD = 1e9 + 7, MAXN = 2e5 + 5; 

int submod(int a, int b) {
	a -= b; 
	if (a < 0) a += MOD; 
	return a;
}

int addmod(int a, int b) {
	a += b; 
	if (a >= MOD) a -= MOD; 
	return a;
}

int mulmod(int a, int b) {
	int64_t x = 1LL * a * b; 
	return x % MOD;
}

int powmod(int a, int b) {
	int res = 1; 
	for (; b; b >>= 1, a = mulmod(a, a)) if (b & 1) {
		res = mulmod(res, a);
	}

	return res;
}

int fact[MAXN], ifact[MAXN], pw2[MAXN], pw7[MAXN];

void init(void) {
	fact[0] = 1; 
	pw2[0] = 1; pw7[0] = 1; 

	for (int i = 1; i <= MAXN - 5; ++i) {
		fact[i] = mulmod(fact[i - 1], i);
		pw2[i] = mulmod(pw2[i - 1], 2);
		pw7[i] = mulmod(pw7[i - 1], 7);
	}

	ifact[MAXN - 5] = powmod(fact[MAXN - 5], MOD - 2);

	for (int i = MAXN - 6; ~i; --i) {
		ifact[i] = mulmod(ifact[i + 1], i + 1);
	}
}

int CkN(int k, int n) {
	if (k < 0 || k > n) return 0; 
	return mulmod(mulmod(fact[n], ifact[k]), ifact[n - k]);
}

int calc(string S) {
	
	int n = (int)S.size();

	int ans = 0; 

	for (int len = 2; len < n; len += 2) {
		int k = len / 2; 

		int temp1 = mulmod(mulmod(pw2[k], CkN(k - 1, len - 1)), pw7[len - k]);
		int temp2 = mulmod(mulmod(pw2[k], CkN(k, len - 1)), pw7[len - 1 - k]);
		temp2 = mulmod(6, temp2); 

		ans = addmod(ans, addmod(temp1, temp2));
	}

	
	if (n & 1) return ans; 
	
	int cnt = 0, k = n / 2; 

	for (int i = 0; i < n; ++i) {
		int lim = S[i] - '0'; 

		for (int j = (i == 0 ? 1 : 0); j < lim; ++j) {
			if (j == 4) continue;
			
			int ncnt = cnt + (j == 6 || j == 8); 
			
			int need = k - ncnt; 
			int rem = n - i - 1; 

			if (need < 0 || need > rem) continue;

			int ways = CkN(need, rem);

			ways = mulmod(ways, pw2[need]);
			ways = mulmod(ways, pw7[rem - need]);

			ans = addmod(ans, ways);
		}

		if (lim == 4) return ans; 

		if (lim == 6 || lim == 8) cnt++;
	}

	if (cnt == k) {
		ans++; 
		if (ans >= MOD) ans -= MOD;
	}

	return ans; 
}

bool check(string S) {
	int cnt = 0;
	for (int i = 0; i < (int)S.size(); ++i) {
		int x = S[i] - '0'; 

		if (x == 4) return false; 

		if (x == 6 || x == 8) cnt++;
	}

	int k = ((int)S.size());

	if (k & 1) return false; 

	if (cnt == k / 2) return true; 
	return false; 
}

void solve(void) { 
	cin >> L >> R; 

	init();

	cout << addmod(submod(calc(R), calc(L)), check(L));
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(task ".inp", "r")) {
		freopen(task ".inp", "r", stdin);
		freopen(task ".out", "w", stdout);
	}

	int t = 1; // cin >> t;
	while (t--) {
		solve(); // cout << '\n';
	}
}