#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <math.h>
#include <map>
#include <algorithm>
#include <set>
#include <bitset>
#include <queue>
#include <cstring>
#include <stack>
#include <iomanip>
#include <assert.h>

#define BIT(x,pos) (((x)>>(pos)) & 1LL)
#define _(x) (1LL<<(x))
#define bitCnt(x) __builtin_popcountll(x)
#define turnOn(x,pos) ((x) = (_(pos)))
#define turnOff(x,pos) ((x) &= ~(_(pos)))
#define flipBit(x,pos) ((x) ^= (_(pos)))
#define lowBit(x) ((x) & (-x))
#define turnAll(x) (_(x)-1LL)

#define name "bedao_r02_tourist"
#define nameTask "bedao_r02_tourist"
#define fastIO ios::sync_with_stdio(false); cin.tie(0);

using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int N = 2E5;
const int INF = 2E9;

bool visited[N+9];
vector<int> adj[N+9];
int nodeA, nodeB;
vector<int> pathNode;
int f[N+9];
int high[N+9];
int n;

bool maximize(int &x, int y)
{
    if (x < y)
    {
        x = y;
        return true;
    }
return false;
}

void pathCreate(int u, int p)
{
    for (int i = 0;i < (int)adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (v == p) continue;

        pathCreate(v, u);

        visited[u] |= visited[v];
    }

    if (visited[u] == 1) pathNode.push_back(u);
}

void dfsUp(int u,int p)
{
    f[u] = 1;
    for (int i = 0;i < (int)adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (v == p) continue;
        high[v] = high[u] + 1;

        dfsUp(v, u);

        if (visited[v] == 1) continue;
        maximize(f[u], f[v] + 1);
    }
}

int main()
{
    if (fopen(name".INP","r"))
        freopen(name".INP","r",stdin),
        freopen(name".OUT","w",stdout);

    fastIO

    cin>>n;

    for (int i = 1;i < n;++i)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cin>>nodeA>>nodeB;

    visited[nodeB] = 1;
    high[nodeA] = 1;

    pathCreate(nodeA,nodeA);
    dfsUp(nodeA, nodeA);

    reverse(pathNode.begin(),pathNode.end());

    for (int x : pathNode) cout << x << " ";

    int res = -INF;

    int distA = 0, distB = 0;
    for (int i = 0;i+1 < (int)pathNode.size(); ++i)
    {
        int u = pathNode[i];
        int v = pathNode[i+1];
        distA = max(distA, high[u] - high[nodeA] + f[u]);
        distB = high[nodeB] - high[v] + f[v];
        maximize(res, min(distA, distB));
    }

    cout<<res;
}
