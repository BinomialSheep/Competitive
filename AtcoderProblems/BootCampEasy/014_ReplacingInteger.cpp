#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll n, k;
  cin >> n >> k;

  ll ans;
  // よく見たら0<=N, 1<=Kなので場合分けは不要だった……
  if (n <= 0 || k <= 0) {
    ans = n;
  } else {
    ll temp = n % k;
    ans = min(temp, k - temp);
  }

  cout << ans << endl;

  return 0;
}