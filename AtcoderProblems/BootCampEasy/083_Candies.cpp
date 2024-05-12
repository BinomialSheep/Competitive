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
  int n;
  cin >> n;
  vector<vector<int>> A(2, vector<int>(100));
  rep(i, 2) rep(j, n) cin >> A[i][j];

  int ans = 0;

  // solve
  // (0, i)で下に移動する
  rep(i, n) {
    int score = 0;
    for (int j = 0; j <= i; j++) score += A[0][j];
    for (int j = i; j < n; j++) score += A[1][j];
    ans = max(ans, score);
  }

  // output
  cout << ans << endl;

  return 0;
}