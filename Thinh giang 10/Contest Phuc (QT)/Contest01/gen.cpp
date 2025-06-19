#include <bits/stdc++.h>

#define CHERRY "4"

using namespace std; 
using namespace chrono; 

using i64 = long long; 

mt19937_64 rng(steady_clock::now().time_since_epoch().count());

i64 randInt(int L, int R) {
	return uniform_int_distribution<i64> (L, R) (rng); 
}

int32_t main() {
	ofstream cout(CHERRY".inp"); 

	int n = randInt(1, 2e5); 
	int q = randInt(1, 2e5); 
	
	cout << n << ' ' << q << '\n'; 

	for (int i = 1; i <= q; ++i) {
		int op = randInt(1, 2); 

		cout << op << ' '; 

		if (op == 1) {
			int x = randInt(1, n); 
			int m = randInt(1, 1e9); 

			cout << x << ' ' << m << " 0 1 0\n"; 
		} else {
			int l = randInt(1, n / 2); 
			int r = randInt(l + 1, n); 

			cout << l << ' ' << r << '\n';
		}
	}

	cout.close(); 
}