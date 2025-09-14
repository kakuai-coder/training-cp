/*
Author: kakuai
created: 30.7.2025
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

#define int long long

const int maxN = 2e5 + 5;
const int Log = 20;

int n, q, a[maxN], st[Log + 1][maxN];
int ans[maxN], bit[maxN], idx[maxN];

struct Segment {
	int l, r, val;

	Segment(int _l = 0, int _r = 0, int _val = 0) : l(_l), r(_r), val(_val) {}
};

struct query_t {
	int l, r, d, id;

	query_t(int _l = 0, int _r = 0, int _d = 0, int _id = 0) : l(_l), r(_r), d(_d), id(_id) {}
};

int getGcd(int l, int r) {
	int k = __lg(r - l + 1);

	return __gcd(st[k][l], st[k][r - (1 << k) + 1]);
}

int getSum(int x) {
	return x * (x - 1) / 2;
}

void update(int id, int val) {
	for (; id <= n; id += id &-id) bit[id] += val;
}

int query(int id) {
	int res = 0;

	for (; id; id -= id & -id) res += bit[id];

	return res;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i <= n; ++i) {
		st[0][i] = a[i];
	}

	for (int j = 1; j <= Log; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		}
	}

	vector<Segment> H;

	for (int i = 1; i <= n; ++i) {
		int cur = a[i];
		int pos = i;
		while (pos <= n) {
			cur = __gcd(cur, a[pos]);

			H.push_back({i, pos, cur});

			int l = pos, r = n + 1;

			while (r - l > 1) {
				int mid = (l + r) >> 1;

				if (getGcd(i, mid) == cur) l = mid;
				else r = mid;
			}
			pos = l + 1;
		}
	}

	sort(H.begin(), H.end(), [&] (const Segment &a, const Segment &b) {
		if (a.val == b.val) return a.l < b.l;
		return a.val < b.val;
 	});

	vector<query_t> queries;

	for (int i = 1; i <= q; ++i) {
		int l, r, d;
		cin >> l >> r >> d;
		d--;
		queries.emplace_back(l, r, d, i);
	}

	sort(queries.begin(), queries.end(), [&] (const query_t &a, const query_t &b) {
		return a.d < b.d;
	});

	for (int i = 1; i <= n; ++i) idx[i] = n + 1;

	int id = 0;

	for (auto &x : queries) {
		while (id < size32(H) && H[id].val <= x.d) {
			int l = H[id].l;
			int r = H[id].r;

			if (idx[l] <= n) {
				update(l, - idx[l]);
			}

			idx[l] = r;
			update(l, idx[l]);
 			++id;
		}

		int l = x.l;

		int lo = x.l - 1, hi = x.r + 1;

		while (hi - lo > 1) {
			int mid = (lo + hi) >> 1;
			if (idx[mid] <= x.r) lo = mid;
			else hi = mid;
		}

		if (l > lo) ans[x.id] = 0;
		else ans[x.id] = (lo - l + 1) * (x.r + 1) - (query(lo) - query(l - 1));

		ans[x.id] = (x.r - x.l + 1) * (x.r - x.l + 2) / 2 - ans[x.id];
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
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
