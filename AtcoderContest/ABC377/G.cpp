#include <bits/stdc++.h>
using namespace std;

// Trieの各ノードを表す構造体
struct TrieNode {
  int children[26];  // 子ノードへのインデックス
  int min_length;  // このプレフィックスを持つ文字列の最小長さ

  TrieNode() : min_length(INT32_MAX) {
    for (int i = 0; i < 26; i++) children[i] = -1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;
  vector<string> S(N);
  for (auto &s : S) cin >> s;

  // Trieの初期化
  vector<TrieNode> trie;
  trie.emplace_back();  // ルートノード

  for (int k = 0; k < N; k++) {
    if (k > 0) {
      // 現在の文字列S[k]に対する最小コストを計算
      int min_cost = S[k].size();  // 空文字列への変換コスト

      int node = 0;  // ルートから開始
      for (int l = 0; l < S[k].size(); l++) {
        char c = S[k][l];
        if (trie[node].children[c - 'a'] == -1) {
          break;  // 共通プレフィックスがこれ以上存在しない場合
        }
        node = trie[node].children[c - 'a'];
        if (trie[node].min_length != INT32_MAX) {
          int L = l + 1;  // プレフィックスの長さ
          int cost = (int)S[k].size() + trie[node].min_length - 2 * L;
          if (cost < min_cost) {
            min_cost = cost;
          }
        }
      }
      cout << min_cost << '\n';
    } else {
      // 最初の文字列は空文字列に変換するコストがそのまま
      cout << S[k].size() << '\n';
    }

    // 現在の文字列S[k]をTrieに挿入
    int node = 0;  // ルートから開始
    for (int l = 0; l < S[k].size(); l++) {
      char c = S[k][l];
      if (trie[node].children[c - 'a'] == -1) {
        trie[node].children[c - 'a'] = trie.size();
        trie.emplace_back();
      }
      node = trie[node].children[c - 'a'];
      // このプレフィックスを持つ文字列の最小長さを更新
      if (S[k].size() < trie[node].min_length) {
        trie[node].min_length = S[k].size();
      }
    }
  }
}
