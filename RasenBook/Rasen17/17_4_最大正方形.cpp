#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  // input
  int H, W;
  cin >> H >> W;
  vector<vector<int>> c(H, vector<int>(W));
  rep(i, H) rep(j, W) cin >> c[i][j];

  // solve
  // dp[i][j]は、i, j始まりで左上に見た時の最大の正方形の長さ
  //面積ではなく長さ。0 origin。
  vector<vector<int>> dp(H, vector<int>(W, 0));
  // init
  // 1行目、1列目はそのマスが綺麗なら1, 汚れていれば0
  rep(i, H) dp[i][0] = (c[i][0] == 0 ? 1 : 0);
  rep(j, W) dp[0][j] = (c[0][j] == 0 ? 1 : 0);
  // recurse
  // 2行目以降は漸化的にmin(左上、左、上)+1になる
  // ↑綺麗なタイルなら。汚ければ当然0
  for (int i = 1; i < H; i++) {
    for (int j = 1; j < W; j++) {
      if (c[i][j] == 1) continue;
      dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
    }
  }
  // find
  int maxLength = 0;
  rep(i, H) rep(j, W) maxLength = max(maxLength, dp[i][j]);

  // output
  cout << maxLength * maxLength << endl;

  return 0;
}