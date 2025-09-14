/*
Author: kakuai
created: 10.8.2025
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int ssz(const T &a) {
	return (int)a.size();
}

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
	static_assert(D >= 1, "Error");
	template <typename... Args>
	Vec(int n = 0, Args... args)
		: vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};
template <typename T>
struct Vec<T, 1> : public vector<T> {
	Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};
}  // namespace std

#define int long long

struct Item {
	long long u, s, y;
};

void kakuai() {
	int n; cin >> n;
	string a, b; cin >> a >> b;
	vector<int> sa(n+1,0), sb(n+1,0);

	for (int i = 1; i <= n; ++i) sa[i] = sa[i-1] + (a[i-1] == '1');
	for (int i = 1; i <= n; ++i) sb[i] = sb[i-1] + (b[i-1] == '1');

	vector<Item> v;

	for (int y = 1; y <= n; ++y) {
		int u = 2*sb[y] - y;
		v.push_back({u, sb[y], y});
	}

	sort(v.begin(), v.end(), [](const Item &A, const Item &B){
		if (A.u != B.u) return A.u < B.u;
		return A.y < B.y;
	});

	vector<int> ps(n+1,0), py(n+1,0), uv(n);

	for (int i = 1; i <= n; ++i) {
		ps[i] = ps[i-1] + v[i-1].s;
		py[i] = py[i-1] + (v[i-1].y - v[i-1].s);
		uv[i-1] = v[i-1].u;
	}

	int tot_py = py[n];

	long long ans = 0;

	for (int x = 1; x <= n; ++x) {
		int t = sa[x];
		int C = x - 2*t;
		int k = upper_bound(uv.begin(), uv.end(), C) - uv.begin();
		int s1 = k*t + ps[k];
		int rem = tot_py - py[k];
		int s2 = (n - k) * (x - t) + rem;
		ans += s1 + s2;
	}

	cout << ans << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "f"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
