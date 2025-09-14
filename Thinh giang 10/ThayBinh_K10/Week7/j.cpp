/*
Author: kakuai
created: 31.7.2025
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

const int maxN = 1e4 + 5, maxS = 105;
const int Mod = 1e9 + 7;

int n;
string s;

int pi[maxS], nxt[maxN][2], dp[maxN][maxS][3];

void kakuai(void) {
	// voi26 = winner
	cin >> n >> s;

	int m = size32(s);
	s = ' ' + s;

	for (int i = 2; i <= m; ++i) {
		int j = pi[i - 1];
		while (j && s[j + 1] != s[i]) j = pi[j];

		if (s[j + 1] == s[i]) j++;

		pi[i] = j;
	}

	for (int i = 1; i <= m + 1; ++i) {
		for (int j = 0; j <= 1; ++j) {
			char c = '0' + j;

			if (i <= m && s[i] == c) {
				nxt[i][j] = i + 1;
			} else {
				int x = i - 1;
				while (x && s[x + 1] != c) x = pi[x];

				if (s[x + 1] == c) x++;

				nxt[i][j] = x + 1;
			}
		}
	}

	dp[0][1][0] = 1;

	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= m + 1; ++j) {
			for (int cnt = 0; cnt <= 2; ++cnt) if (dp[i][j][cnt]) {
				for (int k = 0; k <= 1; ++k) {
					int nxtj = nxt[j][k];
					int nxtcnt = cnt;

					if (nxtj == m + 1) {
						nxtcnt++;
						if (nxtcnt > 2) nxtcnt = 2;
					}

					dp[i + 1][nxtj][nxtcnt] += dp[i][j][cnt];
					dp[i + 1][nxtj][nxtcnt] %= Mod;
				}
			}
		}
	}

	int ans = 0;

	for (int j = 1; j <= m + 1; ++j) {
		ans += dp[n][j][1];
		if (ans >= Mod) ans -= Mod;
	}

	cout << ans;

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "j"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
