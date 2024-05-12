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
  int q, h, s, d;
  cin >> q >> h >> s >> d;
  int n;
  cin >> n;

  // 2リットル買う最安値と、1リットル買う最安値だけ分かればdpしなくていい
  ll p1, p2;
  p1 = min(q * 4, min(h * 2, s));
  p2 = (p1 * 2 <= d) ? p1 * 2 : d;

  ll ans;
  if (n % 2 == 0) {
    ans = p2 * (n / 2);
  } else {
    ans = p2 * (n / 2) + p1;
  }

  cout << ans << endl;

  return 0;
}