#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ii pair<int,int>
#define el '\n'
const ll INF = (ll)1e18;

int m, n;
vector<string> a;
static ll dp[2005][2005][2];
static char parDir[2005][2005][2];
static char parBit[2005][2005][2];
static int b[2005][2005];
int dx[2] = {0, 1}, dy[2] = {1, 0};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

		#define cherry "d5gpath"
		if (fopen(cherry".inp", "r")) {
			freopen(cherry".inp", "r", stdin);
			freopen(cherry".ans", "w", stdout);
		}

    cin >> m >> n;
    a.resize(m);
    for(int i=0;i<m;i++) cin >> a[i];
    int a11 = a[0][0] - '0';
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            b[i][j] = (a[i-1][j-1]-'0') ^ a11;
        }
    }

    for(int i=1;i<=m;i++)
      for(int j=1;j<=n;j++)
        dp[i][j][0] = dp[i][j][1] = INF;

    dp[1][1][0] = 0;
    for(int sum=2; sum<=m+n; sum++){
      for(int i=1; i<=m; i++){
        int j = sum - i;
        if(j<1 || j>n) continue;
        for(int p=0;p<2;p++){
          ll &cur = dp[i][j][p];
          if(j>1){
            ll prev = dp[i][j-1][p];
            if(prev<INF){
              int yj = p ^ b[i][j];
              ll cand = prev + yj;
              if(cand < cur){
                cur = cand;
                parDir[i][j][p] = 0;
                parBit[i][j][p] = p;
              }
            }
          }

          if(i>1){
            for(int q=0;q<2;q++){
              ll prev = dp[i-1][j][q];
              if(prev>=INF) continue;
              // tính x_i khi xuống
              int xi = q ^ b[i-1][j] ^ b[i][j];
              if(xi<0||xi>1) continue;
              ll cand = prev + xi;
              if(cand < dp[i][j][xi]){
                dp[i][j][xi] = cand;
                parDir[i][j][xi] = 1;
                parBit[i][j][xi] = q;
              }
            }
          }
        }
      }
    }

    ll best = min(dp[m][n][0], dp[m][n][1]);
    if(best>=INF){
      cout << -1 << el;
      return 0;
    }

    vector<int> x(m+1,0), y(n+1,0);
    int ci = m, cj = n, cp = (dp[m][n][0]<dp[m][n][1]? 0:1);
    int v = a11 ^ 1;
    while(ci>1 || cj>1){
      x[ci] = cp;
      y[cj] = cp ^ b[ci][cj];
      char d = parDir[ci][cj][cp];
      int pp = parBit[ci][cj][cp];
      if(d==0){
        cj--;
        cp = pp;
      } else {
        ci--;
        cp = pp;
      }
    }

    x[1] = 0;
    y[1] = 0;

    vector<int> bestR, bestC;
    ll bestSum = INF;
    for(int t=0;t<2;t++){
      int r1 = (t==0?0:v);
      int c1 = (t==0?v:0);
      vector<int> R, C;
      for(int i=1;i<=m;i++){
        int ri = x[i] ^ r1;
        if(ri) R.push_back(i);
      }
      for(int j=1;j<=n;j++){
        int cj2 = y[j] ^ c1;
        if(cj2) C.push_back(j);
      }
      ll s = (ll)R.size() + (ll)C.size();
      if(s < bestSum){
        bestSum = s;
        bestR = R;
        bestC = C;
      }
    }

    cout << bestR.size() + bestC.size();

    return 0;
}