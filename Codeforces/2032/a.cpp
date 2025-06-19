/*
    Author: Tinhnopro (a.k.a Tinh nop)
    From: CHV Phu Tho with luv <3
*/
#include <bits/stdc++.h>

using namespace std;


void run_case(void) {
	int n; cin >> n;
	int cnt0 = 0, cnt1 = 0; 
	for (int i = 1; i <= 2 * n; ++i) {
		int x; cin >> x; 
		cnt0 += (x == 0);
		cnt1 += (x == 1);
	}
	cout << (cnt0 % 2 + cnt1 % 2) / 2 << ' ' << min(cnt0, cnt1) << '\n';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#define task "a"
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }

    int tests = 1;
    cin >> tests;
    while (tests--) run_case();
    // cerr << "\nRuntime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s Tinh nop";
}
