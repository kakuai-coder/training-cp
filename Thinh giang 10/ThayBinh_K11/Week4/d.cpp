/*
	Author: tinhnopro
	created: 2025.04.25 14:47:23
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 5011; 

struct Point {
	int x, y; 

	Point() {
		x = y = 0; 
	}

	Point(int _x, int _y) : x(_x), y(_y) {};
};

int n, w, h; 
int dp[maxN]; 
Point p[maxN];

bool cmp(const Point &a, const Point &b) {
	if (a.x == b.x) return a.y > b.y; 

	return a.x < b.x; 
}

void tinhnop() {
	cin >> n >> w >> h; 
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].x >> p[i].y; 
	}

	sort(p + 1, p + n + 1, cmp);

	int ans = 0; 

	for (int i = 1; i <= n; ++i) {
		dp[i] = 1; 
		for (int j = 1; j < i; ++j) {
			if ((p[j].x +1 == p[i].x && p[j].y == p[i].y) || 
					(p[j].y + 1 == p[i].y && p[j].x == p[i].x) ||
					(p[j].x - 1 == p[i].x && p[j].y == p[i].y) ||
					(p[j].y - 1 == p[i].y && p[j].x == p[i].x)) continue;
			maximize(dp[i], dp[j] + 1); 
		}
		cout << i << ' ' << dp[i] << '\n';
		maximize(ans, dp[i]);
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}