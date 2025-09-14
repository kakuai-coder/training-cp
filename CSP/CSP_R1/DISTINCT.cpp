/*
Author: kakuai
created: 2025.07.24
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

const int NMask = (1 << 26) + 1, C = 26; 

string s;
bool cnt[NMask]; int last[C];


void kakuai(void) {
	// voi26 = winner
	cin >> s; 

	int n = size32(s); 
	s = ' ' + s; 

	set<int> pos; 
    int res = 1;
	for (int i = n; i >= 1; --i) {
		
		if (pos.find(last[s[i] - 'a']) != pos.end()) 
			pos.erase(pos.find(last[s[i] - 'a']));

		int d = 1 << (s[i] - 'a');

		if(cnt[d] == 0) res++, cnt[d] = 1;

		for (int x : pos) {
			d |= 1 << (s[x] - 'a');
			if(cnt[d] == 0) res++, cnt[d] = 1;
		}

		last[s[i] - 'a'] = i; 	

		pos.insert(i);

	}


	cout << res; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "DISTINCT"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}