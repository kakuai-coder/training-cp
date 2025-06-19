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


void process(void) {
	int n; cin >> n;
	cout << (n % 2 == 1 ? "Kosuke\n" : "Sakurako\n");
}

int32_t main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	#define name "a"
	if (fopen(name".inp", "r")) {
		freopen(name".inp", "r", stdin);
		freopen(name".out", "w", stdout);
	}

	int t; cin >> t; while (t--)
	process();

	cerr << "\nRuntime: " << (1.0 * clock() / CLOCKS_PER_SEC) << "s. Code by Tinhnopro\n";
	return 0;
}
