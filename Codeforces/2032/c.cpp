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

void Tinhnopro(void) {
	int n; cin >> n; 
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	int res = 1e9 + 11; 
	for (int i = 0; i < n; ++i) {
		int k = lower_bound(a.begin(), a.end(), a[i] + a[i + 1]) - a.begin();
		minimize(res, i + n - k);
	}
	cout << res << '\n';
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#define name "c"
	if (fopen(name".inp", "r"))
		freopen(name".inp", "r", stdin),
		freopen(name".out", "w", stdout);

	int t; cin >> t; while (t--)
	Tinhnopro();

	cerr << "\nRuntime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s \n";
	return 0;
}
