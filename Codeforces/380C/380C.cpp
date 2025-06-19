/*
	Author: tinhnopro
	created: 04.01.2025 08:10:49
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK ""

using namespace std;

using i64 = long long;

const int maxN = 1e6 + 5; 

struct Node {
	int op, cl, cnt; 
	
	Node() : op(0), cl(0), cnt(0) {}

	Node(int _op, int _cl, int _cnt) : 
		op(_op), cl(_cl), cnt(_cnt) {}
};

string s; 
int q, n;
Node st[4 * maxN];  

void build(int id, int l, int r) {
	if (l == r) {
		
	}
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> s >> q; 
	for (int l, r; q; q--) {
		cin >> l >> r; 

	}
}