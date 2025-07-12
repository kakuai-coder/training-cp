/*
	Author: kakuai
	created: 2025.07.04 15:17:31
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5;

int n; 
vector<int> adj[maxN];
int k; 
bool ok;
int rem[maxN];

void dfs(int u, int p) {
	multiset<int> s;
	for (int v : adj[u]) if (v != p && ok) {
		dfs(v, u);
		s.insert(rem[v] + 1);
	}

	while (s.size() > 2) {
		int t = *s.begin();
		s.erase(s.begin());
		auto it = s.lower_bound(k - t);
		if (it == s.end()) {
			if (!rem[u] && u != 1) {
				rem[u] = t;
			} else {
				ok = false;
				break;
			}
		} else {
				s.erase(it);
		}
	}

	if (ssize(s) == 1) {
		if (!rem[u]) {
			rem[u] = *s.begin();
		} else {
			ok = false;
		}
	} else if (ssize(s) == 2) {
		if (rem[u]) {
			if (*s.begin() + *prev(s.end()) < k) {
				ok = false;
			}
		} else {
			if (*s.begin() >= k && u != 1) {
				rem[u] = *prev(s.end());
			} else if (*prev(s.end()) >= k && u != 1) {
				rem[u] = *s.begin();
			} else {
				if (*s.begin() + *prev(s.end()) < k) {
					ok = false;
				}
			}
		}
	}
}


bool can(int x) {
	memset(rem, 0, sizeof(rem));
	k = x; 

	ok = true; 

	dfs(1, 0);

	if (ok && (rem[1] >= k || rem[1] == 0)) return true; 
	return false; 
}

void kakuai() {
	cin >> n; 
	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	int l = 0, r = n + 1;

	while (r - l > 1) {
		int mid = (l + r) >> 1;

		if (can(mid)) {
			l = mid;
		} else r = mid; 
	}

	cout << l;
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "C"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}