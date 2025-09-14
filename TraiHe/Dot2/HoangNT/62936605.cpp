#include <bits/stdc++.h>

using namespace std;

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int ssiz(const T &a) {
	return int(a.size());
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

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 20.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 3e5 + 5;
int n, a[MAXN];
int64_t sum[MAXN];
int pre[MAXN], nxt[MAXN];

void kakuai(void) { 
	cin >> n;
 
	for (int i = 1; i <= n; ++i) cin >> a[i];
 
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
 
	vector<int> st;
 
	for (int i = 1; i <= n; ++i) {
		while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
		pre[i] = st.empty() ? 0 : st.back();
		st.push_back(i);
	}
 
	st.clear();
 
	for (int i = n; i >= 1; --i) {
		while (!st.empty() && a[st.back()] < a[i]) st.pop_back();
 
		nxt[i] = st.empty() ? n + 1 : st.back();
		st.push_back(i);
	}
 
	int64_t ans = 0;
 
	for (int i = 1; i <= n; ++i) {
		int L = pre[i] + 1;
		int R = nxt[i] - 1;
 
		int cntL = i - L + 1;
		int cntR = R - i + 1;
 
		if (cntL <= cntR) {
			for (int j = L; j <= i; ++j) {
				int64_t need = sum[j - 1] + 2LL * a[i];
 
				// pref[i] - pref[j - 1] > 2 * ai -> pref[i] > pref[j - 1] + 2 * ai
 
				int id = upper_bound(sum + i, sum + R + 1, need) - sum;
 
				if (id == R + 1) continue;
 
				ans += (R - id + 1);
			}
		} else {
			for (int j = i; j <= R; ++j) {
				int64_t need = sum[j] - 2LL * a[i];
 
				// pref[j] - pref[i - 1] > 2 * ai > pref[i - 1] < pref[j] - 2 * ai
 
				int id = lower_bound(sum + (L - 1), sum + i, need) - sum;
 
				ans += (id - L + 1);
			}
		}
	}
 
	cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
