#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll a, b, c, k;
  cin >> a >> b >> c >> k;
  ll ans;
  if (k % 2 == 0) {
    ans = a - b;
  } else {
    ans = b - a;
  }

  cout << ans << endl;

  return 0;
}