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
// > kakuai < <cherry> >> 25.08.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 5005, MAXV = 2e4 + 5;
const int64_t INFLL = (int64_t)9e18 + 11; 
const int INF = 1e9 + 11;  

int n, m, k; 

struct Item {
	int64_t price, val; 
};

Item item[MAXN];
int64_t dp[2][MAXV], max_pref[MAXN];

void kakuai(void) { 
	cin >> n >> m >> k;

	k /= 2; 

	int64_t sumPrice = 0;

	for (int i = 1; i <= n; ++i) {
		cin >> item[i].price;
		sumPrice += item[i].price;
	}

	vector<int64_t> vals; 
	vals.push_back(INFLL);

	for (int i = 1; i <= n; ++i) {
		cin >> item[i].val; 
		vals.push_back(item[i].val);
	}

	sort(vals.begin(), vals.end(), greater<int64_t>());
	sort(item + 1, item + n + 1, [](const Item &A, const Item &B) {
		return A.price > B.price;
	});

	vals[0] = 0; 

	for (size_t i = 1; i < vals.size(); ++i) vals[i] += vals[i - 1];

	// for (size_t i = 1; i <= n; ++i) cout << vals[i] << ' ';

	if (sumPrice <= m) {	
		cout << vals[n]; 
		return ; 
	}

	bool finish; 
	for (int i = 0; i < 2; ++i) for (int j = 0; j <= m; ++j) {
		dp[i][j] = -INFLL;
	}
	
	if (k) {
		finish = false; 
		pqmin<int> pq; 
		int64_t sum = 0; 

		for (int i = 1; i <= n; ++i) {
			sum += item[i].val;
			pq.push(item[i].val);

			if ((int)pq.size() > k) {
				sum -= pq.top(); 
				pq.pop();
			}

			max_pref[i] = sum; 

		}

	} else {
		for (int i = 1; i <= n; ++i) max_pref[i] = 0; 
		finish = true;
		dp[(n + 1) & 1][0] = 0; 
	}
	
	int64_t ans = 0, sumsuffix = 0, sumpicksuffix = 0; 

	priority_queue<int> pq; 

	for (int i = n; i; --i) {
		sumsuffix += item[i].price;

		int cur = i & 1; 
		int pre = 1 - cur; 
		int64_t best = -INFLL; 

		for (int j = 0; j <= m; ++j) {
			if (dp[pre][j] != -INFLL && j + item[i].price <= m)
			maxim(dp[cur][j + item[i].price], dp[pre][j] + item[i].val);
			
			maxim(dp[cur][j], dp[pre][j]);

			maxim(best, dp[cur][j]);

			dp[pre][j] = -INFLL;
		}

		if (sumsuffix <= m) {
			pq.push(item[i].val);

			if (n -  i + 1 < k) {
				maxim(ans, vals[n - i + 1]);
			} else {
				if (!finish) {
					maxim(ans, vals[n - i + 1]);
					finish = true;
				} 

				maxim(dp[cur][sumsuffix], sumpicksuffix);

				vector<int> v, tmp;

				for (int t = 1; t < i; ++t) v.push_back(item[t].val);
				
				while (!pq.empty()) {
					v.push_back(pq.top());
					tmp.push_back(pq.top());
					pq.pop();
				}

				for (int x : tmp) pq.push(x); 


				sort(v.begin(), v.end(), greater<int>());

				int d = min(k, (int)v.size());

				int64_t res = 0; 

				for (int j = 0; j < d; ++j) {
					res += v[j];
				}


				maxim(ans, res + sumpicksuffix);
				maxim(best, sumpicksuffix);

				if (!pq.empty()) {
					sumpicksuffix += pq.top(); 
					pq.pop();
				}
			}
		}
		
		maxim(ans, max_pref[i - 1] + best);
	}

	cout << ans; 
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	cin >> T;
	while (T--) {
		kakuai();
		cout << '\n';
	}
}