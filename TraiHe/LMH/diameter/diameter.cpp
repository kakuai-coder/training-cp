/*
	Author: kakuai
	created: 2025.06.24 
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <typename T> bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T> bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }

const int maxN = 2e5 + 5;
int n;
vector<pair<int,int>> adj[maxN];
i64 dpL[maxN], dpR[maxN], h[maxN], d1_on[maxN], d0_on[maxN];
int on_path[maxN];

pair<int,int> farthest(int src, vector<int> &par, vector<int> &dist) {
		par.assign(n+1, -1);
		dist.assign(n+1, -1);
		queue<int> q;
		dist[src] = 0;
		q.push(src);
		int best = src;
		while (!q.empty()) {
				int u = q.front(); q.pop();
				if (dist[u] > dist[best]) best = u;
				for (auto it : adj[u]) {
						int v = it.first, w = it.second;
						if (dist[v] < 0) {
								dist[v] = dist[u] + w;
								par[v] = u;
								q.push(v);
						}
				}
		}
		return {best, dist[best]};
}

void dfs(int u, int p, i64 acc, int idx) {
		maximize(h[idx], acc);
		for(auto it : adj[u]) {
				int v = it.first, w = it.second;
				if(v != p && !on_path[v])
						dfs(v, u, acc + w, idx);
		}
}

int main(){
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
		cin >> n;

		for(int i = 1, u, v, w; i < n; ++i){
				cin >> u >> v >> w;
				adj[u].emplace_back(v,w);
				adj[v].emplace_back(u,w);
		}

		vector<int> par0, d0;
		pair<int,int> tmp1 = farthest(1, par0, d0);
		int A = tmp1.first;

		vector<int> par1, d1;
		pair<int,int> tmp2 = farthest(A, par1, d1);
		int B = tmp2.first;
		int diam = tmp2.second;

		vector<int> P;
		for(int x = B; x != -1; x = par1[x])
				P.push_back(x);
		reverse(P.begin(), P.end());
		int K = P.size();

		for(int i = 0; i < K; ++i)
				on_path[P[i]] = 1;

		for(int i = 0; i < K; ++i)
				dfs(P[i], 0, 0, i);

		for(int i = 1; i < K; ++i){
				for(auto it : adj[P[i]]) {
						int v = it.first, w = it.second;
						if(v == P[i-1]){
								d0_on[i] = d0_on[i-1] + w;
								break;
						}
				}
		}

		for(int i = K-2; i >= 0; --i){
				for(auto it : adj[P[i]]) {
						int v = it.first, w = it.second;
						if(v == P[i+1]){
								d1_on[i] = d1_on[i+1] + w;
								break;
						}
				}
		}

		dpL[0] = max(i64(0), h[0]);

		i64 bestA = h[0] - d0_on[0];
		for(int i = 1; i < K; ++i){
				dpL[i] = dpL[i-1];
				i64 Ai = h[i] - d0_on[i];
				i64 Bi = h[i] + d0_on[i];
				dpL[i] = max(dpL[i], bestA + Bi);
				bestA = max(bestA, Ai);
		}

		dpR[K-1] = max(i64(0), h[K-1]);
		bestA = h[K-1] - d1_on[K-1];
		for(int i = K-2; i >= 0; --i){
				dpR[i] = dpR[i+1];
				i64 Ai = h[i] - d1_on[i];
				i64 Bi = h[i] + d1_on[i];
				dpR[i] = max(dpR[i], bestA + Bi);
				bestA = max(bestA, Ai);
		}

		i64 ans = (i64) 1e18 + 11;

		for(int i = 0; i+1 < K; ++i){
				ans = min(ans, max(dpL[i], dpR[i+1]));
		}

		cout << ans << "\n";
		return 0;
}
