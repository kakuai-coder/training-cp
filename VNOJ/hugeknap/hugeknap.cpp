#pragma GCC optimize(3)
#pragma GCC target("avx,avx2")
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

template<typename T> void maximize(T &res, const T &val) { if (res < val) res = val; }
template<typename T> void minimize(T &res, const T &val) { if (res > val) res = val; }

typedef long long ll;
/// ====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====

const int LIM_N = 10011;
const int LIM_W = 1011;

int n, w;
int c[LIM_N], v[LIM_N];
int f[LIM_W];

int calc(int *f, int l = 1, int r = n)
{
	int upper = 0;
	for (int i = l; i <= r; ++i)
		upper += c[i];

	minimize(upper, w);
	for (int s = 0; s <= upper; ++s)
		f[s] = 0;

	for (int i = l; i <= r; ++i)
		for (int s = upper; s >= c[i]; --s)
			maximize(f[s], f[s - c[i]] + v[i]);

	return upper;
}

int L[LIM_W], R[LIM_W];
vector<int> selected;
void trace(int s = w, int l = 1, int r = n)
{
	if (l == r)
	{
		if (s == c[l])
		{
			selected.push_back(l);
		}

		return ;
	}

	int m = (l + r) >> 1;
	int sleft  = calc(L, l, m + 0);
	int sright = calc(R, m + 1, r);

	int mx = -1;
	int pleft = 0;
	int pright = s;
	for (int v = max(0, s - sright); v <= min(s, sleft); ++v)
	{
		if (mx < L[v] + R[s - v])
		{
			mx = L[v] + R[s - v];
			pleft = v;
			pright = s - v;
		}
	}

	trace(pleft , l, m + 0);
	trace(pright, m + 1, r);
}

int main()
{
	int t; cin >> t; while (t--) {
		cin >> n >> w;
		for (int i = 1; i <= n; ++i)
			cin >> c[i];

		for (int i = 1; i <= n; ++i)
			cin >> v[i];
		for (int i = 0; i <= w; ++i) f[i] = 0;
		for (int i = 0; i <= w; ++i) L[i] = 0;
		for (int i = 0; i <= w; ++i) R[i] = 0;
		selected.clear();
		calc(f);
		int res = f[w];
		int weight_used = max_element(f, f + w + 1) - f;

		trace(weight_used);
		cout << res << ' ' << selected.size() << '\n';
		for (int p : selected)
		{
				cout << p << ' ';
		}
		cout << '\n';
	}
	return 0;
}
