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

static vector<int> spf;

void build_spf(int up) {
	spf.assign(up + 1, 0);
	if (up >= 1) spf[1] = 1;
	for (int i = 2; i <= up; ++i) {
		if (spf[i] == 0) {
			spf[i] = i;
			if ((long long)i * i <= up)
				for (int j = i * i; j <= up; j += i)
					if (spf[j] == 0) spf[j] = i;
		}
	}
}

vector<int> unique_pf(int x) {
	vector<int> res;
	while (x > 1) {
		int p = spf[x];
		if (p == 0) p = x;
		res.push_back(p);
		while (x % p == 0) x /= p;
	}
	return res;
}

int mygcd(int a, int b) {
	if (a == 0) return b;
	if (b == 0) return a;
	return __gcd(a, b);
}

void kakuai() {
	// voi26 = winner
	int t;
	if (!(cin >> t)) return;
	vector<tuple<int,int,vector<int>>> tests;
	tests.reserve(t);
	int max_m = 1;
	for (int tt = 0; tt < t; ++tt) {
		int n, m;
		cin >> n >> m;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) cin >> a[i];
		tests.emplace_back(n, m, move(a));
		max_m = max(max_m, m);
	}
	build_spf(max_m);

	for (auto &tc : tests) {
		int n, m; vector<int> a;
		tie(n, m, a) = tc;

		vector<vector<int>> multiples(m + 1);
		vector<vector<int>> pf(n);
		for (int i = 0; i < n; ++i) {
			pf[i] = unique_pf(a[i]);
			for (int p : pf[i]) if (p <= m) multiples[p].push_back(i);
		}

		vector<int> all_idx(n); iota(all_idx.begin(), all_idx.end(), 0);
		vector<int> seen(n, 0);
		int timer = 1;
		vector<pair<int,int>> pairs; pairs.reserve(n);

		for (int i = 0; i < n; ++i) {
			++timer;
			for (int p : pf[i]) if (p <= m) {
				for (int idx : multiples[p]) seen[idx] = timer;
			}
			seen[i] = timer;
			int partner = -1;
			for (int idx : all_idx) if (seen[idx] != timer) { partner = idx; break; }
			if (partner != -1) pairs.emplace_back(i, partner);
		}

		bool printed = false;
		int P = (int)pairs.size();
		for (int i = 0; i < P && !printed; ++i) {
			for (int j = i+1; j < P && !printed; ++j) {
				int a1 = pairs[i].first, b1 = pairs[i].second;
				int a2 = pairs[j].first, b2 = pairs[j].second;
				if (a1!=a2 && a1!=b2 && b1!=a2 && b1!=b2) {
					cout << a1+1 << ' ' << b1+1 << ' ' << a2+1 << ' ' << b2+1 << '\n';
					printed = true;
				}
			}
		}
		if (printed) continue;

		int K = min(n, 700);
		vector<pair<int,int>> edges;
		edges.reserve((size_t)K*(K-1)/2);
		for (int i = 0; i < K; ++i) {
			for (int j = i+1; j < K; ++j) {
				if (mygcd(a[i], a[j]) == 1) edges.emplace_back(i, j);
			}
		}
		bool found = false;
		int p1=-1,q1=-1,p2=-1,q2=-1;
		int E = (int)edges.size();
		for (int i = 0; i < E && !found; ++i) {
			int u = edges[i].first, v = edges[i].second;
			for (int j = i+1; j < E; ++j) {
				int x = edges[j].first, y = edges[j].second;
				if (u!=x && u!=y && v!=x && v!=y) {
					p1=u; q1=v; p2=x; q2=y;
					found = true; break;
				}
			}
		}
		if (found) {
			cout << p1+1 << ' ' << q1+1 << ' ' << p2+1 << ' ' << q2+1 << '\n';
			continue;
		}

		if (n <= 2000) {
			edges.clear();
			for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j)
				if (mygcd(a[i], a[j]) == 1) edges.emplace_back(i, j);
			E = (int)edges.size();
			found = false;
			for (int i = 0; i < E && !found; ++i) {
				int u = edges[i].first, v = edges[i].second;
				for (int j = i+1; j < E; ++j) {
					int x = edges[j].first, y = edges[j].second;
					if (u!=x && u!=y && v!=x && v!=y) {
						p1=u; q1=v; p2=x; q2=y;
						found = true; break;
					}
				}
			}
			if (found) {
				cout << p1+1 << ' ' << q1+1 << ' ' << p2+1 << ' ' << q2+1 << '\n';
				continue;
			}
		}

		cout << 0 << '\n';
	}
}

int main() {
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
