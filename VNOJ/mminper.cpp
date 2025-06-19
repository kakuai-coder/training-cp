/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-15
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef tinhnop_local
#include "D:\Tinhnopro\header\debug.h"
#else
#define debug(...) 0
#endif // tinhnop_local

#define ALL(v) (v).begin(), (v).end()
#define ssize(s) ((signed) (s).size())

const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int bit[N], nxt[N];
int n, m;

void update(int i) {
    for (; i <= n; i += i & -i)
        ++bit[i];
}

int prefixSum(int i) {
    int ans = 0;
    for (; i; i -= i & -i)
        ans += bit[i];
    return ans;
}

int getNext(int i) {
    if (nxt[i] < i) return nxt[i];
    return nxt[i] = getNext(nxt[i] + (nxt[i] == i));
}

void solve() {
    for (int i = 1; i <= n + 1; ++i) bit[i] = 0, nxt[i] = i - 1;
    int invCnt = 0;
    vector<int> a;
    for (int i = 1; i <= n; ++i) {
        int maxBuff = (long long)(n - i) * (n - i - 1) / 2;
        int l = 1, r = n, v = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            int pos = getNext(mid) + 1;
            if (pos > n) {
                r = mid - 1;
                continue;
            }
            int more = pos - 1 - prefixSum(pos);
            if (invCnt + maxBuff + more >= m)
                v = pos, r = mid - 1;
            else
                l = mid + 1;
        }
        a.push_back(v);
        invCnt += v - 1 - prefixSum(v);
        update(v);
        nxt[v] = v;
    }
    int res = 0, pw2 = 1;
    for (int i = 0; i < ssize(a); ++i) {
        res += 1LL * a[i] * pw2 % mod;
        pw2 = 1LL * pw2 * 2 % mod;
        if (res >= mod) res -= mod;
    }
    cout << res << '\n';
}

void tinhnop() {
    int t; cin >> t;
	while(t--) {
        cin >> n >> m;
		solve();
	}
}
///////////////////////////////////////////
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	freopen("mminper.inp", "r", stdin);
	freopen("mminper.out", "w", stdout);
///////////////////////////////////////////
	tinhnop();
//	cerr << "\n[time] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";
	return 0;
}
