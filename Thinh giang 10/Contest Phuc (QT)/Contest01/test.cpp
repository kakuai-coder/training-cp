#include <bits/stdc++.h>

#define CHERRY "4"

using namespace std; 

int32_t main() {
	int num_test = 100;
	for (int i = 1; i <= num_test; ++i) {
		system("gen.exe");
		system(CHERRY".exe"); 
		system(CHERRY"_bf.exe"); 

		if (system("fc " CHERRY ".out " CHERRY ".ans") != 0) {
			return 0; 
		}
	}
}