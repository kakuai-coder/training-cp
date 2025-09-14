#include <bits/stdc++.h>

using namespace std;

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int ssiz(const T &a) {
	return int(a.size());
}

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
	static_assert(D >= 1, "Error");
	template <typename... Args>
	Vec(int n = 0, Args... args)
		: vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};
template <typename T>
struct Vec<T, 1> : public vector<T> {
	Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 24.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5; 

int n, q, a[MAXN];
set<int> s[MAXN], f; 
int smax[MAXN], smin[MAXN], sc[MAXN], cnt[MAXN], freq[MAXN];


void add(int x) {
	int d = cnt[x]; 
	s[d].erase(x);
	freq[d]--; 

	if (freq[d] == 0) f.erase(d);
	
	cnt[x]++;

	s[d + 1].insert(x); 

	freq[d + 1]++; 
	if (freq[d + 1] == 1) {
		f.insert(d + 1);
	}
}

void remove(int x) {
	int d = cnt[x];
	s[d].erase(x); 
	freq[d]--;

	if (freq[d] == 0) f.erase(d);

	cnt[x]--; 

	s[d - 1].insert(x); 

	freq[d - 1]++; 
	if (freq[d - 1] == 1) f.insert(d - 1);
}

void kakuai(void) { 
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) s[0].insert(i); 
	f.insert(0);
	freq[0] = n;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		add(a[i]);
	}	 

	while (q--) {
		int idx, x;
		cin >> idx >> x; 

		int id = 0; 

		remove(a[idx]); 
		a[idx] = x;
		add(a[idx]);

		for (int val : f) {
			if (val == 0) continue;

			id++; 
			sc[id] = val; 
			smax[id] = *s[val].rbegin();
			smin[id] = *s[val].begin();
		}

		for (int i = id - 1; i >= 1; --i) smax[i] = max(smax[i], smax[i + 1]);

		int ans = 0; 

		for (int i = 1, j = id; i <= id; ++i) {
			int range = sc[id] - sc[i];

			while (j && sc[j] >= range) {
				--j;
			}

			j++;

			if (sc[j] >= range) maxim(ans, smax[j] - smin[i]);
		}

		cout << ans << '\n';
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
