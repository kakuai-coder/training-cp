#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+7;
int n, r, a[N];
long long pref[N];

namespace sub2 {
    long long dp[N];
    long long solve() {
        if (n == r) {
            return pref[n];
        }
        memset(dp, -0x3f, (n+1) * sizeof(long long));
        long long res = LLONG_MIN;
        for (int i = 0; i <= r; ++i) {
            dp[i] = 0;
        }
        for (int i = r+1; i <= n; ++i) {
            dp[i] = pref[i];
            for (int j = i == n ? i-r : i-r*2; j > 1; --j) {
                dp[i] = max(dp[i], pref[i]-pref[j-1] + dp[j-1]);
            }
            res = max(res, dp[i]);
            dp[i] = max(dp[i], dp[i-1]);
        }
        return res;
    }
}

namespace sub3 {
    long long dp[N];
    long long solve() {
        if (n == r) {
            return pref[n];
        }
        memset(dp, -0x3f, (n+1) * sizeof(long long));
        long long res = LLONG_MIN;
        long long mx = 0;
        dp[0] = 0;
        for (int i = 0; i <= r; ++i) {
            dp[i] = 0;
        }
        for (int i = r+1; i <= n; ++i) {
            if (i < n) {
                dp[i] = pref[i] + mx;
            } else {
                for (int j = i-r; j >= 1; --j) {
                    dp[i] = max(dp[i], pref[i] - pref[j-1] + dp[j-1]);
                }
            }
            res = max(res, dp[i]);
            dp[i] = max(dp[i], dp[i-1]);
            if (i-r*2 >= 1) {
                mx = max(mx, dp[i-r*2]-pref[i-r*2]);
            }
        }
        // for (int i = 1; i <= n; ++i) cout << dp[i] << ' ';
        return res;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("Bowling.inp", "r", stdin); 
    freopen("Bowling.ans", "w", stdout);

    cin >> n >> r;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }
    cout << sub3::solve();

    return 0;
}