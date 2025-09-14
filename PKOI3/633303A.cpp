#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 04.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 2009; 

int n, m; 
char a[MAXN][MAXN];


void kakuai(void) { 
	cin >> n >> m; 
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	vector<char> ans; 

	set<pair<int, int> > cur, nxt;

	ans.push_back(a[1][1]);

	cur.insert({1, 1});

	for (int i = 1; i <= n + m - 2; ++i) {
		char best = 'z' + 1; 
		nxt.clear();

		for (auto &d : cur) {
			int x = d.first; 
			int y = d.second; 

			if (x + 1 <= n) minim(best, a[x + 1][y]); 
			if (y + 1 <= m) minim(best, a[x][y + 1]);
		}

		for (auto &d : cur) {
			int x = d.first; 
			int y = d.second; 

			if (x + 1 <= n && a[x + 1][y] == best) nxt.insert({x + 1, y}); 
			if (y + 1 <= m && a[x][y + 1] == best) nxt.insert({x, y + 1});
		}

		ans.push_back(best);

		cur.swap(nxt);
	}

	for (auto &x : ans) cout << x; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
