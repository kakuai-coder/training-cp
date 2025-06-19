/*
	Author: tinhnopro
	created: 04.04.2025 15:26:16
*/
#include <bits/stdc++.h>

#define CHERRY ""

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 

int n, k, a[maxN]; 

struct Ckn {
	static const int MAXN = 1e5 + 1000;
	static const int	MOD = 1e9 + 7;

	long long fac[MAXN + 1000], ifac[MAXN + 1000];

	long long POW(long long A, long long N) { if (N == 0) return 1; if (N == 1) return A % MOD; long long tmp = POW(A, N / 2); if (N % 2) return (tmp * tmp % MOD * A) % MOD; else return (tmp * tmp) % MOD;}

	void PRE(int N) {
			fac[0] = 1;
			for (int i = 1; i <= N; ++i)
					fac[i] = (1ll * i * fac[i - 1]) % MOD;

			ifac[N - 1] = POW(fac[N - 1], MOD - 2);

			for (int i = N - 2; i >= 0; --i)
					ifac[i] = (1ll * (i + 1) * ifac[i + 1]) % MOD;
	}

	long long CALC(long long r, long long n){
			return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
	}
} Ckn;

const int mod = 1e9 + 7; 

void solve() { 
	cin >> n >> k; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}	

	sort(a + 1, a + n + 1); 
	Ckn.PRE(n); 

	int ans = 0; 

	for (int i = k; i <= n; ++i) {
		ans += 1LL * Ckn.CALC(k - 1, i - 1) * a[i] % mod; 
		ans %= mod; 
	}

	cout << ans; 

	return void(cout << '\n');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t;

	for (int i = 1; i <= t; ++i) {
		cerr << "Case #" << i << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}