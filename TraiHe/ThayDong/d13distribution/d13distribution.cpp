/*
	Author: tinhnopro
	created: 2025.06.15 07:56:40
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5; 

struct Data {
	int x[3]; 

	Data() {
		memset(x, 0, sizeof(x));
	}

	Data(int _a, int _b, int _c) {
		x[0] = _a; 
		x[1] = _b;
		x[2] = _c;
	}

	int cost() {
		return max({x[0], x[1], x[2]}) - min({x[0], x[1], x[2]});
	}
};

int n, k, a[maxN];
vector<Data> cur1, cur2;  
unordered_map<int, int> mp; 

void backtrack(int idx, int sum1, int sum2, int sum3) {
	if (idx == n + 1) {
		cur1.push_back({sum1, sum2, sum3});
		return ; 
	}

	backtrack(idx + 1, sum1 + a[idx], sum2, sum3);
	backtrack(idx + 1, sum1, sum2 + a[idx], sum3);
	backtrack(idx + 1, sum1, sum2, sum3 + a[idx]);
}

void backtrack2(int idx, int sum1, int sum2, int sum3) {
	if (idx == k + 1) {
		cur2.push_back({sum1, sum2, sum3});
		return ;
	}

	backtrack2(idx + 1, sum1 + a[idx], sum2, sum3);
	backtrack2(idx + 1, sum1, sum2 + a[idx], sum3);
	backtrack2(idx + 1, sum1, sum2, sum3 + a[idx]);
}

bool cmp(const Data &a, const Data &b) {
	if (a.x[0] == b.x[0]) {
		if (a.x[1] == b.x[1]) {
			return a.x[2] < b.x[2];
		}
		return a.x[1] < b.x[1];
	}

	return a.x[0] < b.x[0];
}

void tinhnop() {
	cin >> n; 
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		sum += a[i];
	}

	k = n / 2; 

	backtrack(k + 1, 0, 0, 0);
	backtrack2(1, 0, 0, 0);

	sort(cur1.begin(), cur1.end(), cmp);
	sort(cur2.begin(), cur2.end(), cmp);

	int val = sum / 3 + (sum % 3 != 0);

	for (int i = 0; i < ssize(cur2); ++i) mp[cur2[i].x[0]] = i;

	int ans = 1e18 + 11; 

	for (auto &c : cur1) {
		int l = -1, r = ssize(cur2) - 1; 

		while (r - l > 1) {
			int mid = (l + r) / 2; 
			if (cur2[mid].x[0] + c.x[0] >= val) {
				r = mid; 
			} else l = mid;
		}

		int pos = r; 
		
		int last = mp[cur2[pos].x[0]];

		l = pos - 1, r = last;
		while (r - l > 1) {
			int mid = (l + r) / 2; 
			Data d, d1; 
			d.x[0] = cur2[mid].x[0] + c.x[0]; 
			d.x[1] = cur2[mid].x[1] + c.x[1];
			d.x[2] = cur2[mid].x[2] + c.x[2]; 

			d1.x[0] = cur2[mid + 1].x[0] + c.x[0]; 
			d1.x[1] = cur2[mid + 1].x[1] + c.x[1];
			d1.x[2] = cur2[mid + 1].x[2] + c.x[2]; 
			if (d.cost() >= d1.cost()) l = mid; 
			else r = mid; 
 		} 

		Data d;

		d.x[0] = cur2[l].x[0] + c.x[0]; 
		d.x[1] = cur2[l].x[1] + c.x[1];
		d.x[2] = cur2[l].x[2] + c.x[2];
		
		minimize(ans, d.cost()); 

		d.x[0] = cur2[l + 1].x[0] + c.x[0]; 
		d.x[1] = cur2[l + 1].x[1] + c.x[1];
		d.x[2] = cur2[l + 1].x[2] + c.x[2];
		
		minimize(ans, d.cost());

		d.x[0] = cur2[l - 1].x[0] + c.x[0]; 
		d.x[1] = cur2[l - 1].x[1] + c.x[1];
		d.x[2] = cur2[l - 1].x[2] + c.x[2];
		
		minimize(ans, d.cost());
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d13distribution"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}