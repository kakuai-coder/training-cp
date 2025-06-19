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

const int maxN = 5e5 + 5;
int m, n, X, Y;

namespace SUB1 {
    vector<vector<int>> A;
    const int MOD = 1e9 + 7;
    int mp[maxN + 10];
    set<int> S;

    void addCol(int u, int x, int c) {
        FOR(i, u, x) {
            int val = A[i][c];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]++;
                if (mp[val] == 1) {
                    S.erase(val);
                }
            }
        }
    }

    void delCol(int u, int x, int c) {
        FOR(i, u, x) {
            int val = A[i][c];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]--;
                if (mp[val] == 0) {
                    S.insert(val);
                }
            }
        }
    }

    void addRow(int r, int v, int y) {
        FOR(j, v, y) {
            int val = A[r][j];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]++;
                if (mp[val] == 1) {
                    S.erase(val);
                }
            }
        }
    }

    void delRow(int r, int v, int y) {
        FOR(j, v, y) {
            int val = A[r][j];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]--;
                if (mp[val] == 0) {
                    S.insert(val);
                }
            }
        }
    }

    int BS() {
        return *(S.begin());
    }

    void SOLVE() {
        A.resize(m + 3, vector<int>(n + 3));

        FOR(i, 1, m)
            FOR(j, 1, n)
                cin >> A[i][j];

        if (X > Y) {
            vector<vector<int>> B = A;
            A.clear();
            A.resize(n + 3, vector<int>(m + 3));
            FOR(i, 1, m)
                FOR(j, 1, n)
                    A[j][i] = B[i][j];
            swap(m, n);
            swap(X, Y);
        }

        int lim = X * Y + 1;
        FOR(i, 1, lim) {
            S.insert(i);
        }

        int u = 1, v = 1;
        int x = X, y = Y;
        FOR(i, u, x) {
            addRow(i, v, y);
        }

        int res = BS();
        int maxRowStart = m - X + 1;
        for (int row = 1; row <= maxRowStart; row++) {
            if (row > 1) {
                delRow(row-1, v, y);
                addRow(row+X-1, v, y);
                u = row; x = row + X - 1;
                res = (res * BS()) % MOD;
            }
            if ((row % 2) == 1) {
                while (v < n - Y + 1) {
                    delCol(u, x, v);
                    addCol(u, x, v + Y);
                    v++;
                    y = v + Y - 1;
                    res = (res * BS()) % MOD;
                }
            } else {
                while (v > 1) {
                    delCol(u, x, v + Y - 1);
                    addCol(u, x, v - 1);
                    v--;
                    y = v + Y - 1;
                    res = (res * BS()) % MOD;
                }
            }
        }

        cout << res;
    }
}

namespace SUB2 {
    int A[634][634];
    const int MOD = 1e9 + 7;
    int mp[maxN + 10];
    set<int> S;

    void addCol(int u, int x, int c) {
        FOR(i, u, x) {
            int val = A[i][c];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]++;
                if (mp[val] == 1) {
                    S.erase(val);
                }
            }
        }
    }

    void delCol(int u, int x, int c) {
        FOR(i, u, x) {
            int val = A[i][c];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]--;
                if (mp[val] == 0) {
                    S.insert(val);
                }
            }
        }
    }

    void addRow(int r, int v, int y) {
        FOR(j, v, y) {
            int val = A[r][j];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]++;
                if (mp[val] == 1) {
                    S.erase(val);
                }
            }
        }
    }

    void delRow(int r, int v, int y) {
        FOR(j, v, y) {
            int val = A[r][j];
            int lim = X * Y + 1;
            if (val <= lim) {
                mp[val]--;
                if (mp[val] == 0) {
                    S.insert(val);
                }
            }
        }
    }

    int BS() {
        return *(S.begin());
    }

    void SOLVE() {
        FOR(i, 1, m)
            FOR(j, 1, n)
                cin >> A[i][j];

        int lim = X * Y + 1;
        FOR(i, 1, lim) {
            S.insert(i);
        }

        int u = 1, v = 1;
        int x = X, y = Y;
        FOR(i, u, x) {
            addRow(i, v, y);
        }

        int res = BS();
        int maxRowStart = m - X + 1;
        for (int row = 1; row <= maxRowStart; row++) {
            if (row > 1) {
                delRow(row-1, v, y);
                addRow(row+X-1, v, y);
                u = row; x = row + X - 1;
                res = (res * BS()) % MOD;
            }
            if ((row % 2) == 1) {
                while (v < n - Y + 1) {
                    delCol(u, x, v);
                    addCol(u, x, v + Y);
                    v++;
                    y = v + Y - 1;
                    res = (res * BS()) % MOD;
                }
            } else {
                while (v > 1) {
                    delCol(u, x, v + Y - 1);
                    addCol(u, x, v - 1);
                    v--;
                    y = v + Y - 1;
                    res = (res * BS()) % MOD;
                }
            }
        }

        cout << res;
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> m >> n >> X >> Y;

    if (m <= 630 && n <= 630)
        SUB2::SOLVE();
    else
        SUB1::SOLVE();

    return 0;
}