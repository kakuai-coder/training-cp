/*
		Author: kakuai
		created: 2025.07.09 14:45:06
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long 

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}
#if __cplusplus < 202002L
template <class T>
int ssize(const T &a) {
	return a.size();
}
#endif
//_____________________________________________________________________________________________

const int maxN = 75;

int n;
int fb[maxN];
int dp[maxN][2][2][maxN], f[maxN][2][2][maxN];
string S;

string bit(int s) {
	string res = "";
	for (int i = 73; i >= 1; --i) {
		if (fb[i] > s && res.empty()) continue;
		if (fb[i] > s) res += '0';
		else {
			s -= fb[i];
			res += '1';
		}
	}
	return res;
}

int sol(int i, int ok, int last, int cnt) {
	if (i == ssize(S)) return cnt;
	if (~dp[i][ok][last][cnt]) return dp[i][ok][last][cnt];
	
	int cur = 0;
	int lim = ok ? 1 : S[i] - '0';

	for (int j = 0; j <= lim; ++j) {
		if (j == 1 && last == 1) continue;
		int nok = ok | (j < lim);
		int ncnt = cnt;
		if (cnt || j) ncnt++;
		cur += sol(i + 1, nok, j, ncnt);
	}
	return dp[i][ok][last][cnt] = cur;
}

int calc(int x) {
	S = bit(x);
	memset(dp, -1, sizeof(dp));
	return sol(0, 0, 0, 0);
}

int cal(int i, int ok, int last, int cnt) {
	if (i == ssize(S)) return cnt;
	if (~f[i][ok][last][cnt]) return f[i][ok][last][cnt];

	int cur = 0;
	int lim = ok ? 1 : S[i] - '0';

	for (int j = 0; j <= lim; ++j) {
		if (j == 1 && last == 1) continue;
		int nok = ok | (j < lim);
		int ncnt = cnt + (j == 1);
		cur += cal(i + 1, nok, j, ncnt);
	}
	return f[i][ok][last][cnt] = cur;
}

void kakuai() {
	cin >> n;

	fb[1] = 1;
	fb[2] = 2;
	for (int i = 3; i < maxN; ++i) fb[i] = fb[i - 1] + fb[i - 2];

	int l = 0, r = 1e15 + 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (calc(mid) <= n) l = mid;
		else r = mid;
	}

	S = bit(l);

	memset(f, -1, sizeof(f));
	int ans = cal(0, 0, 0, 0);

	int len = n - calc(l);
	string t = bit(l + 1);
	int cnt = 0;
	for (int i = 0; i < len; ++i) {
		if (t[i] == '1') cnt++;
	}

	cout << ans + cnt << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "finary"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	kakuai();

	cerr << "\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
