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
	
	vector <vector<int> > pos(2); 

	for (int i = 2; i <= n; ++i) {
		if (s[i] == s[i - 1]) pos[0].push_back(i); 
		if (s[i] == s[i - 2]) pos[1].push_back(i);
	}

	while (q--) {
		int l, r; 
		cin >> l >> r; 

		if (ssize(pos[0])) {
			int Left = lower_bound(pos[0].begin(), pos[0].end(), l + 1) - pos[0].begin();
			int Right = upper_bound(pos[0].begin(), pos[0].end(), r) - pos[0].begin() - 1;
			
			// cout << Left << ' ' << Right << ": ";

			if (Right - Left + 1 > 0) {
				cout << "YES\n";
				continue;
			}

		} 
		if (ssize(pos[1])) {
			int Left = lower_bound(pos[1].begin(), pos[1].end(), l + 2) - pos[1].begin();
			int Right = upper_bound(pos[1].begin(), pos[1].end(), r) - pos[1].begin() - 1;

			// cout << Left << ' ' << Right << ": ";

			if (Right - Left + 1 > 0) {
				cout << "YES\n";
				continue;
			}
		}

		cout << "NO\n";

	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "DOMISTR"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}