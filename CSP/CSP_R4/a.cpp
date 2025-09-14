/*
Author: kakuai
created: 2025.07.26
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

string s; 

void kakuai(void) {
	// voi26 = winner
	cin >> s; 

	int n = size32(s);
	s = ' ' + s; 
	
	vector<int> a(n  + 1, 0);

	int ans = 0; 

	vector<int> stk; 

	unordered_map<char, char> match = {{')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};

	for (int i = 1; i <= n; ++i) {
		if (s[i] == '(' || s[i] == '{' || s[i] == '[' || s[i] == '<') {
			stk.push_back(i);
		} else {
			if (!stk.empty() && s[stk.back()] == match[s[i]]) {
				stk.pop_back();

				maximize(ans, i - stk.back());
			} else {
				while (!stk.empty()) stk.pop_back();
				stk.push_back(i);
			}
		}
	}

	cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "a"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}