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

  vector<int> B(n - 1);
  rep(i, n - 1) cin >> B[i];

  int ans = B[0];
  rep(i, n - 2) { ans += min(B[i], B[i + 1]); }
  ans += B[n - 2];

  cout << ans << endl;

  return 0;
}