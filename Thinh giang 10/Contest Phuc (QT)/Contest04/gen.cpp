#include <bits/stdc++.h>

#define TASK "QuerySum"
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

	int n = randInt(1, 10);
	
	cout << n << '\n';

	for (int i = 1; i <= n; ++i) cout << randInt(-10, 10) << ' '; 
	cout << '\n'; 
	int q = randInt(1, 10); 

	cout << q << '\n'; 

	for (int i = 1; i <= q; ++i) {
		int type = randInt(1, 2); 
		int l = randInt(1, max(n / 2, 1)); 
		int r = randInt(l + 1, n);

		cout << type << ' ' << l << ' ' << r;

		if (type == 1) cout << ' ' << randInt(1, 10);
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
