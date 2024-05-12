#include <bits/stdc++.h>
using namespace std;

void solve() {
  // 入力
  int N, K;
  cin >> N >> K;
  vector<int> S(N);
  for (int i = 0; i < N; i++) cin >> S[i];

  // 商品の形ごとの個数を数える
  map<int, int> mp;
  for (int i = 0; i < N; i++) {
    mp[S[i]]++;
  }

  // YESで初期化し、NOか判定する
  string ans = "YES";
  // 商品が2×Kよりも多い場合、NO
  if (N > K * 2) ans = "NO";
  for (auto p : mp) {
    // 同じ形の商品が3個以上ある場合、NO
    if (p.second > 2) ans = "NO";
  }

  // 出力
  cout << ans << "\n";
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
  return 0;
}