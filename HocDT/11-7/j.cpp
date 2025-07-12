/*************************************
*    author: marvinthang             *
*    created: 11.07.2025 15:14:50    *
*************************************/

#include <bits/stdc++.h>

using namespace std;

#define             fi  first
#define             se  second
#define           left  ___left___
#define          right  ___right___
#define   scan_op(...)  istream & operator >> (istream &in, __VA_ARGS__ &u)
#define  print_op(...)  ostream & operator << (ostream &out, const __VA_ARGS__ &u)
#define     file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

namespace std {
template <class U, class V> scan_op(pair <U, V>) { return in >> u.first >> u.second; }
template <class T> scan_op(vector <T>) { for (size_t i = 0; i < u.size(); ++i) in >> u[i]; return in; }
template <class U, class V> print_op(pair <U, V>) { return out << '(' << u.first << ", " << u.second << ')'; }
template <size_t i, class T> ostream &print_tuple_utils(ostream &out, const T &tup) { if constexpr(i == tuple_size<T>::value) return out << ")"; else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); }
template <class...U> print_op(tuple <U...>) { return print_tuple_utils<0, tuple <U...>>(out, u); }
template <class Con, class = decltype(begin(declval<Con>()))>typename enable_if <!is_same<Con, string>::value, ostream &>::type operator << (ostream &out, const Con &con) { out << '{'; for (__typeof(con.begin()) it = con.begin(); it != con.end(); ++it) out << (it == con.begin() ? "" : ", ") << *it; return out << '}'; }
template <class T> print_op(stack <T>) { vector <T> v; stack <T> st = u; while (!st.empty()) v.push_back(st.top()), st.pop(); reverse(v.begin(), v.end()); return out << v; }
template <class T> print_op(queue <T>) { queue <T> q = u; out << '{'; while (!q.empty()) { out << q.front(); q.pop(); if (!q.empty()) out << ", "; } out << '}'; return out; }
template <class T, class X, class Y> print_op(priority_queue <T, X, Y>) { priority_queue <T, X, Y> pq = u; out << '{'; while (!pq.empty()) { out << pq.top(); pq.pop(); if (!pq.empty()) out << ", "; } out << '}'; return out; }
template <class Fun> class y_combinator_result { Fun fun_; public: template <class T> explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)) {} template <class...Args> decltype(auto)operator()(Args &&...args) { return fun_(ref(*this), forward<Args>(args)...); } };
template <class Fun> decltype(auto)y_combinator(Fun &&fun) { return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun)); }
template <typename T, int D> struct Vec: public vector <Vec<T, D - 1>> { static_assert(D >= 1, "Vector dimension must be greater than zero!"); template <typename ...Args> Vec(int n = 0, Args ...args): vector <Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {} };
template <typename T> struct Vec<T, 1>: public vector<T>{ Vec(int n = 0, const T &val = T()): vector<T>(n, val) {} };
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
}

static char buf[450 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*) &buf[i -= s];
}
void operator delete(void*) {}

struct Node {
	Node *left, *right;
	int val;
	Node(int val = 0): val(val), left(nullptr), right(nullptr) {}
	Node(Node *left, Node *right): left(left), right(right), val(0) {
		if (left) val += left->val;
		if (right) val += right->val;
	}
};

Node* build(int l, int r) {
	if (r - l == 1) return new Node();
	int m = l + r >> 1;
	return new Node(build(l, m), build(m, r));
}
Node* update(Node *cur, int l, int r, int p, int val) {
	if (r - l == 1) {
		return new Node(cur->val + val);
	}
	int m = l + r >> 1;
	if (p < m) {
		return new Node(update(cur->left, l, m, p, val), cur->right);
	} else {
		return new Node(cur->left, update(cur->right, m, r, p, val));
	}
}

int query(Node *cur, int l, int r, int u, int v) {
	if (r <= u || l >= v) return 0;
	if (u <= l && r <= v) return cur->val;
	int m = l + r >> 1;
	return query(cur->left, l, m, u, v) + query(cur->right, m, r, u, v);
}
void process(void) {
	int n, q, s; cin >> n >> q >> s;
	vector <int> a(n); cin >> a;

	int ma = *max_element(a.begin(), a.end());
	vector <int> lpf(ma + 1), primes, pos(ma + 1);
	for (int i = 2; i <= ma; ++i) {
		if (!lpf[i]) {
			lpf[i] = i;
			pos[i] = primes.size();
			primes.push_back(i);
		}
		for (int j = 0; j < (int)primes.size() && primes[j] <= lpf[i] && primes[j] * i <= ma; ++j) {
			lpf[primes[j] * i] = primes[j];
		}
	}

	vector <vector <pair <int, int>>> updateAt(primes.size());
	for (int i = 0; i < n; ++i) {
		while (a[i] > 1) {
			int p = lpf[a[i]];
			int cnt = 0;
			while (lpf[a[i]] == p) {
				++cnt;
				a[i] /= p;
			}
			updateAt[pos[p]].emplace_back(i, cnt);
		}
	}
	vector <Node*> segs;
	segs.push_back(build(0, n));
	for (int i = 0; i < ssize(primes); ++i) {
		Node *cur = segs.back();
		for (auto [idx, cnt]: updateAt[i]) {
			cur = update(cur, 0, n, idx, cnt);
		}
		segs.push_back(cur);
	}
	long long sum = 0;
	for (int i = 0; i < q; ++i) {
		int x, y, z, t; cin >> x >> y >> z >> t;
		int l = min((x + sum * s) % n, (y + sum * s) % n);
		int r = 1 + max((x + sum * s) % n, (y + sum * s) % n);
		int u = 1 + min((z + sum * s) % 1000000, (t + sum * s) % 1000000);
		int v = 1 + max((z + sum * s) % 1000000, (t + sum * s) % 1000000);

		u = lower_bound(primes.begin(), primes.end(), u) - primes.begin();
		v = upper_bound(primes.begin(), primes.end(), v) - primes.begin();
		
		int res = query(segs[v], 0, n, l, r) - query(segs[u], 0, n, l, r);
		
		cout << res << '\n';
		
		sum += res;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	file("11-7");
	// int t; cin >> t; while (t--)
	process();
	return (0^0);
}