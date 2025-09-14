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
				pref[i][j] = (pref[i - 1][j] * Base % Mod[j] + s[i - 1] - 'A' + 1) % Mod[j];
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

PolyHash hasha, hashb; 
int n, m, k; 
string a, b; 

unordered_map<uint64_t, int> S; 

bool check(int len) {
	S.clear(); 

	for (int i = 1; i + len - 1 <= hasha.sz; ++i) {
		S[hasha.get(i, len).to_uint64()]++;
	}

	for (int i = 1; i + len - 1 <= hashb.sz; ++i) {
		uint64_t id = hashb.get(i, len).to_uint64(); 

		if (S.count(id)) {
			if (S[id] >= k) return true;  
		}
	}

	return false; 
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m >> k; 
	cin >> b >> a; 

	hasha = PolyHash(a); 
	hashb = PolyHash(b); 

	int l = 0, r = n + 1; 

	while (r - l > 1) {
		int mid = (l + r) >> 1; 

		if (check(mid)) l = mid; 
		else r = mid;
	}

	int len = l; 
	S.clear(); 

	for (int i = 1; i + len - 1 <= hasha.sz; ++i) {
		S[hasha.get(i, len).to_uint64()]++;
	}

	uint64_t minHash = (1ULL << 64LL) - 1; 
	int minpos = -1; 
	 

	for (int i = 1; i + len - 1 <= hashb.sz; ++i) {
		uint64_t id = hashb.get(i, len).to_uint64(); 

		if (S.count(id)) {
			if (S[id] >= k) {
				if (minpos == -1 || b.substr(i - 1, len) < b.substr(minpos, len)) {
					minpos = i - 1;
				}
			}
		}
	}

	for (int i = minpos; i <= minpos + len - 1; ++i) cout << b[i];
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "D"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}