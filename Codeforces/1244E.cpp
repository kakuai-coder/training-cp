/*
	Author: Tinhnopro (Tinh nop)
	From: CHV Phu Tho
 */
#include<bits/stdc++.h>

namespace std {
	// optimize min max
	template<typename T1, typename T2> bool maximize(T1 &a, T2 b) { return a < b ? a = b, 1 : 0; }
	template<typename T1, typename T2> bool minimize(T1 &a, T2 b) { return a > b ? a = b, 1 : 0; }
	// vector
	template<typename T, int D> struct vec : public vector<vec<T, D - 1>> {
		static_assert(D >= 1, "Init error");
		template<typename... Args>
			vec(int n = 0, Args... args) : vector<vec<T, D - 1>>(n, vec<T, D - 1>(args...)) {}
	};
	template<typename T> struct vec<T, 1> : public vector<T> {
		vec(int n = 0, T val = T()) : vector<T>(n, val) {}
		template<typename InputIt>
			vec(InputIt first, InputIt last) : vector<T>(first, last) {}
	};
	// size
	template<typename T> int Size(const T &a) {  return a.size(); }
}
using namespace std;

const int MAXN  = 1e5 + 11;

int n;
int64_t k;
int64_t a[MAXN];
int64_t costLeft[MAXN], costRight[MAXN];

void process(void) {
	cin >> n >> k; 
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	

	for (int i = 1; i < n; ++i) {
		costLeft[i] = costLeft[i - 1] + 1ll * i * (a[i] - a[i - 1]);
		// cout << costLeft[i] << ' ';
	}
	// cout << '\n';

	for (int i = n - 2; i >= 0; --i) { 
		costRight[i] = costRight[i + 1] + 1ll * (n - i - 1) * (a[i + 1] - a[i]);
		// cout << costRight[i] << ' ';
	}
	// cout << '\n';
	int64_t ans = (int64_t) 1e18 + 11; 
	for (int i = 0; i < n; ++i) {
		int64_t used = costLeft[i];
		int64_t remain = k - used;
		int l = i, r = n - 1, res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (costRight[mid] <= remain) {
				res = mid;
				r = mid - 1; 
			} else l = mid + 1;
		}
		if (res != -1) {
			int64_t exc = remain - costRight[res];
			int64_t c = a[res] - a[i] - exc / (n - res);
			c = max(0LL, c);
			minimize(ans, c); 
		}
	}

	cout << ans;
}

int32_t main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	#define name "1244E"
	if (fopen(name".inp", "r")) {
		freopen(name".inp", "r", stdin);
		freopen(name".out", "w", stdout);
	}

	// int t; cin >> t; while (t--)
	process();

	cerr << "\nRuntime: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s. Code by Tinhnopro\n";
	return 0;
}