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
  int n;
  cin >> n;
  int x = 0, y = 0, t = 0;
  rep(i, n) {
    int ti, xi, yi;
    cin >> ti >> xi >> yi;
    // マンハッタン距離
    int dd = abs(x - xi) + abs(y - yi);
    int dt = ti - t;
    // 判定
    if (dt - dd >= 0 && (dt - dd) % 2 == 0) {
      x = xi;
      y = yi;
      t = ti;
    } else {
      cout << "No" << endl;
      return 0;
    }
  }

  /* solve */

  /* output */
  cout << "Yes" << endl;

  return 0;
}