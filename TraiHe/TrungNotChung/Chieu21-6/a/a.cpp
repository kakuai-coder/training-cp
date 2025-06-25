/*
  Author: kakuai
  created: 2025.06.21 16:03:01
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename T> bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T> bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
template <class T> int ssize(const T &a) { return a.size(); }
#endif

const int MAXN = 200000;
int n, q;
vector<int> adj[MAXN+1];

void kakuai(){
  cin >> n >> q;
  for(int i = 1; i <= n; i++){
    adj[i].clear();
  }
  for(int i = 1, u, v; i < n; i++){
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> distA(n+1), distB(n+1);
  queue<int> bfs;
  while(q--){
    int a, b;
    cin >> a >> b;

    fill(distA.begin(), distA.end(), -1);
    distA[a] = 0;
    bfs.push(a);
    while(!bfs.empty()){
      int u = bfs.front(); bfs.pop();
      for(int v: adj[u]){
        if(distA[v] == -1){
          distA[v] = distA[u] + 1;
          bfs.push(v);
        }
      }
    }

    fill(distB.begin(), distB.end(), -1);
    distB[b] = 0;
    bfs.push(b);
    while(!bfs.empty()){
      int u = bfs.front(); bfs.pop();
      for(int v: adj[u]){
        if(distB[v] == -1){
          distB[v] = distB[u] + 1;
          bfs.push(v);
        }
      }
    }

    i64 ans = 0;
    for(int i = 1; i <= n; i++){
      ans += min(distA[i], distB[i]);
    }
    cout << ans << "\n";
  }
}

int32_t main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  kakuai();
  return 0;
}
