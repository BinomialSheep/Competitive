#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  cin >> n;
  int X[n];
  rep(i, n) cin >> X[i];

  int ans = 1000 * 1000 * 1000;
  int value;
  for (int i = 1; i <= 100; i++) {
    value = 0;
    rep(j, n) {
      //
      value += (X[j] - i) * (X[j] - i);
    }
    ans = min(ans, value);
  }

  cout << ans << endl;
  return 0;
}