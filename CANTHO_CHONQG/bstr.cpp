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
// > kakuai < <cherry> >> 01.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());


void kakuai(void) { 
	int n; 
	cin >> n; 
	vector<char> a(n + 1), b(n + 1); 

	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	for (int i = 1; i <= n; ++i) cin >> b[i]; 

	vector<int> pos0, pos1; 

	for (int i = 1; i <= n; ++i) if (a[i] != b[i]) {
		if (a[i] == '0') pos0.push_back(i); 
		else pos1.push_back(i);
	} 

	if ((pos0.size() + pos1.size()) & 1) {
		cout << -1; 
		return ; 
	}

	vector<pair<int, int> > ans; 
	
	for (size_t i = 0; i < pos0.size(); i += 2) {
		if (i + 1 == pos0.size()) continue;
		ans.emplace_back(pos0[i], pos0[i + 1]);
	}

	for (size_t i = 0; i < pos1.size(); i += 2) {
		if (i + 1 == pos1.size()) continue;
		ans.emplace_back(pos1[i], pos1[i + 1]);
	}

	if ((pos0.size()) & 1) {
		ans.emplace_back(pos0.back(), pos0.back());
		ans.emplace_back(pos0.back(), pos1.back());
	}

	cout << ans.size() << '\n'; 

	for (auto &an : ans) {
		cout << an.first << ' ' << an.second << '\n';
	}
	
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	fio("bstr");

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
