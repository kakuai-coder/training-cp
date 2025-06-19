#include <bits/stdc++.h>

#define CHERRY "Bowling"

using namespace std; 

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

using i64 = long long; 

i64 randInt(i64 l, i64 r) {
	return uniform_int_distribution<i64> (l, r) (rng);
}

void gentest() {
	ofstream cout(CHERRY".inp");
	int n = randInt(1, 20); 
	int r = randInt(1, n); 

	cout << n << ' ' << r << '\n';
	
	for (int i = 1; i <= n; ++i) {
		cout << randInt(-20, 20) << ' '; 
	}
}

int32_t main() {
	int num_test = 100;
	for (int i = 1; i <= num_test; ++i) {
		gentest();
		system(CHERRY".exe"); 
		system(CHERRY"_bf.exe"); 

		if (system("fc " CHERRY ".out " CHERRY ".ans") != 0) {
			return 0; 
		}
	}
}