
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        i64 n;
        cin >> n;

        map<int, vector<i64>> groups;
        for (i64 p2 = 1, a = 0; p2 <= n; p2 <<= 1, ++a){
            for (i64 x = p2, b = 0; x <= n; x *= 3, ++b){
                groups[a + b].push_back(x);
            }
        }

        int best = 0;
        for (auto &kv : groups){
            auto &vec = kv.second;
            sort(vec.begin(), vec.end());
            i64 sum = 0;
            int cnt = 0;
            for (i64 x : vec){
                if (sum + x > n) break;
                sum += x;
                ++cnt;
            }
            best = max(best, cnt);
        }

        cout << best << "\n";
    }
    return 0;
}
