/*
	Author: kakuai
	created: 2025.07.03 10:30:00
*/
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif

struct BIT {
    vector<int> bit;
    int n;
    void init(int _n) {
        n = _n;
        bit.assign(n+1, 0);
    }
    void update(int i) {
        for (; i <= n; i += i & -i)
            bit[i]++;
    }
    int findKth(int k) {
        int pos = 0;
        for (int pw = 1<<20; pw; pw >>= 1) {
            if (pos + pw <= n && bit[pos+pw] < k) {
                pos += pw;
                k -= bit[pos];
            }
        }
        return pos+1;
    }
};

int n;
i64 w, h;
vector<pair<i64,i64>> trees;

// return minimal corner area containing half trees
i64 solve_corner(const vector<pair<i64,i64>>& pts) {
    int half = n / 2;
    vector<pair<i64,i64>> a = pts;
    sort(a.begin(), a.end(), [](auto &a, auto &b){ return a.first < b.first; });
    vector<i64> ys;
    ys.reserve(n);
    for (auto &p : a) ys.push_back(p.second);
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());

    BIT bit;
    bit.init((int)ys.size());

    i64 min_area = LLONG_MAX;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int yid = int(lower_bound(ys.begin(), ys.end(), a[i].second) - ys.begin()) + 1;
        bit.update(yid);
        ++cnt;
        if (cnt < half) continue;
        i64 xval = a[i].first;
        int kth = bit.findKth(half);
        i64 yval = ys[kth - 1];
        minimize(min_area, xval * yval);
    }
    return min_area;
}

void kakuai() {
    cin >> n >> h >> w; // h = height (rows), w = width (cols)
    if (n % 2 != 0) {
        cout << -1;
        return;
    }

    trees.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> trees[i].first >> trees[i].second;

    i64 total = w * h;
    i64 best_min_area = LLONG_MAX;
    vector<pair<i64,i64>> tmp;

    // 4 corner orientations
    tmp = trees;
    minimize(best_min_area, solve_corner(tmp));

    tmp = trees;
    for (auto &p : tmp) p.first = w - p.first + 1;
    minimize(best_min_area, solve_corner(tmp));

    tmp = trees;
    for (auto &p : tmp) p.second = h - p.second + 1;
    minimize(best_min_area, solve_corner(tmp));

    tmp = trees;
    for (auto &p : tmp) {
        p.first = w - p.first + 1;
        p.second = h - p.second + 1;
    }
    minimize(best_min_area, solve_corner(tmp));

    if (best_min_area == LLONG_MAX) cout << -1;
    else cout << (total - best_min_area);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #define cherry "qfarm"
    if (fopen(cherry ".inp", "r")) {
        freopen(cherry ".inp", "r", stdin);
        freopen(cherry ".out", "w", stdout);
    }

    kakuai();
    cerr << "\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
    return 0;
}
