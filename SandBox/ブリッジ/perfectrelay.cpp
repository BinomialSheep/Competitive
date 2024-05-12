#include <bits/stdc++.h>

// 【フィネ子のperfect relay命題】
// 全アナー配置とシェイプを特定可能なリレーは構築可能か？
// https://twitter.com/NeverPsychic/status/1645950008271990785
int main() {
  // 1Cオープンから可能な全リレーステップ
  const int fib35 = 9227465;

  // あるスートにおけるあり得るアナーの組み合わせを求める関数
  auto f = [](int n) {
    int ret = 0;
    int mx = std::min(4, n);             // アナーの最大枚数
    int mn = std::max(0, n - (13 - 4));  // アナーの最小枚数
    for (int bit = 0; bit < (1 << 4); bit++)
      // 各アナー配置について、あり得るアナー枚数ならインクリメント
      if (mn <= __builtin_popcount(bit) && __builtin_popcount(bit) <= mx) ret++;
    return ret;
  };

  int sum = 0;  // 全シェイプにおけるありうるアナー配置の組み合わせ
  for (int c = 0; c <= 13; c++)
    for (int d = 0; d <= 13; d++)
      for (int h = 0; h <= 13; h++) {
        int s = 13 - c - d - h;
        if (s < 0) continue;
        // そのシェイプにおいてありうるアナー配置の組み合わせを求めて合計に足す
        sum += f(c) * f(d) * f(h) * f(s);
      }

  // 判定結果：Yes 4582640
  printf("%s %d\n", (sum <= fib35 ? "Yes" : "No"), sum);
  return 0;
}
