#include <bits/stdc++.h>

#define TASK "rmindist"
#define TIME ((1.0 * clock()) / CLOCKS_PER_SEC)

using namespace std;

using i64 = long long;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

i64 randInt(i64 l, i64 r) {
	return uniform_int_distribution<i64> (l, r) (rng);
}

char randaz() {
	return char('a' + randInt(0, 25));
}

char randAZ() {
	return char('A' + randInt(0, 25));
}

void gentest() {
	ofstream cout(TASK".inp");

	int m = randInt(1, 20); 
	int n = randInt(1, 20); 

	int A = randInt(1, 200); 
	int B = randInt(1, 200); 

	cout << m << ' ' << n << ' ' << A << ' ' << B << '\n'; 

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << randInt(1, 100) << ' ';
		}
		cout << '\n';
	}

	cout.close();
}

signed main() {
	for (int i = 1; i <= 100; ++i) {
		gentest();

		system(TASK".exe");
		system(TASK"_bf.exe");

		if (system("fc " TASK ".out " TASK ".ans") != 0) {
			return 0;
		}
	}
}
