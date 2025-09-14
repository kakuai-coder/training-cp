#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* nxt[26];
    bool isWord;
    int lenWord;

    TrieNode() {
        fill(nxt, nxt + 26, nullptr);
        isWord = false;
        lenWord = 0;
    }
};

TrieNode* root = new TrieNode();
int N, M;
string P;
vector<int> dp;

void insertWord(const string &s) {
    TrieNode* node = root;
    for (char ch : s) {
        int c = ch - 'a';
        if (!node->nxt[c]) node->nxt[c] = new TrieNode();
        node = node->nxt[c];
    }
    node->isWord = true;
    node->lenWord = s.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    cin >> P;

    int Lmax = 0;
    for (int i = 0; i < M; ++i) {
        string word;
        cin >> word;
        insertWord(word);
        Lmax = max(Lmax, (int)word.size());
    }

    dp.assign(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        dp[i] = dp[i - 1];
        TrieNode* node = root;
        for (int j = i; j >= max(1, i - Lmax + 1); --j) {
            int c = P[j - 1] - 'a';
            if (!node->nxt[c]) break;
            node = node->nxt[c];
            if (node->isWord) {
                dp[i] = max(dp[i], dp[j - 1] + node->lenWord);
            }
        }
    }

    cout << (N - dp[N]) << '\n';

    return 0;
}
