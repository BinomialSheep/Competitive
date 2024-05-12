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
  vector<int> h(n);
  rep(i, n) cin >> h[i];

  for (int i = n - 1; i >= 1; i--) {
    // 右から確定していく
    if (h[i - 1] <= h[i]) {
      continue;
    } else if (h[i - 1] - 1 == h[i]) {
      h[i - 1]--;
    } else {
      // cout << h[i - 1] << " " << h[i] << " " << i << endl;
      //  h[i-1]の方が2以上大きかったらどうしようもない
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;

  return 0;
}