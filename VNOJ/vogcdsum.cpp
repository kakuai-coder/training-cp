/*
	Author: Tinhnopro (Tinh nop)
	From: CHV Phu Tho
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T, int D>
struct vec : public vector<vec<T, D - 1>> {
	static_assert(D >= 1, "Init Error");
	template <typename... Args>
	vec(int n = 0, Args... args) : vector<vec<T, D - 1>>(n, vec<T, D - 1>(args...)) {}
};

template <typename T>
struct vec<T, 1> : public vector<T> {
	vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};

template <typename T>
using tpair = pair<T, T>;

template <typename T>
int Size(const T &a) { return a.size(); }

template <typename T1, typename T2>
bool maximize(T1 &a, T2 b) {
	return a < b ? a = b, true : false;
}

template <typename T1, typename T2>
bool minimize(T1 &a, T2 b) {
	return a > b ? a = b, true : false;
}
// End of tempalte
const int MAXN = 1e5 + 11; 
const int MOD = 1e9 + 7; 

int n;
int64_t a[MAXN];

int64_t gcd(int64_t a, int64_t b) {
	int64_t r;
	while (b) {
		r = a % b; 
		a = b;
		b = r;
	}
	return a;
}

struct RMQ {
	static const int LOG = 20;
	int64_t st[LOG + 1][MAXN];

#define MASK(x) (1 << (x))

	void init(void) {
		for (int i = 1; i <= n; ++i) {
			st[0][i] = a[i];
		}
		for (int j = 1; j <= LOG; ++j) {
			for (int i = 1; i + MASK(j) - 1 <= n; ++i) {
				st[j][i] = gcd(st[j - 1][i], st[j - 1][i + MASK(j - 1)]);
			}
		}
	}

	int64_t Get(int l, int r) {
		int k = __lg(r - l + 1);
		return gcd(st[k][l], st[k][r - MASK(k) + 1]);
	}
} rmq;

void add(int &a, int b) {
	a += b; 
	if (a >= MOD) a -= MOD;
}

void Tinhnopro(void) {
	cin >> n; 
	for (int i = 1; i <= n; ++i) cin >> a[i];
	rmq.init();
	int ans = 0;
	for (int i = 1; i <= n; ++ i) {
		int j = i;
		while (j <= n) {
			int l = j, r = n, far = -1; 
			while (l <= r) {
				int mid = (l + r) >> 1; 
				if (rmq.Get(i, mid) == rmq.Get(i, j)) {
					far = mid;
					l = mid + 1; 
				} else r = mid - 1;  
			}
			add(ans, 1ll * (far - j + 1) * rmq.Get(i, j) % MOD);
			j = far + 1;
		}
	}
	cout << ans;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#define name "vogcdsum"
	if (fopen(name".inp", "r"))
		freopen(name".inp", "r", stdin),
		freopen(name".out", "w", stdout);

	// int t; cin >> t; while (t--)
	Tinhnopro();

	cerr << "\nRuntime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s \n";
	return 0;
}
