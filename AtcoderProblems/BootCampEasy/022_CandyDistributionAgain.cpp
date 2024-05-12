#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, x;
  cin >> n >> x;
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  sort(a.begin(), a.end());

  int ans = 0;
  rep(i, n) {
    if (i == n - 1) {
      if (a[i] == x) ans++;
      break;
    }
    if (a[i] <= x) {
      x -= a[i];
      ans++;
    } else {
      break;
    }
  }
  cout << ans << endl;

  return 0;
}