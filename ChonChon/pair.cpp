#include <bits/stdc++.h>

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define all(v) (v).begin(), (v).end()

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int siz(const T &a) {
	return a.size();
}

///mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1e5 + 5, MOD = 1e9 + 7;

int n, q;
int a[MAXN];

struct Query {
	int id, l, r, idx;

	void input(const int &_idx) {
		cin >> id >> l >> r;
		idx = _idx;
	}
};

Query queries[MAXN];

namespace Subtask2 {

	struct Node {
		int min1, min2, cnt1, cnt2;

		Node(int _min1 = 0, int _min2 = 0, int _cnt1 = 0, int _cnt2 = 0)
			: min1(_min1), min2(_min2), cnt1(_cnt1), cnt2(_cnt2) {}
	};
	vector<pair<int, int> > v;

	Node mergeNode(const Node &L, const Node &R) {
		Node res;

		v.clear();

		v.push_back({L.min1, L.cnt1});
		v.push_back({L.min2, L.cnt2});
		v.push_back({R.min1, R.cnt1});
		v.push_back({R.min2, R.cnt2});

		int min1 = 1e9, min2 = 1e9; 

		int cnt1 = 0, cnt2 = 0; 

		for (int i = 0; i < 4; ++i) {
			if (v[i].first < min1) {
				min2 = min1; cnt2 = cnt1; 
				min1 = v[i].first; cnt1 = v[i].second;
			} else if (v[i].first == min1) {
				cnt1 += v[i].second;
			} else if (v[i].first < min2) {
				min2 = v[i].first; cnt2 = v[i].second;
			} else if (v[i].first == min2) cnt2 += v[i].second;
		}

		if (min2 == 1e9) {
			min2 = min1; 
			cnt2 = 0;
		}

		res.min1 = min1; 
		res.min2 = min2;
		res.cnt1 = cnt1; 
		res.cnt2 = cnt2; 


		return res;
	}

	Node seg[4 * MAXN];

	void update(int id, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return ;

		if (l == r) {
			seg[id] = Node(val, 1e9, 1, 0);
			return ;
		}

		int mid = (l + r) >> 1;

		update(id << 1, l, mid, pos, val);
		update(id << 1 | 1, mid + 1, r, pos, val);

		seg[id] = mergeNode(seg[id << 1], seg[id << 1 | 1]);
	}

	Node query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return Node(1e9, 1e9, 0, 0);

		if (u <= l && r <= v) {
			return seg[id];
		}

		int mid = (l + r) >> 1;

		return mergeNode(query(id << 1, l, mid, u, v), query(id << 1 | 1, mid + 1, r, u, v));
	}

	void solve(void) {
		for (int i = 1; i <= n; ++i) update(1, 1, n, i, a[i]);

		int64_t ans = 0;

		for (int _ = 1; _ <= q; ++_) {
			int id = queries[_].id;
			int l = queries[_].l;
			int r = queries[_].r;

			if (id == 1) {
				update(1, 1, n, l, r);
			} else {
				Node c = query(1, 1, n, l, r);

				// cout << c.min1 << ' ' << c.min2 << ' ' << c.cnt1 << ' ' << c.cnt2 << '\n';
				
				if (c.cnt1 > 1) {
					ans += 1LL * c.cnt1 * (c.cnt1 - 1) / 2; 
				} else ans += 1LL * c.cnt1 * c.cnt2;
				ans %= MOD;
			}
		}

		cout << ans;
	}
}

void kakuai(void) {
	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i <= q; ++i) {
		queries[i].input(i);
	}

	Subtask2::solve();
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

#define cherry "pair"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	int T = 1;
	cin >> T;
	while (T--) {
		kakuai();
		cout << '\n';
	}

	cerr << '\n' << TIME << "ms\n";
}
