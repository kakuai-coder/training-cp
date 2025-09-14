/*
Author: kakuai
created: 2025.07.19
*/
#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e5 + 5; 

int n, a[maxN]; 

int _abs(int x) {
	return x < 0 ? -x : x; 
}

namespace subtask1 {
	void solve(void) {
		long long res = 0; 
		for (int i = 1; i <= n; ++i) {
			res = 0;
			for (int j = 1; j <= n; ++j) {
				res += 1LL * _abs(i - j) * _abs(a[i] - a[j]);
			}

			cout << res << ' '; 
		}
	}
};

struct Data {
	long long cnt, sum_idx, sum, sum_prod;
	Data() {
		cnt = sum_idx = sum = sum_prod = 0; 
	}
};

vector<int> v; 

struct fenwicktree {
	Data bit[maxN];
	
	void update1(int idx, int val) {
		int k = v[idx - 1]; 
		for (; idx <= n; idx += idx & -idx) {
			bit[idx].cnt++;
			bit[idx].sum_idx += val; 
			bit[idx].sum += k;
			bit[idx].sum_prod += 1LL * k * val;  
		}
	}

	void update2(int idx, int val) {
		int k = v[idx - 1]; 
		for (; idx; idx -= idx & -idx) {
			bit[idx].cnt++;
			bit[idx].sum_idx += val; 
			bit[idx].sum += k;
			bit[idx].sum_prod += 1LL * k * val;  
		}
	}

	Data query1(int idx) {
		Data res; 
		
		for (; idx; idx -= idx & -idx) {
			res.cnt += bit[idx].cnt; 
			res.sum_idx += bit[idx].sum_idx; 
			res.sum += bit[idx].sum;
			res.sum_prod += bit[idx].sum_prod;
		}

		return res;
	}

	Data query2(int idx) {
		Data res; 
		
		for (; idx <= n; idx += idx & -idx) {
			res.cnt += bit[idx].cnt; 
			res.sum_idx += bit[idx].sum_idx; 
			res.sum += bit[idx].sum;
			res.sum_prod += bit[idx].sum_prod;
		}

		return res;
	}

};

namespace subfull {

	fenwicktree bitL, bitR, bitLL, bitRR;

	int b[maxN];
	long long ans[maxN];

	void solve(void) {

		for (int i = 1; i <= n; ++i) {
			v.push_back(a[i]);
		}

		sort(v.begin(), v.end()); 
		v.erase(unique(v.begin(), v.end()), v.end());

		for (int i = 1; i <= n; ++i) {
			b[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		}

		for (int i = 1; i <= n; ++i) {
			bitL.update1(b[i], i);
			bitLL.update2(b[i], i);
			Data x = bitL.query1(b[i]);
			ans[i] += 1LL * a[i] * i * x.cnt;
			ans[i] += x.sum_prod;
			ans[i] -= 1LL * a[i] * x.sum_idx;
			ans[i] -= 1LL * i * x.sum;

			x = bitLL.query2(b[i] + 1);
			ans[i] -= 1LL * a[i] * i * x.cnt;
			ans[i] -= x.sum_prod;
			ans[i] += 1LL * a[i] * x.sum_idx;
			ans[i] += 1LL * i * x.sum;
		}

		for (int i = n; i >= 1; --i) {
			bitR.update2(b[i], i);
			bitRR.update1(b[i], i);

			Data x = bitR.query2(b[i]);
			ans[i] += 1LL * a[i] * i * x.cnt;
			ans[i] += x.sum_prod;
			ans[i] -= 1LL * a[i] * x.sum_idx;
			ans[i] -= 1LL * i * x.sum;

			x = bitRR.query1(b[i] - 1);
			ans[i] -= 1LL * a[i] * i * x.cnt;
			ans[i] -= x.sum_prod;
			ans[i] += 1LL * a[i] * x.sum_idx;
			ans[i] += 1LL * i * x.sum;
		}
		for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	}

};

void kakuai(void) {
	// voi26 = winner
	cin >> n; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	// subfull::solve();
	if (n <= 1e4) subtask1::solve();

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "seq"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".ans", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	// cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n';

	return 0;
}