/*
	Author: kakuai
	created: 2025.07.09 10:41:24
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int MOD = 1e9 + 7;
const int maxN = 505;

int n;
char a[maxN][maxN];
int f[2][maxN][maxN];


void kakuai() {
	while (cin >> n && n) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> a[i][j];
			}
		}

		memset(f, 0, sizeof f);
		if (a[1][1] == a[n][n])
			f[0][1][n] = 1;

		for (int step = 1; step < n; ++step) {
			int cur = step & 1, pre = cur ^ 1;
			memset(f[cur], 0, sizeof f[cur]);

			int x1_lo = max(1, step + 2 - n);
			int x1_hi = min(n, step + 1);
			for (int x1 = x1_lo; x1 <= x1_hi; ++x1) {
				int y1 = step - x1 + 2;
				int x2_max = min(n, 2*n - step - y1);
				int x2_lo = max(1, n - step);
				if (x2_lo > x2_max) continue;
				for (int x2 = x2_lo; x2 <= x2_max; ++x2) {
					int y2 = 2*n - step - x2;
					if (a[x1][y1] != a[x2][y2]) continue;
					int &val = f[cur][x1][x2];
					i64 sum = 0;
					int px1 = x1 - 1, py1 = y1;
					int px2 = x2 + 1, py2 = y2;
					if (px1>=1 && py1>=1 && px2<=n && py2<=n)
							sum += f[pre][px1][px2];
					px1 = x1 - 1; py1 = y1;
					px2 = x2;     py2 = y2 + 1;
					if (px1>=1 && py1>=1 && py2<=n)
							sum += f[pre][px1][px2];
					px1 = x1;     py1 = y1 - 1;
					px2 = x2 + 1; py2 = y2;
					if (py1>=1 && px2<=n && py2<=n)
							sum += f[pre][px1][px2];
					px1 = x1;     py1 = y1 - 1;
					px2 = x2;     py2 = y2 + 1;
					if (py1>=1 && py2<=n)
							sum += f[pre][px1][px2];

					val = sum % MOD;
				}
			}
	}

	i64 res = 0;
	int cur = (n - 1) & 1;

	int x1_lo = max(1, n - (n - 1) + 1 - n + 2); 
	int x1_hi = n;
	for (int x1 = 1; x1 <= n; ++x1) {
			int y1 = n - x1 + 1;
			int x2_lo = max(1, n - (n - 1)); 
			int x2_max = min(n, 2*n - (n - 1) - y1);
			for (int x2 = 1; x2 <= n; ++x2) {
					int y2 = n - x2 + 1;
					if (abs(x1 - x2) + abs(y1 - y2) <= 1) res = (res + f[cur][x1][x2]) % MOD;
			}
	}

		cout << res << '\n';
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}