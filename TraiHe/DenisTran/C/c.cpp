/*
	Author: kakuai
	created: 2025.06.23 12:45:38
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int MOD = 1e9 + 7;
const int oo = 1e18;
const int maxN = 1e5 + 5;

int n , K , D;
int h[maxN];
int t[maxN];
int dp[maxN];

struct SegTree {
	int n0;
	vector<int> st;
	void init(int _n) {
		n0 = 1;
		while (n0 < _n) n0 <<= 1;
		st.assign(2*n0, -oo);
	}
	void upd(int pos, int val) {
		pos += n0;
		st[pos] = val;
		for (pos >>= 1; pos; pos >>= 1)
			st[pos] = max(st[pos<<1], st[pos<<1|1]);
	}
	int get(int L, int R) {
		if (L > R) return -oo;
		L += n0; R += n0;
		int res = -oo;
		while (L <= R) {
				if (L & 1) res = max(res, st[L++]);
				if (!(R & 1)) res = max(res, st[R--]);
				L >>= 1; R >>= 1;
		}
		return res;
	}
};

vector <int> reach[maxN];
SegTree st1, st2;
vector <multiset<int>> mul1 , mul2;


void kakuai() {
	cin >> n >> K >> D;

	for(int i = 1 ; i <= n ; i ++){
		cin >> h[i];
	}

	for(int i = 1 ; i < n ; i ++){
		cin >> t[i];
	}
	for (int i = 1; i < n; i++) {
		reach[i + t[i] + 1].push_back(i);
	}

	for (int i = 1; i <= n; i++){
		dp[i] = -oo;
	}
	dp[1] = h[1];

	st1.init(K);
	st2.init(K);
	mul1.resize(K);
	mul2.resize(K);

	int B = 1 / K;
	int m = 1 % K;
	int U = dp[1] + B * D;
	int W = dp[1] + (B + 1) * D;
	mul1[m].insert(U);
	mul2[m].insert(W);
	st1.upd(m, U);
	st2.upd(m, W);

	for (int i = 2; i <= n; i++) {
		for (int j : reach[i]) {
			int mj = j % K;
			int Bj = j / K;
			int Uj = dp[j] + Bj * D;
			int Wj = dp[j] + (Bj + 1) * D;
			mul1[mj].erase(mul1[mj].find(Uj));
			mul2[mj].erase(mul2[mj].find(Wj));
			int vU = mul1[mj].empty() ? -oo : *mul1[mj].rbegin();
			int vW = mul2[mj].empty() ? -oo : *mul2[mj].rbegin();
			st1.upd(mj, vU);
			st2.upd(mj, vW);
		}
		int A = i / K;
		int r = i % K;
		int best1 = st1.get(0, r);
		int best2 = st2.get(r+1, K-1);
		int best = max(best1, best2);
		if (best <= -oo/2) {
			dp[i] = -oo;
		} else {
				dp[i] = h[i] + best - A * D;
				int Bi = i / K, mi = r;
				int Ui = dp[i] + Bi * D;
				int Wi = dp[i] + (Bi + 1) * D;
				mul1[mi].insert(Ui);
				mul2[mi].insert(Wi);
				st1.upd(mi, *mul1[mi].rbegin());
				st2.upd(mi, *mul2[mi].rbegin());
		}
	}

	cout << dp[n];
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry ""
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}