/*
	Author: kakuai
	created: 2025.06.20 16:00:49
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

const int maxN = 2e5 + 5; 

int n, q;
string a[maxN]; 
set<int> s1[4 * maxN]; 
set<int> s2[4 * maxN];
pair<int, int> seg[maxN]; 

void update(int id, int l, int r, int u, int v, int val) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {

		s1[id].insert(val);
		
		return ;
	}

	s2[id].insert(val);

	int mid = (l + r) >> 1; 
	update(id << 1, l, mid, u, v, val); 
	update(id << 1 | 1, mid + 1, r, u, v, val); 
}

void update2(int id, int l, int r, int u, int v, int val) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {

		s1[id].erase(val);
		
		return ;
	}

	s2[id].erase(val);

	int mid = (l + r) >> 1; 
	update2(id << 1, l, mid, u, v, val); 
	update2(id << 1 | 1, mid + 1, r, u, v, val); 
}

int get_min(set<int> &s) {
	return (*s.begin());
}

int query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return q + 1;
	
	int ret = q + 1; 

	if (u <= l && r <= v) {
		
		if (s1[id].size()) minimize(ret, get_min(s1[id]));
		if (s2[id].size()) minimize(ret, get_min(s2[id]));

		return ret;
	}

	if (s1[id].size()) {
		minimize(ret, get_min(s1[id]));
	}

	int mid = (l + r) >> 1; 

	int res1 = query(id << 1, l, mid, u, v); 
	int res2 = query(id << 1 | 1, mid + 1, r, u, v); 

	minimize(ret, min(res1, res2)); 


	return ret; 
}


void kakuai() {
	cin >> n >> q; 
	
	int id = q + 1; 

	for (int _ = 1; _ <= q; ++_) {
		int type; 
		cin >> type; 
		if (type == 1) {
			string name; 
			int l, r; 
			cin >> name >> l >> r; 
			id--; 
			a[id] = name;
			update(1, 1, n, l, r, id);
			seg[id] = {l, r};
		} else {
			int l, r; 
			cin >> l >> r; 
			int idx = query(1, 1, n, l, r); 
			if (idx == q + 1) {
				cout << -1 << '\n'; 
				continue;
			}
			cout << a[idx] << '\n';
			// cerr << idx << ' ' << seg[idx].first << ' ' << seg[idx].second << '\n';
			update2(1, 1, n, seg[idx].first, seg[idx].second, idx);
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}