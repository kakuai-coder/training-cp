/*
	Author: kakuai
	created: 2025.07.03 16:20:00
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T> bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T> bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }

#if __cplusplus < 202002L
template <class T> int ssize(const T &a) { return a.size(); }
#endif

const int N = 4e5 + 5;

int bit[N];

void add(int x) {
	for (; x < N; x += x & -x) bit[x]++;
}

int get(int x) {
	int res = 0;
	for (; x > 0; x -= x & -x) res += bit[x];
	return res;
}

void kakuai() {
	int n;
	cin >> n;
	vector<pair<int, int>> seg(n);
	vector<int> pos(2 * n + 1);
	vector<bool> used(2 * n + 1, false);
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		seg[i] = {a, b};
		used[a] = used[b] = true;
	}
	vector<int> free;
	for (int i = 1; i <= 2 * n; i++) {
		if (!used[i]) free.push_back(i);
	}
	int m = ssize(free) / 2;
	for (int i = 0; i < m; i++) {
		seg.push_back({free[i], free[i + m]});
	}
	
	sort(seg.begin(), seg.end());
	
	i64 res = 0;
	for (auto &x : seg) {
		int a = x.first; 
		int b = x.second;
		res += get(b - 1) - get(a);
		add(b);
	}
	cout << res << '\n';
}
 
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "i"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}
	kakuai();
	cerr << "\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
