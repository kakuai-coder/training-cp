/*
    Author: kakuai
    created: 2025.07.01 09:10:00
*/
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template <typename T>
bool maximize(T &a, const T &b) { return a < b ? (a = b, true) : false; }

template <typename T>
bool minimize(T &a, const T &b) { return a > b ? (a = b, true) : false; }

int ssize(const string &s) { return static_cast<int>(s.size()); }

void kakuai() {
    string S;
    int m;
    cin >> S >> m;
    int n = ssize(S);

    // lưu trước thứ tự hoán vị của từng (k,d) để tái sử dụng
    map<pair<int,int>, vector<int>> dsort;

    while (m--) {
        int k, d;
        cin >> k >> d;

        // nếu chưa có thì tính perm lần đầu
        if (!dsort.count({k,d})) {
            vector<vector<int>> bucket(d);
            for (int i = 0; i < k; ++i)
                bucket[i % d].push_back(i);
            vector<int> ord;
            for (int i = 0; i < d; ++i)
                ord.insert(ord.end(), bucket[i].begin(), bucket[i].end());
            dsort[{k,d}] = ord;
        }
        auto &perm = dsort[{k,d}];

        // sliding window: i chạy từ 0 → n-k
        for (int i = 0; i + k <= n; ++i) {
            string tmp = S.substr(i, k);
            for (int j = 0; j < k; ++j)
                S[i + j] = tmp[perm[j]];
        }

        // in kết quả sau mỗi phép
        cout << S << "\n";
    }
}

int main() {
    auto t0 = chrono::steady_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    kakuai();

    auto t1 = chrono::steady_clock::now();
    cerr << "Runtime: "
         << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
         << "ms\n";
    return 0;
}
