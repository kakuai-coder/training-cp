/*
	Author: kakuai
	created: 2025.07.04 08:09:24
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

string s; 
int q; 

void kakuai() {
	cin >> s >> q; 

	int n = ssize(s); 
	s = " " + s;

	while (q--) {
		int l, r; 
		cin >> l >> r; 

		bool ok = false; 

		for (int i = l + 1; i <= r; ++i) if (s[i] == s[i - 1]) {
			ok = true; 
			break; 
		}

		if (ok) {
			cout << "yes\n"; 
			continue;
		}

		for (int i = l + 2; i <= r; ++i) if (s[i] == s[i - 2]) {
			ok = true; 
			break; 
		}

		if (ok) {
			cout << "yes\n"; 
		} else cout << "no\n";
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "DOMISTR"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}