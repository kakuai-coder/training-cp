#include <bits/stdc++.h>

using namespace std;

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int ssiz(const T &a) {
	return int(a.size());
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

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 22.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MODV = 1e6 + 3; 
const int64_t INF = (int64_t) 1e18 + 11;

struct Node {
	int l = -1, r = -1;
	int64_t sum = 0, best = -INF; 

	Node() = default;

	Node(int _l, int _r, int64_t _sum, int64_t _best) : 
		l(_l), r(_r), sum(_sum), best(_best) {}

	friend Node operator+(const Node &L, const Node &R) {
		Node res; 
		res.l = L.l; 
		res.r = R.r; 
		res.best = max(L.best, R.best - L.sum);
		res.sum = L.sum + R.sum; 

		return res; 
	}
};

int q;
vector<Node> st(4 * MODV + 5);
vector<array<int, 3> > queries; 
int64_t t[MODV + 1];


void build(int id, int l, int r) {
	if (l == r) {
		st[id] = Node(l, r, 0, -INF);
		return ;
	}

	int mid = (l + r) >> 1; 

	build(id << 1, l, mid); 
	build(id << 1 | 1, mid + 1, r);

	st[id] = st[id << 1] + st[id <<  1 | 1];	
}

void update(int id, int pos, int val) {
	if (st[id].l > pos || pos > st[id].r) return ; 

	if (st[id].l == st[id].r) {
		t[st[id].l] += val; 
		if (t[st[id].l] > 0) st[id] = Node(st[id].l, st[id].r, t[st[id].l], st[id].l);
		else st[id] = Node(st[id].l, st[id].r, 0, -INF);
		return ;
	}

	update(id << 1, pos, val); 
	update(id << 1 | 1, pos, val); 

	st[id] = st[id << 1] + st[id << 1 | 1];
}

void kakuai(void) { 
	cin >> q; 

	for (int i = 1; i <= q; ++i) {
		char op; 
		int x, y; 
		cin >> op; 

		if (op == 'A') {
			cin >> x >> y; 
			queries.push_back({0, x, y});
		} else {
			cin >> x;
			queries.push_back({1, x, -1});
		}
	}

	int64_t ans = 0; 

	build(1, 0, MODV);

	vector<array<int, 2> > adds; 

	for (auto &query : queries) {
		if (query[0] == 0) {
			int x = query[1]; 
			int y = query[2]; 

			int pos = (x + ans) % MODV;
			int val = (y + ans) % MODV; 

			adds.push_back({pos, val});

			update(1, pos, val);
		} else {
			int x = query[1]; 

			int idx = (x + ans) % MODV - 1;
			
			if (adds[idx][1] == -1e9) continue;
			
			int pos = adds[idx][0]; 
			int val = adds[idx][1];

			update(1, pos, -val);

			adds[idx] = {0,(int) -1e9};
		}

		Node root = st[1]; 

		if (root.sum > 0) ans = max(0LL, root.best) + root.sum - 1; 
		else ans = 0;

		cout << ans << '\n'; 
	}
	
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
