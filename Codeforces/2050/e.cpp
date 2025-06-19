/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-05
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

template <typename T, int D>
struct vec : public vector<vec<T, D - 1>> {
	static_assert(D >= 1, "Init Error");
	template <typename... Args>
	vec(int n = 0, Args... args) : vector<vec<T, D - 1>>(n, vec<T, D - 1>(args...)) {}
};

template <typename T>
struct vec<T, 1> : public vector<T> {
	vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};

int f[1005][1005];
int n, m;
string a, b, c;

int calc(int i, int j){
	if (i > n || j > m)
		return 1e9;
	if (i == n && j == m)
		return 0;
	if (f[i][j] != -1)
		return f[i][j];

	int cur = 1e9;

	int vitri = i + j;

	int s1 = calc(i + 1, j);

	if (a[i] != c[vitri])
		s1 ++;

	cur = min(cur, s1);

	int s2 = calc(i, j + 1);
	if (b[j] != c[vitri])
		s2 ++;

	cur = min(cur, s2);

	return f[i][j] = cur;
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {
		cin >> a >> b >> c;
		n = a.size();
		m = b.size();

		for (int i = 0; i <= n; i ++)
			for (int j = 0; j <= m; j ++)
				f[i][j] = -1;

		cout << calc(0, 0) << '\n';
	}
}

