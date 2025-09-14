#include <bits/stdc++.h>

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define all(v) v.begin(), v.end()
#define debug(x) cerr << #x << ": " << x << "\n"

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

// > kakuai < <cherry> >> 08.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 1e4 + 5, MAXQ = 1e5 + 5; 

struct Item {
	int w = 0, v = 0;
};

struct Query {
	int l, r, t, idx; 

	Query(int _l = 0, int _r = 0, int _t = 0, int _idx = 0) : l(_l), r(_r), t(_t), idx(_idx) {}

	void input(int &id) {
		cin >> l >> r >> t; 
		idx = id; 
	}
};

int n, q; 
Item items[MAXN];
Query queries[MAXQ];

namespace Subtask1 {
	bool check(void) {
		for (int i = 1; i <= q; ++i) if (queries[i].r - queries[i].l + 1 > 200) return false; 
		return true;  
	}

	int64_t dp[105];

	void solve(void) {
		int64_t ans = 0; 
		for (int i = 1; i <= q; ++i) {
			int l = queries[i].l; 
			int r = queries[i].r; 
			int t = queries[i].t;

			for (int j = 0; j <= 100; ++j) dp[j] = 0; 

			for (int j = l; j <= r; ++j) {
				for (int W = t; W >= items[j].w; --W) {
					dp[W] = max(dp[W], dp[W - items[j].w] + items[j].v);
				}
			}

			ans += dp[t];
		}
		cout << ans; 
	}
};

namespace Subtask2 {
	bool check(void) {
		return true;
	}

	const int MAXW = 101;

	int64_t ans = 0;

	void calc(int L, int R, vector<Query> &query) {
		if (query.empty()) return ; 
		
		if (L == R) {
			for (Query &q : query) {
				if (q.t >= items[L].w) ans += items[L].v; 
			}

			return ;
		}

		int mid = (L + R) >> 1; 

		int cntL = mid - L + 1; 
		int cntR = R - mid; 

		vector< array<int, MAXW> > dpL(cntL + 1), dpR(cntR + 1);

		array<int, MAXW> cur; 

		cur.fill(0); 

		for (int i = mid; i >= L; --i) {
			for (int j = MAXW; j >= items[i].w; --j) {
				maxim(cur[j], cur[j - items[i].w] + items[i].v);
			}
			dpL[i - L + 1] = cur; 
		}

		cur.fill(0); 

		for (int i = mid + 1; i <= R; ++i) {
			for (int j = MAXW; j >= items[i].w; --j) {
				maxim(cur[j], cur[j - items[i].w] + items[i].v);
			}

			dpR[i - mid] = cur; 
		}

		vector<Query> qL, qR; 

		for (Query &q : query) {
			if (q.r <= mid) qL.push_back(q);
			else if (q.l > mid) qR.push_back(q);
			else {
				int t = q.t; 

				// cout << q.idx << ' ' << mid << '\n';
				
				const array<int, MAXW> &bestL = dpL[q.l - L + 1];
				const array<int, MAXW> &bestR = dpR[q.r - mid];

				int best = 0;

				for (int j = 0; j <= t; ++j) {
					maxim(best, bestL[j] + bestR[t - j]);
				}

				ans += best;
			}
		}

		if (!qL.empty()) calc(L, mid, qL);
		if (!qR.empty()) calc(mid + 1, R, qR);
	}

	void solve(void) {
		vector<Query> query; 

		for (int i = 1; i <= q; ++i) query.push_back(queries[i]); 

		calc(1, n, query);

		cout << ans; 
	}
};

void kakuai(void) { 
	cin >> n; 

	for (int i = 1; i <= n; ++i) cin >> items[i].w >> items[i].v; 

	cin >> q; 

	for (int i = 1; i <= q; ++i) {
		queries[i].input(i);
	}

	// return void(Subtask1::solve()); 
	if (Subtask2::check()) return void(Subtask2::solve());
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

#define cherry "knapsack"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	int T = 1;
	// cin >> T;
	while (T--) {
		kakuai();
		// cout << '\n';
	}

	cerr << '\n' << TIME << "ms";
}