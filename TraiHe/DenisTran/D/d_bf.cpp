#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[200005], child[200005];
int dp[200005][5];
bool vs[1005];
int pre[1005];
vector <int> g[200005];
vector <int> vt, nxt;

void DFS(int u, int parent) {
    child[u] = a[u];
    for (auto v : g[u]) {
        if (v == parent) continue;
        DFS(v, u);
        child[u] = __gcd(child[u], child[v]);
    }
}

int solve(int u, int parent, int ok, int val) {
    if (dp[u][ok] != -1) return dp[u][ok];
    int cur = 0;
    for (auto v : g[u]) {
        if (v == parent) continue;

    }
    if (cur > k) cur = k + 1;
    return dp[u][ok] = cur;
}

void build() {
    for (int i = 1; i <= 1000; i++) {
        for (int j = sqrt(i); j <= i; j++) {
            if (j * j % i == 0) {
                pre[i] = j;
                break;
            }
        }
    }
}

int solve(int u, int parent, int cnt) {
    if (cnt >= nxt.size()) return k + 1;
    if (dp[u][cnt] != -1) return dp[u][cnt];
    int cur = 0;
    int res = 0;
    for (auto v : g[u]) {
        if (v == parent) continue;
        cur += solve(v, u, cnt);
        res += solve(v, u, cnt + 1);
    }
    if (a[u] % nxt[cnt]) cur = k + 1;
    if (cnt + 1 >= nxt.size() || a[u] % nxt[cnt + 1]) res = k + 1;
    else res++;
//    cout << u << " " << parent << " " << cnt << " " << nxt[cnt] << " " << cur << " " << res << '\n';
    if (u != 1)
        cur = min(cur, res);
    if (cur > k) cur = k + 1;
    return dp[u][cnt] = cur;
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

	#define cherry "d"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

    cin >> n >> k;
    k--;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 1;
    DFS(1, 0);
    int val = child[1];
    int i = 2;
    while (i <= sqrt(val)) {
        if (val % i == 0) vt.push_back(i);
        while (val % i == 0)
            val /= i;
        i++;
    }
    if (val != 1) vt.push_back(val);
    vs[child[1]] = true;
    build();
    for (int i = 1; i <= a[1]; i++) {
        if (vs[i]) {
            for (auto res : vt)
                if (i * res <= a[1]) vs[i * res] = true;
            memset(dp, -1, sizeof(dp));
            int j = i;
            nxt.clear();
            nxt.push_back(j);
            while (j != pre[j]) {
                j = pre[j];
                nxt.push_back(j);
            }
            if (solve(1, 0, 0) <= k)
                ans = max(ans, i);
//            for (int i = 1; i <= n; i++)
//            for (int j = 0; j < nxt.size(); j++) {
//                cout << i << " " << nxt[j] << " " << dp[i][j] << '\n';
//            }
        }
    }

    cout << ans * a[1] << '\n';

    return 0;
}