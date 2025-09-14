#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 5;

int n;
int64_t a[maxN];  // Cho phép âm
vector<int64_t> v;

struct Data {
    int64_t cnt;
    int64_t sum_idx;
    int64_t sum_val;
    int64_t sum_prod;
    Data() : cnt(0), sum_idx(0), sum_val(0), sum_prod(0) {}
};

struct fenwicktree {
    Data bit[maxN];

    void update1(int idx, int64_t val_idx, int64_t val_val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx].cnt++;
            bit[idx].sum_idx += val_idx;
            bit[idx].sum_val += val_val;
            bit[idx].sum_prod += val_val * val_idx;
        }
    }

    void update2(int idx, int64_t val_idx, int64_t val_val) {
        for (; idx; idx -= idx & -idx) {
            bit[idx].cnt++;
            bit[idx].sum_idx += val_idx;
            bit[idx].sum_val += val_val;
            bit[idx].sum_prod += val_val * val_idx;
        }
    }

    Data query1(int idx) {
        Data res;
        for (; idx; idx -= idx & -idx) {
            res.cnt += bit[idx].cnt;
            res.sum_idx += bit[idx].sum_idx;
            res.sum_val += bit[idx].sum_val;
            res.sum_prod += bit[idx].sum_prod;
        }
        return res;
    }

    Data query2(int idx) {
        Data res;
        for (; idx <= n; idx += idx & -idx) {
            res.cnt += bit[idx].cnt;
            res.sum_idx += bit[idx].sum_idx;
            res.sum_val += bit[idx].sum_val;
            res.sum_prod += bit[idx].sum_prod;
        }
        return res;
    }
};

fenwicktree bitL, bitR, bitLL, bitRR;
int b[maxN];
__int128 ans[maxN];

// Hàm in __int128_t chính xác
void print128(__int128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string res;
    while (x > 0) {
        res += '0' + (x % 10);
        x /= 10;
    }
    reverse(res.begin(), res.end());
    cout << res;
}

void solve() {
    for (int i = 1; i <= n; ++i) v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for (int i = 1; i <= n; ++i) {
        b[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    for (int i = 1; i <= n; ++i) {
        int64_t val_idx = i;
        int64_t val_val = v[b[i] - 1];

        bitL.update1(b[i], val_idx, val_val);
        bitLL.update2(b[i], val_idx, val_val);

        Data x = bitL.query1(b[i]);
        ans[i] += (__int128)a[i] * i * x.cnt;
        ans[i] += (__int128)x.sum_prod;
        ans[i] -= (__int128)a[i] * x.sum_idx;
        ans[i] -= (__int128)i * x.sum_val;

        x = bitLL.query2(b[i] + 1);
        ans[i] -= (__int128)a[i] * i * x.cnt;
        ans[i] -= (__int128)x.sum_prod;
        ans[i] += (__int128)a[i] * x.sum_idx;
        ans[i] += (__int128)i * x.sum_val;
    }

    for (int i = n; i >= 1; --i) {
        int64_t val_idx = i;
        int64_t val_val = v[b[i] - 1];

        bitR.update2(b[i], val_idx, val_val);
        bitRR.update1(b[i], val_idx, val_val);

        Data x = bitR.query2(b[i]);
        ans[i] += (__int128)a[i] * i * x.cnt;
        ans[i] += (__int128)x.sum_prod;
        ans[i] -= (__int128)a[i] * x.sum_idx;
        ans[i] -= (__int128)i * x.sum_val;

        x = bitRR.query1(b[i] - 1);
        ans[i] -= (__int128)a[i] * i * x.cnt;
        ans[i] -= (__int128)x.sum_prod;
        ans[i] += (__int128)a[i] * x.sum_idx;
        ans[i] += (__int128)i * x.sum_val;
    }

    for (int i = 1; i <= n; ++i) {
        print128(ans[i]);
        cout << ' ';
    }
    cout << '\n';
}

void kakuai() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    solve();
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#define cherry ""
    if (fopen(cherry ".inp", "r")) {
        freopen(cherry ".inp", "r", stdin);
        freopen(cherry ".out", "w", stdout);
    }

    kakuai();
    return 0;
}
