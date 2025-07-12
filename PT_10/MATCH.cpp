/*
	Author: kakuai
	created: 2025.07.12 08:37:16
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

const int maxN = 1e6 + 5; 

int n, m, q; 
int a[maxN], b[maxN], l[maxN], r[maxN];

namespace Sub1 {

	void Main() {
		for (int id = 1; id <= q; ++id) {

			vector<int> v; 

			int ok = 0; 

			for (int i = 0; i <= m - 1; ++i) {
				for (int j = m - i + 1; j <= m; ++j) {
					v.push_back(b[j]);
				}

				for (int j = 1; j < m - i + 1; ++j) v.push_back(b[j]); 

				int idx = 0; 

				for (int j = l[id]; j <= r[id]; ++j) {
					if (a[j] == v[idx]) {
						idx++;
					}
				}

				if (idx == ssize(v)) {
					ok = 1; 
					break;
				}
			}

			cout << (ok ? "YES" : "NO") << '\n';
		}
	}

	bool run() {
		if (q > 10 || max(m, n) > 1000) return false; 
		return Main(), true;
	}
}

namespace Sub2 {

	const i64 Mod = 1e9 + 7; 

	i64 hashA[maxN], hashB[maxN], Pow[maxN];
	i64 Base; 

	void Main() {
		Base = m + 3; 
		set<i64> S; 
		for (int i = 0; i <= m - 1; ++i) {
			vector<int> v; 
			for (int j = m - i + 1; j <= m; ++j) {
				v.push_back(b[j]);
			}

			for (int j = 1; j < m - i + 1; ++j) v.push_back(b[j]); 
			
			for (int d = 1; d <= m; ++d) hashB[i] = (hashB[i] * Base % Mod + (v[d - 1] + 1)) % Mod;
			S.insert(hashB[i]);
		}

		Pow[0] = 1; 

		for (int i = 1; i <= n; ++i) {
			Pow[i] = Pow[i - 1] * Base % Mod;
			hashA[i] = (hashA[i - 1] * Base % Mod + (a[i] + 1)) % Mod;
		}

		for (int i = 1; i <= q; ++i) {
			int u = l[i]; 
			int v = r[i];

			i64 h = (hashA[v] - hashA[u - 1] * Base % Mod + Mod * Mod) % Mod;

			if (S.count(h)) {
				cout << "YES";
			} else cout << "NO";

			cout << '\n';
		}
	}

	bool run() {
		if (m > 1000) return false; 
		for (int i = 1; i <= q; ++i) if (r[i] - l[i] + 1 != m) return false; 
		return Main(), true;
	}
}

namespace SubFull {

	int pref[maxN], suff[maxN], pos[maxN], mark[maxN];

	void Main() {
		for (int i = 1; i <= m; ++i) pos[b[i]] = i; 

		for (int i = 1; i <= n; ++i) a[i] = pos[a[i]];

		for (int idx = 1; idx <= q; ++idx) {
			int u = l[idx]; 
			int v = r[idx]; 

			for (int i = u; i <= v; ++i) {
				pref[i] = mark[a[i] - 1] + 1; 
				mark[a[i]] = max(mark[a[i]], pref[i]);
			}

			for (int i = 1; i <= m; ++i) mark[i] = 0;  

			for (int i = v; i >= u; --i) {
				suff[i] = mark[a[i] + 1] + 1; 
				maximize(mark[a[i]], suff[i]);
			}
			
			int lastM = 0;

			bool ok = false; 

			for (int i = u; i <= v; ++i) {
				if (a[i] == m) lastM = i;
				if (a[i] == 1) {
					if (suff[i] + pref[lastM] >= v - u + 1) {
						ok = true; break;
					}
				}
			}

			cout << (ok ? "YES" : "NO") << '\n';
		}
	}

	bool run() {

		return Main(), true;
	}
}



void kakuai() {
	cin >> n >> m >> q; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	for (int i = 1; i <= m; ++i) {
		cin >> b[i];
	}

	for (int i = 1; i <= q; ++i) {
		cin >> l[i] >> r[i];
	}

	if (Sub1::run()) return ;
	if (Sub2::run()) return ; 
	SubFull::run();
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "MATCH"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}