/*
	Author: kakuai
	created: 2025.07.01 08:19:27
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
char s[maxN], t[maxN];
int p[maxN], q[maxN], r[maxN];

void kakuai() {
	string S;
	int m;
	cin >> S >> m;
	int n = ssize(S);
	for (int i = 0; i < n; ++i) s[i] = S[i];

	while (m--) {
		int k, d;
		cin >> k >> d;

		for (int i = 0; i < n; ++i)
			p[i] = q[i] = i;

		int id = 0;
		for (int i = 0; i < d; ++i) {
			for (int j = i; j < k; j += d)
				p[id++] = j;
		}

		int last = p[0];
		for (int i = 0; i < n - 1; ++i)
			p[i] = p[i + 1];
		p[n - 1] = last;

		int pw = n - k + 1;
		while (pw > 0) {
			if (pw & 1) {
				for (int i = 0; i < n; ++i)
					r[i] = q[p[i]];
				for (int i = 0; i < n; ++i)
					q[i] = r[i];
			}
			for (int i = 0; i < n; ++i)
				r[i] = p[p[i]];
			for (int i = 0; i < n; ++i)
				p[i] = r[i];
			pw >>= 1;
		}

		for (int i = 0; i < n; ++i)
			t[i] = s[q[(k + i - 1) % n]];
		for (int i = 0; i < n; ++i)
			s[i] = t[i];

		for (int i = 0; i < n; ++i)
			cout << s[i];
		cout << '\n';
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "c"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}