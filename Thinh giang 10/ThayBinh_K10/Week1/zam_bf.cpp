#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define el '\n'
#define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TuanM signed main

const int MAXN = 105;
int n, m, w, k, s;
int dist[MAXN];
vector<int> adj[MAXN];
unordered_map<int, unordered_set<int>> visited;
int parent[MAXN][1005];

void bfs() {
    queue<ii> q;
    q.push({w, dist[w]});
    visited[w].insert(dist[w]);
    parent[w][dist[w]] = -1;

    while (!q.empty()) {
        auto [room, curr_dist] = q.front();
        q.pop();

        if (room == k && curr_dist == s) {
            vector<int> path;
            int cur = k, cost = s;
            while (cur != -1) {
                path.pb(cur);
                int prev = parent[cur][cost];
                cost -= dist[cur];
                cur = prev;
            }
            reverse(path.begin(), path.end());

            cout << path.size() << " ";
            for (int r : path) cout << r << " ";
            return;
        }

        for (int next : adj[room]) {
            int new_dist = curr_dist + dist[next];
            if (new_dist <= s && visited[next].find(new_dist) == visited[next].end()) {
                visited[next].insert(new_dist);
                parent[next][new_dist] = room;
                q.push({next, new_dist});
            }
        }
    }

    cout << "-1";
}

TuanM() {
    fastio
		freopen("zam.inp", "r", stdin);
		freopen("zam.ans", "w", stdout);
    cin >> n >> m >> w >> k >> s;

    for (int i = 1; i <= n; i++) {
        cin >> dist[i];
    }

    while (m--) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }

    bfs();

    return 0;
}