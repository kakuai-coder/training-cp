/*
Author: kakuai
created: 2025.07.19
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

const int maxN = 2e5 + 5; 
const int Log = 20; 

int n, q; 
int a[maxN];

namespace subtask12 {

	int st[Log + 1][maxN];

	int Get(int l, int r) {
		int k = __lg(r - l + 1); 
		return __gcd(st[k][l], st[k][r - (1 << k) + 1]);
	}

	void solve(void) {

		for (int i = 1; i <= n; ++i) {
			st[0][i] = a[i];
		}

		for (int j = 1; j <= Log; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
			}
		}

		while (q--) {
			int l, r, x; 
			cin >> l >> r >> x;
			long long ans = 0;  
			for (int u = l; u <= r; ++u) {
				int lo = u - 1, hi = r + 1; 

				while (hi - lo > 1) {
					int mid = (lo + hi) / 2;

					if (Get(u, mid) >= x) {
						lo = mid; 
					} else hi = mid; 
				}
				// cerr << u << ' ' << lo << '\n';

				int d = lo - u + 1; 
				ans += d;
			}

			cout << ans << '\n';
		}
	}
};

void kakuai(void) {
	// voi26 = winner
	cin >> n >> q; 
	
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	subtask12::solve();
	
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "gcd"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}