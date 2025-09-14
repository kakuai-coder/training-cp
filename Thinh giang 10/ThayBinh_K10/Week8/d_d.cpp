/*
	Author: kakuai
	created: 2025.07.31 10:10:00
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

const int N = 3e4 + 5, M = 29 * N, inf = 1e9;
int n, q, ans[N], sz = 0;
string s[N], t[N];

struct node {
	int cnt, mn, nxt[26];
	node() {
		cnt = 0;
		mn = inf;
		memset(nxt, -1, sizeof nxt);
	}
} tr[M];

void add(const string &str, int id) {
	int x = 0;
	for (char c : str) {
		int u = c - 'a';
		if (tr[x].nxt[u] == -1) tr[x].nxt[u] = ++sz;
		x = tr[x].nxt[u];
		tr[x].cnt++;
		minimize(tr[x].mn, id);
	}
}

int get_min(const string &str) {
	int x = 0;
	for (char c : str) {
		int u = c - 'a';
		if (tr[x].nxt[u] == -1) return n;
		x = tr[x].nxt[u];
	}
	return min(n, tr[x].mn);
}

int get_cnt(const string &str) {
	int x = 0, res = 0;
	for (char c : str) {
		int u = c - 'a';
		if (tr[x].nxt[u] == -1) return res;
		x = tr[x].nxt[u];
		res += tr[x].cnt;
	}
	return res;
}

void reset() {
	for (int i = 0; i <= sz; i++) tr[i] = node();
	sz = 0;
}

void kakuai() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i], add(s[i], i);

	cin >> q;
	vector<pair<int, int>> v;
	for (int i = 1; i <= q; i++) {
		cin >> t[i];
		int r = get_min(t[i]);
		v.emplace_back(r, i);
	}

	sort(v.begin(), v.end());
	reset();

	int cur = 1;
	for (auto p : v) {
		int r = p.first, id = p.second;
		while (cur <= r) add(s[cur], cur), cur++;
		ans[id] = get_cnt(t[id]) + r;
	}

	for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry ""
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
