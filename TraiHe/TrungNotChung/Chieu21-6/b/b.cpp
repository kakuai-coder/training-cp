/*
	Author: kakuai
	created: 2025.06.26 17:28:31
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 5e4 + 11; 
const int Block = sqrt(maxN);

struct query_t {
	int idx, id, x, y; 

	query_t(int _idx, int _id, int _x, int _y) : idx(_idx), id(_id), x(_x), y(_y) {}
};

int n, q, a[maxN];
int cnt_x[maxN], cnt_y[maxN];
i64 ans[maxN];
vector<query_t> queries; 
i64 res = 0;

bool cmp(const query_t &a, const query_t &b) {
	if (a.x / Block != b.x / Block) {
		return a.x / Block < b.x / Block; 
	}

	return a.y < b.y; 
}

void add_x(int x) {
	if (x > n) return ; 
	cnt_x[a[x]]++; 
	res += cnt_y[a[x]];
}

void remove_x(int x) {
	if (x > n) return ; 
	cnt_x[a[x]]--; 
	res -= cnt_y[a[x]];
}

void add_y(int y) {
	if (y > n) return ; 
	cnt_y[a[y]]++; 
	res += cnt_x[a[y]];
}

void remove_y(int y) {
	if (y > n) return ; 
	cnt_y[a[y]]--; 
	res -= cnt_y[a[y]];
}

void kakuai() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	cin >> q; 

	for (int i = 1; i <= q; ++i) {
		int l1, r1, l2, r2; 
		cin >> l1 >> r1 >> l2 >> r2; 

		queries.push_back({i, 1, r1, r2}); 
		queries.push_back({i, 1, l1 - 1, l2 - 1}); 
		queries.push_back({i, -1, r1, l2 - 1});
		queries.push_back({i, -1, l1 - 1, r2});
	
	}

	sort(queries.begin(), queries.end(), cmp); 

	int x = 0, y = 0;

	for (query_t &d : queries) {
		int idx = d.idx; 
		int id = d.id; 
		int l = d.x; 
		int r = d.y; 

		while (l > x) add_x(++x); 
		while (l < x) remove_x(x--);

		while (r > y) add_y(++y); 
		while (r < y) remove_y(y--);

		ans[idx] += 1LL * id * res; 
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}