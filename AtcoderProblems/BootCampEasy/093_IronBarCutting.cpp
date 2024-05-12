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
  // in
  int n;
  cin >> n;
  vector<ll> A(n);
  rep(i, n) cin >> A[i];
  // 中間あたりを求める
  ll sum = 0;
  rep(i, n) sum += A[i];
  ll left = 0;
  ll right;
  ll ans = (1LL << 60);
  rep(i, n) {
    left += A[i];
    right = sum - left;

    if (ans > abs(left - right)) {
      ans = abs(left - right);
    }
  }

  cout << ans << endl;

  return 0;
}