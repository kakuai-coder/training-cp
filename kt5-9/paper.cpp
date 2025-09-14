#include <bits/stdc++.h>

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define all(v) v.begin(), v.end()
#define debug(x) cerr << #x << ": " << x << "\n"

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int siz(const T &a) {
	return a.size();
}

// > kakuai < <cherry> >> 10.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void kakuai(void) { 
	 
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

#define cherry "paper"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	int T = 1;
	// cin >> T;
	while (T--) {
		kakuai();
		// cout << '\n';
	}

	cerr << '\n' << TIME << "ms";
}