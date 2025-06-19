#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FOR(i, a, b) for(int i = a; i <= b; i ++)
#define FORD(i, b, a) for(int i = b; i >= a; i --)
#define MASK(o) (1ll << (o))
#define __builtin_popcount __builtin_popcountll
#define C_BIT(mask) __builtin_popcount(mask)
#define BIT(mask, i) ((mask) & (1ll << (i)))
#define ONBIT(mask, i) ((mask) | (1ll << (i)))
#define pb push_back
#define ii pair<int, int>
#define fi first
#define se second

const int maxN = 1e6 + 5;

int n, k;
vector<signed> Edge[maxN];
int A[maxN];
signed pa[maxN];
signed dep[maxN];
int sum = 0;
signed B[maxN];

int rielcin() {
    int res = 0;
    char ch;
    ch = getchar();

    while(true) {
        if ('0' <= ch && ch <= '9' )
        break;

        ch = getchar();
    }

    res = ch - '0';
    while(true) {
        ch = getchar();

        if ('0' > ch || ch>'9')
            break;

        res=res * 10+(ch-'0');
    }

    return res;
}

int cnt = 0;

void dfs(signed u, signed sau) {
    dep[u] = sau;
    ++ cnt;
    for(signed v: Edge[u]) if (v != pa[u]) {
        pa[v] = u;
        dfs(v, sau + 1);
    }
}

int dp[maxN];
bool check(signed x) {
    FOR(i, 1, n)
        dp[i] = A[i];
    signed rem = 0;
    int mx = sum;
    FORD(i, n, 1) {
        if (dp[B[i]] >= x)
            rem ++;
        else {
            dp[pa[B[i]]] += dp[B[i]];
        }
        if (rem == k)
            return true;
    }
    return false;
}

int BS() {
    int l = 0;
    int r = sum / k + 1;
    int res = 0;
    while(l != r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
            res = max(res, mid);
        }
        else
            r = mid;
    }
    return res;
}

int Cnt[maxN];
int head[maxN];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	#define cherry "oliu23split"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

    n = rielcin();
    k = rielcin();
    int i;
    FOR(i, 1, n) {
        A[i] = rielcin();
        sum += A[i];
    }

    FOR(i, 1, n - 1) {
        signed u, v;
        u = rielcin();
        v = rielcin();
        Edge[u].pb(v);
        Edge[v].pb(u);
    }

    dfs(1, 1);

    signed mx = 0;
    FOR(i, 1, n)
        mx = max(mx, dep[i]);

    FOR(i, 1, n)
        Cnt[dep[i]] ++;

    head[1] = 1;
    FOR(i, 2, mx)
        head[i] = head[i - 1] + Cnt[dep[i - 1]];

    FOR(i, 1, n) {
        B[head[dep[i]]] = i;
        head[dep[i]] ++;
    }
    cout << BS();

    return 0;
}