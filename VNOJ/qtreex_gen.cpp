/**
 * Author: tinhnopro (tinh nop)
 * Created: $TODAY_UTC
 */
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

#define TASK ""

using namespace std;

//mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

inline void setIO() {
	if (fopen(TASK ".inp", "r")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(false);
	setIO();

}
