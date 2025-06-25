/*
	Author: kakuai
	created: 2025.06.21 15:34:59
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

struct Query {
    int l1, r1, l2, r2, id;
};
 
const int maxN = 50000 + 5;
int n, q;
int a[maxN];
long long ans[maxN];
long long cur = 0;
long long freq1[maxN], freq2[maxN];
 
void add1(int i) {
	cur += freq2[a[i]];
	freq1[a[i]]++;
}
void remove1(int i) {
	freq1[a[i]]--;
	cur -= freq2[a[i]];
}
void add2(int j) {
	cur += freq1[a[j]];
	freq2[a[j]]++;
}
void remove2(int j) {
	freq2[a[j]]--;
	cur -= freq1[a[j]];
}
 
void kakuai() {
	cin >> n;
	for(int i = 1; i <= n; i++){
			cin >> a[i];
	}
	cin >> q;
	vector<Query> qs(q);
	for(int i = 0; i < q; i++){
			cin >> qs[i].l1 >> qs[i].r1 >> qs[i].l2 >> qs[i].r2;
			qs[i].id = i;
	}

	int B = 1200;
	sort(qs.begin(), qs.end(), [&](Query &A, Query &Bq){
		int b1 = A.l1 / B, b2 = Bq.l1 / B;
		if(b1 != b2) return b1 < b2;
		int c1 = A.l2 / B, c2 = Bq.l2 / B;
		if(c1 != c2) return c1 < c2;
		if(A.r1 != Bq.r1) return A.r1 < Bq.r1;
		return A.r2 < Bq.r2;
	});

	int L1 = 1, R1 = 0, L2 = 1, R2 = 0;

	for(auto &qq : qs) {
		while(R1 < qq.r1) add1(++R1);
		while(R1 > qq.r1) remove1(R1--);
		while(L1 < qq.l1) remove1(L1++);
		while(L1 > qq.l1) add1(--L1);

		while(R2 < qq.r2) add2(++R2);
		while(R2 > qq.r2) remove2(R2--);
		while(L2 < qq.l2) remove2(L2++);
		while(L2 > qq.l2) add2(--L2);

		ans[qq.id] = cur;
	}

	for(int i = 0; i < q; i++){
			cout << ans[i] << "\n";
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