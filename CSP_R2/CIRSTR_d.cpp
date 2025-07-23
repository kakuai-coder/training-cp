/*
	Author: kakuai
	created: 2025.07.12 08:06:02
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

const i64 Base = 31, Mod = 1e9 + 7; 
const int maxN = 1e5 + 5; 

string s1, s2; 

struct Hash {
	
	int n; 
	i64 h[maxN], Pow[maxN];

	void init(string &s) {
		n = ssize(s); 
		s = " " + s;

		Pow[0] = 1; 

		for (int i = 1; i <= n; ++i) {
			Pow[i] = Pow[i - 1] * Base % Mod; 
			h[i] = (h[i - 1] * Base % Mod + (s[i] - 'a' + 1)) % Mod; 
		}
	}

	i64 Get(int l, int r) {
		return (h[r] - h[l - 1] * Pow[r - l + 1] % Mod + Mod * Mod) % Mod;
	}
} hash1, hash2;

set<i64> S;

bool check(int len) {
	S.clear(); 

	for (int i = 1; i <= hash1.n; ++i) {
		if (i + len - 1 <= hash1.n) {
			S.insert(hash1.Get(i, i + len - 1));
		} else {
			i64 d = hash1.Get(i, hash1.n); 
			int rem = len - (hash1.n - i + 1); 
			d = (d * hash1.Pow[rem] % Mod + hash1.Get(1, rem)) % Mod;
			
			S.insert(d);
		}
	}

	for (int i = 1; i <= hash2.n; ++i) {
		if (i + len - 1 <= hash2.n) {
			
			if (S.count(hash2.Get(i, i + len - 1))) return true; 

		} else {
			i64 d = hash2.Get(i, hash2.n); 
			int rem = len - (hash2.n - i + 1); 
			d = (d * hash2.Pow[rem] % Mod + hash2.Get(1, rem)) % Mod;
			
			if (S.count(d)) return true; 
		}
	}

	return false; 
}

void kakuai() {
	cin >> s1 >> s2; 


	hash1.init(s1); 
	hash2.init(s2); 

	int lo = 1, hi = min(hash1.n, hash2.n); 
	while (hi - lo > 1) {
		int mid = (hi + lo) / 2; 

		if (check(mid)) lo = mid; 
		else hi = mid; 
	}

	cout << lo;
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "CIRSSTR"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}