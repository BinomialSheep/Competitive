#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int R, C;
  cin >> R >> C;
  vector<vector<int>> RC(R, vector<int>(C));
  rep(i, R) rep(j, C) cin >> RC[i][j];

  /* solve */
  // Rは総当たり（ビット全探索）
  // Cは独立なので各行を最大にすればいい
  int ans = 0;
  rep(bit, 1 << R) {
    // copy
    vector<vector<int>> copy(R, vector<int>(C));
    rep(i, R) rep(j, C) copy[i][j] = RC[i][j];

    int num = 0;
    // 横の反転操作
    rep(i, R) {
      // i行目を裏返す
      if (bit & (1 << i)) {
        rep(j, C) { copy[i][j] ^= 1; }
      }
    }
    // 縦の最大枚数を数える（単に0と1のmax）
    rep(j, C) {
      int num0 = 0;
      int num1 = 0;
      rep(i, R) {
        if (copy[i][j])
          num1++;
        else
          num0++;
      }
      num += max(num0, num1);
    }
    // cout << bit << ":" << num << endl;
    ans = max(ans, num);
  }

  /* output */
  cout << ans << endl;

  return 0;
}