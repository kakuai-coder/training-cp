/*
	Author: tinhnopro
	created: 27.02.2025 10:09:05
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK "nestedrangescount"

using namespace std;

using i64 = long long;

template<typename T> struct Compressor {
	vector<T> h; 

	void add(const T& x) {
		h.push_back(x);
	}

	void Compress() {
		sort(h.begin(), h.end()); 
		h.resize(unique(h.begin(), h.end()) - h.begin());
	}

	int Get(const T& x) {
		return lower_bound(h.begin(), h.end(), x) - h.begin() + 1; 
	}
};

struct Point {
	int x, y, idx; 

	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

const int maxN = 3e5 + 5;

Compressor<int> com; 
int n, sz, ans[maxN], bit[2 * maxN]; 
Point a[maxN]; 

void update(int u, int val) {
	for (; u; u -= u & -u) bit[u] += val;  
}

int query(int u) {
	int res = 0;
	for (; u <= sz; u += u & -u) res += bit[u];
	return res; 
}

void update2(int u, int val) {
	for (; u <= sz; u += u & -u) bit[u] += val;
}

int query2(int u) {
	int res = 0; 
	for (; u; u -= u & -u) res += bit[u];
	return res; 
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].x >> a[i].y; 
		com.add(a[i].x);
		com.add(a[i].y); 
	}

	com.Compress(); 

	for (int i = 1; i <= n; ++i) {
		a[i].x = com.Get(a[i].x); 
		a[i].y = com.Get(a[i].y); 
		a[i].idx = i; 
	}

	sort(a + 1, a + n + 1, [](const Point& a, const Point& b) {
		if (a.y == b.y) return a.x > b.x; 
		return a.y < b.y; 
	});

	// for (int i = 1; i <= n; ++i) cout << a[i].x << ' ' << a[i].y << '\n';

	sz = (int) com.h.size();

	for (int i = 1; i <= n; ++i) {
		ans[a[i].idx] = query(a[i].x); 
		update(a[i].x, 1);
	}
	
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' '; 
	cout << '\n';
	memset(bit, 0, sizeof(bit));

	for (int i = n; i; --i) {
		ans[a[i].idx] = query2(a[i].x); 
		update2(a[i].x, 1);
	}

	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}