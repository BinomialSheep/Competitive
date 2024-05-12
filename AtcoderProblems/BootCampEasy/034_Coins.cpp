#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int a, b, c, x;
  cin >> a >> b >> c >> x;

  int ans = 0;

  rep(i, a + 1) rep(j, b + 1) rep(k, c + 1) {
    if (500 * i + 100 * j + 50 * k == x) ans++;
  }

  cout << ans << endl;

  return 0;
}