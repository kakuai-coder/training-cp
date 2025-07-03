/*
	Author: kakuai
	created: 2025.07.01 13:41:57
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 3e5 + 5; 

int n, l; 

int lab[maxN], freeCnt[maxN];

int findPar(int u) {
	return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
}

bool joinSet(int u, int v) {
	u = findPar(u); 
	v = findPar(v); 

	if (u == v) return false; 

	if (lab[u] > lab[v]) swap(u, v);

	lab[u] += lab[v]; 
	lab[v] = u; 

	freeCnt[u] += freeCnt[v];

	return true; 
}

void kakuai() {
	cin >> n >> l; 
	
	for (int i = 1; i <= l; ++i) {
		lab[i] = -1; 
		freeCnt[i] = 1; 
	}

	for (int i = 1; i <= n; ++i) {
		int A, B; 
		cin >> A >> B; 

		int u = findPar(A); 
		int v = findPar(B); 

		bool ok = false; 

		if (u != v) {
			if (freeCnt[u] + freeCnt[v] > 0) {
				joinSet(u, v); 
				int par = findPar(u);

				freeCnt[par]--;

				ok = true; 
			}
		} else {
			if (freeCnt[u] > 0) {
				freeCnt[u]--;
				ok = true; 
			}
		}

		cout << (ok ? "BOX\n" : "GARBAGE\n");
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}