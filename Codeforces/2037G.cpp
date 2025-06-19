/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-18
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

typedef long long int64;
typedef unsigned long long uint64;
////////////////////////////////////////

const int maxN = 2e5 + 11;
const int maxV = 1e6 + 11;
const int mod = 998244353;

int n, a[maxN], pre[maxV], dp[maxN];
int min_prime[maxV];

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

void sub(int &a, int b) {
	a -= b;
	if (a < 0) a += mod;
}

void sieve(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (min_prime[i] == 0) {
            for (int j = i * i; j <= n; j += i) {
                if (min_prime[j] == 0) {
                    min_prime[j] = i;
                }
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (min_prime[i] == 0) {
            min_prime[i] = i;
        }
    }
}

int Get(int x) {
	vector<int> res;
	while (x != 1) {
		int c = min_prime[x];
		res.push_back(min_prime[x]);
		while (x % c == 0) {
			x /= c;
		}
	}

	int sz = ssz(res);
	int ret = 0;
	for (int mask = 1; mask < (1 << sz); ++mask) {
		int c_bit = __builtin_popcount(mask);
		int d = 1;
		for (int i = 0; i < sz; ++i) if((mask >> i) & 1) {
			d *= res[i];
		}
		if (c_bit & 1) add(ret, pre[d]);
		else sub(ret, pre[d]);
	}
	return ret;
}

void update(int x, int val) {
	vector<int> res;
	while (x != 1) {
		int c = min_prime[x];
		res.push_back(min_prime[x]);
		while (x % c == 0) {
			x /= c;
		}
	}

	int sz = ssz(res);
	for (int mask = 1; mask < (1 << sz); ++mask) {
		int d = 1;
		for (int i = 0; i < sz; ++i) if((mask >> i) & 1) {
			d *= res[i];
		}
		add(pre[d], val);
	}
}

void tinhnop() {
	sieve(maxV - 1);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (i == 1) dp[1] = 1;
		else dp[i] = Get(a[i]);
		update(a[i], dp[i]);
	}

	cout << dp[n];
}
////////////////////////////////////////
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	tinhnop();
//	cerr << "\n[time] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";
}
