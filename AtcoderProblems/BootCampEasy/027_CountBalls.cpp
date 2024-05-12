#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll n, a, b;
  cin >> n >> a >> b;
  ll full = n / (a + b);
  ll ans1 = a * full;
  ll rest = n % (a + b);
  ll ans2 = rest >= a ? a : rest;

  cout << ans1 + ans2 << endl;

  return 0;
}