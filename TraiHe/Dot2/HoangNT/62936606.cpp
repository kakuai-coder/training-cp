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

const int MAXN = 3e5 + 5, LOG = 20; 

int n, a[MAXN], mx[LOG + 1][MAXN], nxt[MAXN], pre[MAXN];

int getMax(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1); 

	return max(mx[k][l], mx[k][r - (1 << k) + 1]);
};

int lastR(int L, int R, int val) {
	int lo = L - 1, hi = R + 1, mid; 

	while (hi - lo > 1) {
		mid = (lo + hi) >> 1; 

		if (getMax(L, mid) < val) lo = mid; 
		else hi = mid; 
	}

	return lo; 
}

int lastL(int L, int R, int val) {
	int lo = L - 1, hi = R + 1, mid; 

	while (hi - lo > 1) {
		mid = (lo + hi) >> 1; 
		
		if (getMax(mid, R) < val) hi = mid; 
		else lo = mid; 
	}

	return hi; 
}


void kakuai(void) { 
	cin >> n; 

	int mxVal = 0;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		mx[0][i] = a[i];
		maxim(mxVal, a[i]);
	}

	for (int j = 1; j <= LOG; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
		}
	}

	vector<int> st; 

	for (int i = 1; i <= n; ++i) {
		while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();

		pre[i] = (st.empty() ? 1 : st.back() + 1);

		st.push_back(i);
	}

	st.clear(); 

	for (int i = n; i; --i) {
		while (!st.empty() && a[st.back()] > a[i]) st.pop_back();

		nxt[i] = (st.empty() ? n : st.back() - 1);

		st.push_back(i);
	}

	int64_t ans = 0; 

	for (int i = 1; i <= n; ++i) {
		int L = pre[i]; 
		int R = nxt[i]; 

		for (int d = 1; d <= mxVal / a[i]; ++d) {
			int Left_L = lastL(L, i, a[i] * (d + 1));
			int Left_R = lastL(L, i, a[i] * d) - 1;

			int Right_L = lastR(i, R, a[i] * d) + 1; 
			int Right_R = lastR(i, R, a[i] * (d + 1));

			ans += 1LL * (Left_R - Left_L + 1) * (Right_R - i + 1) * d; 
			ans += 1LL * (Right_R - Right_L + 1) * (i - Left_R) * d; 

			// cout << Left_L << ' ' << Left_R << ' ' << Right_L << ' ' << Right_R << '\n'; 
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
