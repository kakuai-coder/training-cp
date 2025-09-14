#include <bits/stdc++.h>
using namespace std;

//–– Manacher: tính d1 (odd) và d2 (even) trong O(n) ––
void manacher(const string &s, vector<int> &d1, vector<int> &d2) {
    int n = s.size();
    d1.assign(n,0);
    for(int i=0, l=0, r=-1; i<n; i++){
        int k = i>r ? 1 : min(d1[l+r-i], r-i+1);
        while(i-k>=0 && i+k<n && s[i-k]==s[i+k]) k++;
        d1[i]=k--;
        if(i+k>r) l=i-k, r=i+k;
    }
    d2.assign(n,0);
    for(int i=0, l=0, r=-1; i<n; i++){
        int k = i>r ? 0 : min(d2[l+r-i+1], r-i+1);
        while(i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k]) k++;
        d2[i]=k--;
        if(i+k>r) l=i-k-1, r=i+k;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // nếu có file PADBLE.INP thì redirect
    if (fopen("PADBLE.INP","r")) {
        freopen("PADBLE.INP","r", stdin);
        freopen("PADBLE.OUT","w", stdout);
    }

    string S;
    cin >> S;
    int n = S.size();

    // 1) Manacher để sinh d1, d2
    vector<int> d1, d2;
    manacher(S, d1, d2);

    // 2) prefix‐count để check “có cả 'a' & 'b'” trong O(1)
    vector<array<int,2>> pref(n+1);
    for(int i=0;i<n;i++){
        pref[i+1] = pref[i];
        pref[i+1][ S[i]=='a' ? 0 : 1 ]++;
    }
    auto hasBoth = [&](int l,int r){
        return (pref[r+1][0]-pref[l][0] > 0)
            && (pref[r+1][1]-pref[l][1] > 0);
    };

    // 3) Tạo event evF[k] = { i | S[i..i+k-1] palindrome }
    //           evG[k] = { r | S[r-k+1..r] palindrome }
    //    Sử dụng d1/d2 để liệt kê **chính xác** từng length K ở mỗi center.
    int maxK = n; // ta chỉ dùng k <= n/2 sau này
    vector<vector<int>> evF(maxK+1), evG(maxK+1);

    // odd‐palindromes (length = 2*t-1)
    for(int c=0;c<n;c++){
        for(int t=1; t<=d1[c]; t++){
            int K = 2*t-1;        // độ dài palindrome
            int i = c - (t-1);    // bắt đầu = center-(t-1)
            int r = c + (t-1);    // kết thúc
            // nếu K là “half‐length” ta thêm vào evF/evG
            if (K <= maxK) {
                evF[K].push_back(i);
                evG[K].push_back(r);
            }
        }
    }
    // even‐palindromes (length = 2*t)
    for(int c=0;c<n;c++){
        for(int t=1; t<=d2[c]; t++){
            int K = 2*t;
            int i = c - t;    // bắt đầu
            int r = c + t -1; // kết thúc
            if (K <= maxK) {
                evF[K].push_back(i);
                evG[K].push_back(r);
            }
        }
    }

    // 4) Tham lam: duyệt half‐length k từ lớn xuống
    //    mỗi event chỉ được xử lý một lần
    vector<char> inA(n,0), inB(n,0);
    int bestK = 0;
    for(int k = n/2; k >= 1; --k){
        int L = 2*k;  // full length = 2*k

        // 4.1) đánh dấu B mới, rồi thử ngay với các i đã inA
        for(int r : evG[k]){
            inB[r] = 1;
            int i = r - (L-1);
            if (i >= 0 && inA[i] && hasBoth(i, r)) {
                bestK = k;
                break;
            }
        }
        if (bestK) break;

        // 4.2) đánh dấu A mới, rồi thử ngay với các r đã inB
        for(int i : evF[k]){
            inA[i] = 1;
            int r = i + (L-1);
            if (r < n && inB[r] && hasBoth(i, r)) {
                bestK = k;
                break;
            }
        }
        if (bestK) break;
    }

    if (!bestK) {
        cout << -1 << "\n";
        return 0;
    }

    // 5) Đếm lại số vị trí i thỏa với half‐length = bestK
    int L = 2*bestK, cnt = 0;
    for(int i=0; i+L<=n; i++){
        int r = i + L -1;
        if (inA[i] && inB[r] && hasBoth(i, r))
            cnt++;
    }

    cout << L << " " << cnt << "\n";
    return 0;
}
