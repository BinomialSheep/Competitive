#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, k;
  cin >> n >> k;

  int ans = 0;

  int xi;
  rep(i, n) {
    cin >> xi;
    if (xi <= abs(xi - k))
      ans += 2 * xi;
    else
      ans += 2 * abs(xi - k);
  }

  cout << ans << endl;

  return 0;
}