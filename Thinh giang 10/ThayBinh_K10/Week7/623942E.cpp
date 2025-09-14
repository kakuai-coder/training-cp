/*
Author: kakuai
created: 2025.07.23
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
int size32(const T &a) {
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

struct Hash {
	static const int64_t mod1 = 1000000007, mod2 = 1000000009;
	static const int64_t base1 = 91138233, base2 = 97266353;
	int64_t h1 = 0, h2 = 0;

	void add(int x) {
		h1 = (h1 * base1 + x) % mod1;
		h2 = (h2 * base2 + x) % mod2;
	}

	bool operator<(Hash const &o) const {
		return h1 != o.h1 ? h1 < o.h1 : h2 < o.h2;
	}
};


void kakuai(void) {
	// voi26 = winner
	int n;
	cin >> n;
	vector<int> a(n);
	for (int &x : a) cin >> x;

	vector<tuple<int,int,int>> ans;
	for (int k = 1; k <= n; ++k) {
		if (n % k) continue;
		int m = n / k;
		map<Hash,int> cnt;
		for (int i = 0; i < m; ++i) {
			vector<int> b(a.begin() + i*k, a.begin() + (i+1)*k);
			sort(b.begin(), b.end());
			Hash h;
			for (int x : b) h.add(x);
			if (cnt.size() > 2) break;
		}
		if (cnt.size() == 2) {
			auto it = cnt.begin();
			int p = it->second;
			++it;
			int q = it->second;
			if (p < q) swap(p,q);  
			ans.emplace_back(k, p, q);
		}
	}

	if (ans.empty()) {
		cout << -1 << "\n";
	} else {
		cout << ans.size() << "\n";
		for (auto &t : ans) {
			int k,p,q;
			tie(k,p,q) = t;
			cout << k << " " << p << " " << q << "\n";
		}
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry ""
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}