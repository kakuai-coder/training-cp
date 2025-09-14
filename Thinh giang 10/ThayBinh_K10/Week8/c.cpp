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
	int isWord, len, cnt;

	Node() {
		for (int i = 0; i < 26; ++i) child[i] = nullptr;
		isWord = len = cnt = 0;
	}
};

struct Trie {
	int cur;
	Node* root;

	Trie() : cur(0) {
		root = new Node();
	}

	void ins(string &s) {

		Node* p = root;

		for (char c : s) {
			int id = c - 'a';

			if (p->child[id] == nullptr) p->child[id] = new Node();

			p = p->child[id];
			p->cnt++;
		}

		p->isWord = 1;
		p->len++;
	}
} trie;

void kakuai(void) {
	// voi26 = winner
	cin >> n;

	vector<string> v;

	for (int i = 1; i <= n; ++i) {
		string t;
		cin >> t;
		trie.ins(t);
		v.push_back(t);
	}

	int64_t ans = 0;

	for (string &x : v) {
		Node* p = trie.root;

		for (char c : x) {
			int id = c - 'a';
			if (p->child[id] == nullptr) break;
			p = p->child[id];
		}

//		cout << p->cnt << '\n';
		ans += p->cnt - 1;
		p->cnt--;
	}

	cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "c"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
