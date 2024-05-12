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
  ll a, b, c, x, y;
  cin >> a >> b >> c >> x >> y;
  /* solve */
  // AとBだけ買う
  if (a + b <= 2 * c) {
    cout << a * x + b * y << endl;
    return 0;
  }
  // ABとAを買う
  if (x >= y && a < 2 * c) {
    cout << a * (x - y) + c * 2 * y << endl;
    return 0;
  }
  // ABとBを買う
  if (x < y && b < 2 * c) {
    cout << c * 2 * x + b * (y - x) << endl;
    return 0;
  }

  // ABを買って捨てる
  cout << c * 2 * llMax(x, y) << endl;

  /* output */

  return 0;
}