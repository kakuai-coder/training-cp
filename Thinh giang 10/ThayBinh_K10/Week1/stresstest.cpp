#include <bits/stdc++.h>

#define TASK "zam"
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
	int n = randInt(1, 100); 
	int m = randInt(1, 1000); 

	int st = randInt(1, n); 
	int en = randInt(1, n); 
	int s = randInt(1, 1000); 

	cout << n << ' ' << m << ' ' << st << ' ' << en << ' ' << s << '\n'; 

	for (int i = 1; i <= n; ++i) cout << randInt(1, 500) << ' '; 
	cout << '\n'; 

	for (int i = 1; i <= n; ++i) { 
		int u = randInt(1, n); 
		int v = randInt(1, n); 

		cout << u << ' ' << v << '\n';
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
