/*
	Author: kakuai
	created: 2025.06.30 14:14:41
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

int m, n, A, B, a[605][605]; 
i64 col[605], sum[605][605];

void sub1() {
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
		}
	}

	i64 ans = (i64) 1e18 + 11; 

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int x = 1; x + i - 1 <= m; ++x) {
				for (int y = 1; y + j - 1 <= n; ++y) {
					int u = i + x - 1; 
					int v = j + y - 1; 

					i64 res = sum[u][v] - sum[u][j - 1] - sum[i - 1][v] + sum[i - 1][j - 1];
					
					minimize(ans, abs(res - A) + abs(res - B));
				}
			}
		}
	}

	cout << ans; 
}

void kakuai() {
	cin >> m >> n >> A >> B; 

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}

	if (m <= 20 && n <= 20) {
		sub1(); 
		return ; 
	}

	if (A > B) swap(A, B); 

	i64 res = 0, ans = (i64)1e18 + 11; 

	for (int row1 = 1; row1 <= m; ++row1) {
		
		for (int i = 1; i <= n; ++i) col[i] = 0; 

		for (int row2 = row1; row2 <= m; ++row2) {
			for (int i = 1; i <= n; ++i) col[i] += a[row2][i];

			i64 sum = 0; 
			int l = 1; 
			for (int r = 1; r <= n; ++r) {
				sum += col[r]; 
				while (sum >= A && l <= r) {
					sum -= col[l]; 
					l++;
				}

				if (sum < A) maximize(res, sum);
			}
		}
	}

	minimize(ans, A + B - 1LL * 2 * res);

	res = (i64) 1e18 + 11;

	for (int row1 = 1; row1 <= m; ++row1) {
		
		for (int i = 1; i <= n; ++i) col[i] = 0; 

		for (int row2 = row1; row2 <= m; ++row2) {
			for (int i = 1; i <= n; ++i) col[i] += a[row2][i];

			i64 sum = 0; 
			int l = 1; 
			for (int r = 1; r <= n; ++r) {
				sum += col[r]; 
				while (sum > B && l <= r) {
					minimize(res, sum);
					sum -= col[l]; 
					l++;
				}
			}
		}
	}

	minimize(ans, 1LL * 2 * res - A - B);
	
	bool ok = false; 

	for (int row1 = 1; row1 <= m; ++row1) {
		
		for (int i = 1; i <= n; ++i) col[i] = 0; 

		for (int row2 = row1; row2 <= m; ++row2) {
			for (int i = 1; i <= n; ++i) col[i] += a[row2][i];

			i64 sum = 0; 
			int l = 1; 
			for (int r = 1; r <= n; ++r) {
				sum += col[r]; 
				while (sum > B && l <= r) {
					sum -= col[l]; 
					l++;
				}

				if (sum >= A) {
					ok = true; 
					break;
				}
			}
		}
	}

	if (ok) minimize(ans, (i64) B - A); 

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "rmindist"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}