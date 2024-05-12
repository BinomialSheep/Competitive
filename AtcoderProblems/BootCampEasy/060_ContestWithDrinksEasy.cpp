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
  int n;
  cin >> n;
  vector<int> T(n);
  rep(i, n) cin >> T[i];
  int sum = 0;
  rep(i, n) sum += T[i];

  int m;
  cin >> m;
  vector<int> ans(m);
  int p, x;
  rep(i, m) {
    cin >> p >> x;
    ans[i] = sum - T[p - 1] + x;
  }

  rep(i, m) cout << ans[i] << endl;

  return 0;
}