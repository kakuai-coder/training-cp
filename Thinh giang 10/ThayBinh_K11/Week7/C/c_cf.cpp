#include <bits/stdc++.h>

using namespace std;

#define task "deleg"
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define bit(s, i) (((s) >> (i)) & 1)
#define ii pair<int, int>
#define fi first
#define se second
#define ll long long
#define eb emplace_back
#define pb push_back
#define __builtin_popcount __builtin_popcountll

void solve();

int32_t main() {
    if (fopen(task ".in", "r")) {
        freopen(task ".in", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

const int N = 1e5 + 5;

int n, rem[N], dist;
bool isWrong;
vector<int> adj[N];

void dfs(int u, int p) {
    multiset<int> s;
    for (int v : adj[u]) if (v != p && !isWrong) {
        dfs(v, u);
        s.insert(rem[v] + 1);
    }

    while (s.size() > 2) {
        int t = *s.begin();
        s.erase(s.begin());
        auto it = s.lower_bound(dist - t);
        if (it == s.end()) {
            if (!rem[u] && u != 1) {
                rem[u] = t;
            } else {
                isWrong = true;
                break;
            }
        } else {
            s.erase(it);
        }
    }

    if (sz(s) == 1) {
        if (!rem[u]) {
            rem[u] = *s.begin();
        } else {
            isWrong = true;
        }
    } else if (sz(s) == 2) {
        if (rem[u]) {
            if (*s.begin() + *prev(s.end()) < dist) {
                isWrong = 1;
            }
        } else {
            if (*s.begin() >= dist && u != 1) {
                rem[u] = *prev(s.end());
            } else if (*prev(s.end()) >= dist && u != 1) {
                rem[u] = *s.begin();
            } else {
                if (*s.begin() + *prev(s.end()) < dist) {
                    isWrong = 1;
                }
            }
        }
    }
}

bool chk(int x) {
    memset(rem, 0, sizeof(rem));
    isWrong = 0;
    dist = x;
    dfs(1, 0);
    if ((rem[1] >= dist || rem[1] == 0) && !isWrong) return true;
    return false;
}

void solve() {
    cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; 
        cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }

    // cout << chk(2) << '\n';
    int L = 1, R = n, res = 0;
    while (L <= R) {
        int M = (L + R) >> 1;
        if (chk(M)) {
            L = M + 1;
            res = M;
        } else {
            R = M - 1;
        }
    }

    cout << res << '\n';
}
