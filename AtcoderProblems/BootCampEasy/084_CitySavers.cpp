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
  vector<int> A(n + 1);
  vector<int> B(n);
  rep(i, n + 1) cin >> A[i];
  rep(i, n) cin >> B[i];

  // solve
  // 貪欲に、iをできるだけ倒して余ったらi+1も倒す
  ll ans = 0;
  rep(i, n) {
    if (A[i] >= B[i]) {
      // A[i]を倒しけなければA[i]をできるだけ倒す
      ans += B[i];
    } else {
      // A[i]を倒して余裕があればA[i+1]も倒す
      B[i] -= A[i];
      ans += A[i];
      if (A[i + 1] >= B[i]) {
        // A[i+1]を倒しきれないならできるだけ倒す
        ans += B[i];
        A[i + 1] -= B[i];
      } else {
        // A[i+1]も倒しきれるなら倒して役目終わり
        ans += A[i + 1];
        A[i + 1] = 0;
      }
    }
  }

  // output
  cout << ans << endl;

  return 0;
}