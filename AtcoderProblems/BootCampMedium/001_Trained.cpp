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
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  /* solve */
  // ループ検出してもいいが、まぁn回回して到達しないなら絶対到達しない
  int shining = 0;
  rep(i, n) {
    shining = a[shining] - 1;
    if (shining == 1) {
      cout << i + 1 << endl;
      return 0;
    }
  }
  cout << -1 << endl;

  return 0;
}