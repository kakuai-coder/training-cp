#include <bits/stdc++.h>
using namespace std;
const int BLOCK = 2154;
int n, q;
long long res;
string s;
int dp[100005], cnt[200005], par[100005];
long long ans[100005];
unordered_map <int, int> p;
int RMQ[100005][17];

int get(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(RMQ[l][k], RMQ[r - (1 << k) + 1][k]);
}

struct ZATA {
    int l, r, id;
} ques[100005];

bool cmp(ZATA A, ZATA B) {
    if (A.l / BLOCK != B.l / BLOCK) return A.l < B.l;
    else return A.r < B.r;
}

int FIND(int u) {
    return par[u] == u ? u : par[u] = FIND(par[u]);
}

void MERGE(int u, int v) {
    u = FIND(u);
    v = FIND(v);
    if (u == v) return;
    if (u > v) swap(u, v);
    par[v] = u;
}

void ADD(int pos) {
    res -= 1LL * cnt[dp[pos]] * (cnt[dp[pos]] - 1) / 2;
    cnt[dp[pos]]++;
    res += 1LL * cnt[dp[pos]] * (cnt[dp[pos]] - 1) / 2;
}

void REMOVE(int pos) {
    res -= 1LL * cnt[dp[pos]] * (cnt[dp[pos]] - 1) / 2;
    cnt[dp[pos]]--;
    res += 1LL * cnt[dp[pos]] * (cnt[dp[pos]] - 1) / 2;
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> s;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> ques[i].l >> ques[i].r;
        ques[i].r++;
        ques[i].id = i;
    }

    n = s.size();
    s = " " + s;
    for (int i = 1; i <= n; i++) {
        dp[i + 1] = dp[i];
        if (s[i] == '(') dp[i + 1]++;
        else dp[i + 1]--;
        RMQ[i + 1][0] = dp[i + 1];
    }
    for (int i = 1; i <= n + 1; i++) par[i] = i;
    for (int k = 1; k <= 16; k++)
    for (int i = 1; i + (1 << k) - 1 <= n + 1; i++)
        RMQ[i][k] = min(RMQ[i][k - 1], RMQ[i + (1 << (k - 1))][k - 1]);
    for (int i = 1; i <= n + 1; i++) {
        int pos = p[dp[i]];
        if (pos) {
            if (get(pos, i) >= dp[i])
                MERGE(pos, i);
        }
        p[dp[i]] = i;
        dp[i] = FIND(i);
    }
    sort(ques + 1, ques + q + 1, cmp);
    int l = 1;
    int r = 0;
    for (int i = 1; i <= q; i++) {
        while (ques[i].r > r) {
            r++;
            ADD(r);
        }
        while (ques[i].l < l) {
            l--;
            ADD(l);
        }
        while (ques[i].l > l) {
					l++;
					REMOVE(l);
        }
        while (ques[i].r < r) {
            r--;
            REMOVE(r);
        }
        ans[ques[i].id] = res;
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';

    return 0;
}