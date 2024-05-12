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
  // in
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  // solve
  // 最小公倍数の時に、総和-nとなる！
  int ans = 0;
  rep(i, n) ans += a[i];
  ans -= n;

  // out
  cout << ans << endl;

  return 0;
}