/*
Author: kakuai
created: 2025.07.18
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

const int maxN = 5009; 
const long long INF = (long long)4e15;
 
int n, m;
long long a[maxN];
long long dp[maxN][maxN], sum[maxN][maxN], g[maxN][maxN];
pair<long long, int> d[maxN];


void kakuai(void) {
	// voi26 = winner
	cin >> n >> m; 
 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		
	}
 
	for (int i = 1; i <= m; ++i) {
		cin >> d[i].first >> d[i].second;	
	}
 
	sort(a + 1, a + n + 1); 
	sort(d + 1, d + m + 1);

	for (int j = 1; j <= m; ++j) {
		sum[0][j] = 0; 
		for (int i = 1; i <= n; ++i) 
			sum[i][j] = sum[i - 1][j] + llabs(a[i] - d[j].first);
	}
 
	dp[0][0] = 0; 

	for (int i = 1; i <= n; ++i) dp[i][0] = INF; 
 
	for (int j = 1; j <= m; ++j) {
		deque<int> dq; 

		for (int i = 0; i <= n; ++i) {
			long long val = dp[i][j - 1] - sum[i][j];
			
			while (!dq.empty() && dp[dq.back()][j - 1] - sum[dq.back()][j] >= val) {
				dq.pop_back();
			}

			dq.push_back(i);

			while (!dq.empty() && dq.front() < i - d[j].second) dq.pop_front();

			int idx = dq.front(); 

			dp[i][j] = sum[i][j] + dp[idx][j - 1] - sum[idx][j];
		}
	}
 
	cout << dp[n][m];
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "ROBOT"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}