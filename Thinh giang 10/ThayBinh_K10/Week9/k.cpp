/*
Author: kakuai
created: 7.8.2025
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int size32(const T &a) {
	return (int)a.size();
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

}  // namespace std

const int MaxN = 2e5 + 5;

int n;
int64_t L, depth[MaxN];
vector<int> adj[MaxN];
multiset<int64_t> sack[MaxN];
int ans[MaxN];

void dfs(int u) {
    sack[u].insert(depth[u]);

    for (int v : adj[u]) {
        dfs(v);

        if (sack[u].size() < sack[v].size()) {
            swap(sack[u], sack[v]);
        }

        for (auto d : sack[v]) {
            sack[u].insert(d);
        }

        sack[v].clear();
    }

    while (!sack[u].empty() && *sack[u].rbegin() > depth[u] + L) {
        sack[u].erase(prev(sack[u].end()));
    }

    ans[u] = size32(sack[u]);
}

void kakuai(void) {
    cin >> n >> L;

    for (int i = 2; i <= n; ++i) {
        int p;
        int64_t w;
        cin >> p >> w;
        adj[p].push_back(i);
        depth[i] = depth[p] + w;
    }

    dfs(1);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
}

int32_t main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#define cherry "k"
    if (fopen(cherry ".inp", "r")) {
        freopen(cherry ".inp", "r", stdin);
        freopen(cherry ".out", "w", stdout);
    }

    // int Ntest; cin >> Ntest; while (Ntest--)
    kakuai();

    return 0;
}
