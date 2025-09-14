/*
Author: kakuai
created: 2025.07.23
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

constexpr int64_t Base = 311, NMod = 2; 
constexpr int64_t Mod[NMod] = {(int64_t)1e9 + 7, (int64_t)1e9 + 2277};

struct valHash {
	int64_t val[NMod];

	valHash(int64_t x = 0) { 
		for (int i = 0; i < NMod; ++i) val[i] = x; 
	}

	int64_t& operator[](int i) { return val[i]; }
	const int64_t& operator[](int i) const { return val[i]; }

	bool operator==(const valHash& other) const {
		for (int i = 0; i < NMod; ++i)
			if (val[i] != other.val[i]) return false;
		return true;
	}

	uint64_t to_uint64() {
		return (uint64_t(val[0]) << 32) | uint64_t(val[1]);
	}
};

struct PolyHash {
	vector<valHash> pow, pref;
	int sz;

	PolyHash() : sz(0) {}

	PolyHash(const string &s) {
		sz = size32(s);
		pow.assign(sz + 1, valHash(1));
		pref.assign(sz + 1, valHash());

		for (int i = 1; i <= sz; ++i) {
			for (int j = 0; j < NMod; ++j) {
				pow[i][j] = pow[i - 1][j] * Base % Mod[j];
				pref[i][j] = (pref[i - 1][j] * Base % Mod[j] + s[i - 1] - 'a' + 1) % Mod[j];
			}
		}
	}

	valHash get(int pos, int len) const {
		static valHash ret;
		for (int j = 0; j < NMod; ++j) {
			ret[j] = (pref[pos + len - 1][j] - pref[pos - 1][j] * pow[len][j] % Mod[j] + Mod[j] * Mod[j]) % Mod[j];
		}
		return ret;
	}

	valHash get_range(int l, int r) const {
		return get(l, r - l + 1);
	}
};

void kakuai(void) {
	// voi26 = winner
	string a, b; 
	cin >> a >> b; 

	PolyHash hasha(a), hashb(b); 

	valHash d = hashb.pref.back();

	int len = size32(b), cnt = 0;

	for (int i = 1; i + len - 1 <= hasha.sz; ++i) {
		if (hasha.get(i, len) == d) cnt++;
	}	

	cout << cnt; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "A"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}