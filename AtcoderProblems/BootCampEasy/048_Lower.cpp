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
  vector<int> h(n);
  rep(i, n) cin >> h[i];

  int ans = 0;
  int temp = 0;
  rep(i, n - 1) {
    if (h[i] >= h[i + 1]) {
      temp++;
    } else {
      ans = max(ans, temp);
      temp = 0;
    }
  }
  if (h[n - 2] >= h[n - 1]) {
    ans = max(ans, temp);
  }

  cout << ans << endl;

  return 0;
}