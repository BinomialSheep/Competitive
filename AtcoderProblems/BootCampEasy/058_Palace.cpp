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
  int n, t, a;
  cin >> n >> t >> a;
  vector<int> h(n);
  rep(i, n) cin >> h[i];
  double best = INFTY;
  int ans = -1;

  rep(i, n) {
    double temperature = (t - h[i] * 0.006);
    if (best > abs(temperature - a)) {
      best = abs(temperature - a);
      ans = i + 1;
    }
  }

  cout << ans << endl;

  return 0;
}