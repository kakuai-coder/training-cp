/*
    Author: Tinhnopro (a.k.a Tinh nop)
    From: CHV Phu Tho with luv <3
*/
#include <bits/stdc++.h>

using namespace std;

int n, k;


void run_case(void) {
	cin >> n >> k; 

	if (n == 1) {
		if (k != 1) cout << -1 << '\n';
		cout << 1 << '\n' << 1 << '\n';
		return ;
	}

	int d1 = k - 1; 
	int d2 = n - k;
	if (d2 == 0) {
		cout << -1 << '\n';
		return ;
	}
	if (d1 == 0) {
		cout << -1 << '\n';
		return ;
	}
	if (d1 % 2 != d2 % 2) {
		cout << -1 << '\n';
		return ;
	} 

	if (d1 % 2 == 1) {
		cout << 3 << '\n';
		cout << 1 << " " << k << ' ' << k + 1 << '\n';
		return ;
	} 
	if (d1 % 2 == 0) {
		cout << 5 << '\n';
		cout << 1 << " " << k - 1 << " " << k << " " << k + 1 << " " << k + 2 << "\n";
		return ;
	}
	cout << -1 << "\n";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#define task "b"
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }

    int tests = 1;
    cin >> tests;
    while (tests--) run_case();
    // cerr << "\nRuntime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s Tinh nop";
}
