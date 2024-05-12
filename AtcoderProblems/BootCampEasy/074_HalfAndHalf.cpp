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
  int a, b, c, x, y;
  cin >> a >> b >> c >> x >> y;

  int sum1 = a * x + b * y;
  int sum2;
  if (x >= y) {
    sum2 = 2 * c * y + a * (x - y);
  } else {
    sum2 = 2 * c * x + b * (y - x);
  }
  int sum3 = 2 * c * max(x, y);

  cout << min(sum1, min(sum2, sum3)) << endl;

  return 0;
}