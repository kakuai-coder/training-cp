/*
	Author: kakuai
	created: 2025.07.07 15:38:25
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 5e5 + 5; 
const int Mod = 1e9 + 7; 

int n, m, q, a[maxN], b[maxN], c[maxN];
int sumA[maxN], sumC[maxN]; 

void kakuai() {
	cin >> n >> m >> q; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i <= m; ++i) {
		cin >> b[i]; 
	}

	for (int i = 1; i <= q; ++i) {
		cin >> c[i];
	}

	sort(a + 1, a + n + 1); 
	sort(b + 1, b + m + 1); 
	sort(c + 1, c + q + 1); 

	for (int i = 1; i <= n; ++i) {
		sumA[i] = sumA[i - 1] + a[i]; 
		sumA[i] %= Mod;
	}

	for (int i = 1; i <= q; ++i) {
		sumC[i] = sumC[i - 1] + c[i];
		sumC[i] %= Mod; 
	}

	int ans = 0; 

	for (int i = 1; i <= m; ++i) {
		int j = upper_bound(a + 1, a + n + 1, b[i]) - a - 1;
		int k = upper_bound(c + 1, c + q + 1, b[i]) - c - 1; 
		
		ans += ((b[i] * sumA[j]) % Mod * k % Mod + 
		 				(b[i] * sumC[k]) % Mod * j % Mod + 
						((b[i] * b[i]) % Mod * j) % Mod * k % Mod + 
						sumA[j] * sumC[k] % Mod) % Mod; 
		ans %= Mod;  
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "wtriple"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}