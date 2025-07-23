#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

long long modpow(long long a, long long b){
	long long r = 1;
	while(b){
		if(b & 1) r = r * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return r;
}

main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	const int MAXB = 30;
	int basis[MAXB];
	memset(basis, 0, sizeof(basis));
	int r = 0;

	for(int v : a){
		int x = v;
		for(int b = MAXB - 1; b >= 0; b--){
			if(!(x & (1 << b))) continue;
			if(!basis[b]){
				basis[b] = x;
				r++;
				break;
			}
			x ^= basis[b];
		}
	}

	long long t = modpow(2, n - r);

	long long term1 = (modpow(2, r) + MOD - 1) % MOD;
	long long term2 = t * t % MOD;
	long long term3 = (t + MOD - 1) % MOD;
	long long ans = (term1 * term2 + term3 * term3) % MOD;

	cout << ans << "\n";
	return 0;
}