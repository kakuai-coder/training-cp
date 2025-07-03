#include <bits/stdc++.h>

using namespace std;

#define el '\n'
#define TASK ""
#define int long long

const int MAXN = 2e5 + 5;

int n , m;
struct Data{
	int u , v , w , id;
} edge[MAXN];
int TM;
int par[MAXN];
bool res[MAXN];
vector <int> d , low;
int timer;
vector <vector <pair <int , int>>> adj;

bool cmp(Data a , Data b){
	return a.w < b.w;
}

void make_set(int node){
	par[node] = node;
}

int find_set(int node){
	if (par[node] != node) par[node] = find_set(par[node]);
	return par[node];
}

void union_set(int a , int b){
	a = find_set(a);
	b = find_set(b);
	if (a != b){
		if (a > b) swap(a , b);
		par[a] = b;
	}
}

void tarjan(int u , int id){
    d[u] = low[u] = ++ timer; 
    for(auto x : adj[u]){
        int v = x.first;
        int new_id = x.second;
        if (id != new_id){
            if (d[v] == 0){
            	tarjan(v , new_id);
            	if (low[v] > d[u]){
                	res[edge[new_id].id] = 1;
                }
                low[u] = min(low[u] , low[v]);
            } else {
				low[u] = min(low[u] , low[v]);                
            }
        }
    }
}

signed main(){
	if (fopen(TASK".inp" , "r")){
    	freopen(TASK".inp" , "r" , stdin); 
    	freopen (TASK".out" , "w" , stdout); 
	}

    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for(int i = 1 ; i <= m ; i ++){	
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
		edge[i].id = i;
	}

	for(int i = 1 ; i <= n ; i ++){
		make_set(i);
	}

	sort(edge + 1 , edge + m + 1 , cmp);

	int l = 1;

	while(l <= m){
		int r = l;
		while(r <= m && edge[r].w == edge[l].w){
			r ++;
		}
		r --;
		TM = 0;
		vector <int> zip;
	    zip.reserve(2 * (r - l + 1));
	    for(int i = l; i <= r; i++){
	        int pu = find_set(edge[i].u);
	        int pv = find_set(edge[i].v);
	        if(pu != pv){
	            zip.push_back(pu);
	            zip.push_back(pv);
	        }
	    }
	    sort(zip.begin(), zip.end());
	    zip.erase(unique(zip.begin(), zip.end()), zip.end());
	    TM = zip.size();

	    adj.assign(TM, {});
	    d.assign(TM, 0);
	    low.assign(TM, 0);
	    timer = 0;

	    for(int i = l; i <= r; i++){
	        int pu = find_set(edge[i].u);
	        int pv = find_set(edge[i].v);
	        if(pu == pv) continue;
	        int cu = lower_bound(zip.begin(), zip.end(), pu) - zip.begin();
	        int cv = lower_bound(zip.begin(), zip.end(), pv) - zip.begin();
	        adj[cu].emplace_back(cv, i);
	        adj[cv].emplace_back(cu, i);
	    }
		for(int i = 0 ; i < TM ; i ++){
			if (d[i] == 0){
				tarjan(i , -1);
			}
		}
		for(int i = l ; i <= r ; i ++){
			union_set(edge[i].u , edge[i].v);
		}
		l = r + 1;
	}

	for(int i = 1 ; i <= m ; i ++){
		if (res[i] == 0) cout << "No ";
		else cout << "Yes ";
	}
    
    return 0;
}
