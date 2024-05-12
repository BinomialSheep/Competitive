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
  int x;
  cin >> x;

  // DPで解いてみる
  // i円の買うことが可能ならtrue
  vector<bool> dp(x + 200, false);

  dp[0] = true;
  // たかだか100000*6なので間に合う
  rep(i, x + 1) {
    if (dp[i]) {
      // i円帰るならi+100円～i+105円も買える
      rep(j, 6) dp[i + 100 + j] = true;
    }
  }

  cout << (dp[x] ? 1 : 0) << endl;

  return 0;
}