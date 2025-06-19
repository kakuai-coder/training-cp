#include <bits/stdc++.h>
using namespace std;
const int BLOCK = 1000;
int n;
int a[200005];

namespace sub1 {

    int b[200005];

    void SOLVE() {

        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            int res = 0;
            for (int j = 1; j <= i; j++) {
                if (a[j] > a[i]) b[j]++;
                else if (a[j] < a[i]) b[j]--;
                res += (b[j] == 0);
            }
            ans += res;
        }

        cout << ans << '\n';

    }

}

namespace sub2 {

    int pos[200005], bit[200005];
    int cnt[205][400005];
    int lazy[205];

    int getblock(int pos) {
        return pos / BLOCK + 1;
    }

    void upd(int pos, int val) {
        int k = getblock(pos);
        for (int i = pos; i <= min(k * BLOCK - 1, n); i++) {
            cnt[k][bit[i] + 200000]--;
            bit[i] += val;
            cnt[k][bit[i] + 200000]++;
        }
        for (int i = k + 1; i <= getblock(n); i++) lazy[i] += val;
    }

    long long get(int pos) {
        long long ans = 0;
        int k = getblock(pos);
        int res = bit[pos] + lazy[k];
        for (int i = pos; i <= min(k * BLOCK - 1, n); i++)
            ans += (bit[i] + lazy[k] == res);
        res += 200000;
        for (int i = k + 1; i <= getblock(n); i++)
            ans += cnt[i][res - lazy[i]];
        return ans;
    }

    void SOLVE() {

        long long ans = 0;
        for (int i = 1; i <= n; i++) pos[a[i]] = i;
        for (int i = 1; i <= n; i++) {
            bit[i] = bit[i - 1] + (a[i] != 1);
            cnt[getblock(i)][bit[i] + 200000]++;
        }
        ans += get(pos[1]);
        for (int i = 2; i <= n; i++) {
            upd(pos[i - 1], -1);
            upd(pos[i], -1);
            ans += get(pos[i]);
        }

        cout << ans << '\n';

    }

}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    sub2::SOLVE();

    return 0;
}