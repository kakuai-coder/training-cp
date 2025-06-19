#include <bits/stdc++.h>
using namespace std;
const int oo = 1e9 + 7;
const long long ooo = 1e18 + 7;
int n, k;
int h[100105], w[100105];

namespace sub1 {

    long long dp[100105];

    void SOLVE() {

        for (int i = 1; i <= n; i++) dp[i] = ooo;
        int sum = 0;
        int j = 1;
        for (int i = 1; i <= n; i++) {
            sum += w[i];
            while (sum > k) {
                sum -= w[j];
                j++;
            }
            int res = -oo;
            for (int l = i; l >= j; l--) {
                res = max(res, h[l]);
                dp[i] = min(dp[i], dp[l - 1] + res);
            }
        }

        cout << dp[n] << '\n';

    }

}

bool checksub2() {
    for (int i = 1; i < n; i++) if (h[i + 1] < h[i]) return false;
    return true;
}

namespace sub2 {

    long long st[4 * 100105];

    void upd(int id, int l, int r, int pos, long long val) {
        if (l > pos || r < pos) return;
        if (l >= pos && r <= pos) {
            st[id] = val;
            return;
        }
        int mid = (l + r) / 2;
        upd(id * 2, l, mid, pos, val);
        upd(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = min(st[id * 2], st[id * 2 + 1]);
    }

    long long get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return ooo;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        return min(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }

    void SOLVE() {


        int j = 1;
        long long sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += w[i];
            while (sum > k) {
                sum -= w[j];
                j++;
            }
            long long res = get(1, 0, n, j - 1, i - 1);
            upd(1, 0, n, i, res + h[i]);
        }

        cout << get(1, 0, n, n, n) << '\n';

    }

}

namespace sub3 {

    long long st[4 * 100105], lazy[4 * 100105];

    void down(int id, int l, int r) {
        if (l != r && lazy[id]) {
            st[id * 2] += lazy[id];
            st[id * 2 + 1] += lazy[id];
            lazy[id * 2] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
        }
        lazy[id] = 0;
    }

    void upd(int id, int l, int r, int u, int v, long long val) {
        if (l > v || r < u) return;
        down(id, l, r);
        if (l >= u && r <= v) {
            st[id] += val;
            lazy[id] += val;
            return;
        }
        int mid = (l + r) / 2;
        upd(id * 2, l, mid, u, v, val);
        upd(id * 2 + 1, mid + 1, r, u, v, val);
        st[id] = min(st[id * 2], st[id * 2 + 1]);
    }

    long long get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return ooo;
        down(id, l, r);
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        return min(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }

    void SOLVE() {

        for (int i = 0; i <= 4 * (n + 15); i++) st[i] = lazy[i] = 0;
        int j = 1;
        long long sum = 0;
        stack <int> st;
        st.push(0);
        for (int i = 1; i <= n; i++) {
            sum += w[i];
            while (sum > k) {
                sum -= w[j];
                j++;
            }
            while (st.size() > 1 && h[st.top()] <= h[i]) {
                int pos = st.top();
                st.pop();
                upd(1, 0, n, st.top(), pos - 1, -h[pos]);
            }
            upd(1, 0, n, st.top(), i - 1, h[i]);
            long long res = get(1, 0, n, j - 1, i - 1);
            upd(1, 0, n, i, i, res);
            st.push(i);
        }

        cout << get(1, 0, n, n, n) << '\n';

    }

}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int test;
    cin >> test;

    while (test--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> h[i] >> w[i];

        sub3::SOLVE();

    }

    return 0;
}