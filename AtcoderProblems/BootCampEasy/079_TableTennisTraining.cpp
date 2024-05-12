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
  ll n, a, b;
  cin >> n >> a >> b;
  ll ans = 0;

  if ((b - a) % 2 == 0) {
    // 偶数差なら互いに近づけばいいので簡単
    ans = (b - a) / 2;
  } else {
    // 端に近い方に進む
    if (a - 1 <= n - b) {
      ans = (a - 1) + 1 + (b - 1 - (a - 1 + 1)) / 2;
    } else {
      ans = (n - b) + 1 + (n - a - (n - b + 1)) / 2;
    }
  }

  cout << ans << endl;

  return 0;
}