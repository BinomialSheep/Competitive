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
  vector<ll> a(3 * n);
  rep(i, 3 * n) cin >> a[i];
  //
  sort(a.begin(), a.end());
  ll sum = 0;
  rep(i, n) {
    // 上から2, 4, 6...2nを取る
    sum += a[3 * n - 2 * i - 2];
  }

  // output
  cout << sum << endl;

  return 0;
}