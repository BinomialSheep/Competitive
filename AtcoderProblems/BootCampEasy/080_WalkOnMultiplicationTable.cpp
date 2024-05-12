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
  ll n;
  cin >> n;
  // 約数を√nまで列挙
  vector<ll> divisorList;
  ll fin = sqrt(n);
  for (ll i = 1; i <= fin; i++) {
    if (n % i == 0) divisorList.push_back(i);
  }
  // 移動回数の最小値を求める
  ll ans = (1LL << 40);
  for (ll divisor : divisorList) {
    // 縦方向にdivisor - 1回、横方向にn / divisor - 1回
    ans = min(ans, divisor + (n / divisor) - 2);
  }

  cout << ans << endl;

  return 0;
}