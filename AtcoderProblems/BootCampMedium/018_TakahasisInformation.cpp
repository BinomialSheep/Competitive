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
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  vector<vector<int>> c(3, vector<int>(3));
  rep(i, 3) rep(j, 3) cin >> c[i][j];

  /* solve */
  // a1=0としても一般性は失われない
  // その時、b1,b2,b3が確定するので、a2とa3の整合性だけ判定すればいい
  int a20 = c[1][0] - c[0][0];
  int a21 = c[1][1] - c[0][1];
  int a22 = c[1][2] - c[0][2];
  if (a20 != a21 || a20 != a22) {
    cout << "No" << endl;
    return 0;
  }
  int a30 = c[2][0] - c[1][0];
  int a31 = c[2][1] - c[1][1];
  int a32 = c[2][2] - c[1][2];
  if (a30 != a31 || a30 != a32) {
    cout << "No" << endl;
    return 0;
  }

  /* output */
  cout << "Yes" << endl;

  return 0;
}