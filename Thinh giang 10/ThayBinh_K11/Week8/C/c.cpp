/*
	Author: kakuai
	created: 2025.07.09 11:41:44
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5, maxB = 330;

int n, q, e;
int a[maxN], l[maxN], r[maxN], block[maxN];
int g[maxB][maxB], v[maxB][maxN];

u64 s[maxN], t[maxB], f[maxB];

void update(int x, i64 w) {
	for (int i = x; block[i] == block[x]; i++) {
		s[i] += w;
	}
	for (int i = block[n]; i > block[x]; i--) {
		t[i] += w;
	}
	for (int i = 1; i <= block[n]; i++) {
		f[i] += w * (v[i][x] + g[i][block[x]]);
	}
}

void kakuai() {
	cin >> n;
	e = maxB;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
		block[i] = (i - 1) / e + 1;
	}
	for (int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];

		for (int j = l[i]; j <= r[i] && block[j] == block[l[i]]; j++) {
			v[block[i]][j]++;
		}
		for (int j = r[i]; j >= l[i] && block[j] == block[r[i]] && block[l[i]] != block[r[i]]; j--) {
			v[block[i]][j]++;
		}
		for (int j = block[l[i]] + 1; j < block[r[i]]; j++) {
			g[block[i]][j]++;
		}
		f[block[i]] += s[r[i]] - s[l[i] - 1];
	}

	cin >> q;
	while (q--) {
		int type, x, y;
		cin >> type >> x >> y;
		if (type == 1) {
			update(x, y - a[x]);
			a[x] = y;
		} else {
			u64 res = 0;
			for (int i = x; i <= y && block[i] == block[x]; i++) {
				res += s[r[i]] + t[block[r[i]]] - s[l[i] - 1] - t[block[l[i] - 1]];
			}
			for (int i = y; i >= x && block[i] == block[y] && block[x] != block[y]; i--) {
				res += s[r[i]] + t[block[r[i]]] - s[l[i] - 1] - t[block[l[i] - 1]];
			}
			for (int i = block[x] + 1; i < block[y]; i++) {
				res += f[i];
			}
			cout << res << '\n';
		}
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
