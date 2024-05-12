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
  const int MOD = 998244353;

  // 直前の最小桁がvec[i]である個数(1-origin)
  vector<int> vec(10, 1);
  // 退避用
  vector<int> copy(10, 1);
  // n-1回やればいいn桁目が求まる
  for (int i = 1; i < n; i++) {
    rep(j, 10) copy[j] = vec[j];

    // 例えば1は、直前が1の場合と2の場合がある
    vec[1] = (copy[1] + copy[2]) % MOD;
    vec[9] = (copy[8] + copy[9]) % MOD;
    // 例えば2は、直前が1の場合と2の場合と3の場合がある
    for (int k = 2; k <= 8; k++) {
      vec[k] = ((copy[k - 1] + copy[k]) % MOD + copy[k + 1]) % MOD;
    }
  }

  int ans = 0;
  for (int i = 1; i < 10; i++) {
    ans = (ans + vec[i]) % MOD;
  }
  cout << ans % MOD << endl;

  return 0;
}