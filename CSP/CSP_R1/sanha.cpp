/*
Author: kakuai
created: 28.7.2025
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

const int maxN = 1e5 + 5;
const int Block = 311;

int n, q, a[maxN];

namespace Subtask12 {

	int lab[maxN];

	void init(int l, int r) {
		for (int i = l; i <= r; ++i) {
			lab[i] = -1;
		}
	}

	int findPar(int u) {
		return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
	}

	void joinSet(int u, int v) {
		u = findPar(u);
		v = findPar(v);

		if (u == v) return ;

		if (lab[u] > lab[v]) swap(u, v);

		lab[u] += lab[v];
		lab[v] = u;
	}

	void solve(void) {
		while (q--) {
			int l, r;
			cin >> l >> r;

			vector<int> stk;

			init(l, r);

			for (int i = l; i <= r; ++i) {
				while (!stk.empty() && a[stk.back()] > a[i]) stk.pop_back();

				if (!stk.empty()) {
					if (a[stk.back()] == a[i]) {
						joinSet(stk.back(), i);
					}
				}

				stk.push_back(i);
			}

			int cnt = 0;

			for (int i = l; i <= r; ++i) if (lab[i] < 0) cnt++;

			cout << cnt << '\n';
		}
	}

	bool run(void) {
		if (n > 1000 || q > 1000) return false;
		return solve(), true;
	}
};


int pre[maxN], cntUp[maxN], ans[maxN];
vector<pair<int, int> > quest[maxN];
int bit[maxN];

void update(int id, int val) {
	for (; id <= n; id += id & -id) bit[id] += val;
}

int query(int id) {
	int res = 0;

	for (; id; id -= id & -id) res += bit[id];

	return res;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	vector<int> stk;

	for (int i = 1; i <= n; ++i) {
		while (!stk.empty() && a[stk.back()] > a[i]) stk.pop_back();

		if (!stk.empty()) {
			pre[i] = stk.back();
			cntUp[i] = (a[stk.back()] == a[i] ? 1 : 0);
		} else {
			pre[i] = 0;
			cntUp[i] = 1;
		}
		stk.push_back(i);
	}

	for (int i = 1; i <= q; ++i) {
		int l, r;
		cin >> l >> r;
		quest[r].emplace_back(l, i);
		ans[i] = r - l + 1;
	}

	for (int r = 1; r <= n; ++r) {
		if (pre[r]) update(pre[r], cntUp[r]);

		for (auto &x : quest[r]) {
			int l = x.first;
			int i = x.second;

			ans[i] -= query(r) - query(l - 1);
		}
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "sanha"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
