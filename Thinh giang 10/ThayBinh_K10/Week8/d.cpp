/*
Author: kakuai
created: 31.7.2025
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

const int maxN = 3e5 + 5;

int n, m;
char s[maxN];

struct Node {
	Node* child[26];
	int isWord, len, cnt, idx;

	Node() {
		for (int i = 0; i < 26; ++i) child[i] = nullptr;
		isWord = len = cnt = 0;
		idx = maxN;
	}
};

struct Trie {
	int cur;
	Node* root;

	Trie() : cur(0) {
		root = new Node();
	}

	void ins(string &s, int idx) {

		Node* p = root;

		for (char c : s) {
			int id = c - 'a';

			if (p->child[id] == nullptr) p->child[id] = new Node();

			p = p->child[id];
			p->cnt++;
		}

		p->isWord = 1;
		p->idx = min(p->idx, idx);
		p->len++;
	}

	int getPos(const string &x) {
		Node* p = root;

		for (char c : x) {
			int id = c - 'a';
			if (p->child[id] == nullptr) return n;
			p = p->child[id];
		}

		return min(n, p->idx);
	}

	int getCnt(const string &x) {
		Node* p = root;

		int ret = 0;

		for (char c : x) {
			int id = c - 'a';
			if (p->child[id] == nullptr) return ret;
			p = p->child[id];
			ret += p->cnt;
		}

		return ret;
	}

} trie1, trie2;

string t[maxN], queries[maxN];
int ans[maxN];

void kakuai(void) {
	// voi26 = winner
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> t[i];
		trie1.ins(t[i], i);
	}

	int q;
	cin >> q;
	vector<pair<int, int> > ask(q + 1);

	for (int i = 1; i <= q; ++i) {
		cin >> queries[i];

		int id = trie1.getPos(queries[i]);

		ask.push_back({id, i});
	}

	sort(ask.begin(), ask.end());

	int cur = 1;

	for (auto & as : ask) {
		int id = as.first;
		int idx = as.second;
		while (cur <= id) trie2.ins(t[cur], cur), cur++;

		ans[idx] = id + trie2.getCnt(queries[idx]);
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "d"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
