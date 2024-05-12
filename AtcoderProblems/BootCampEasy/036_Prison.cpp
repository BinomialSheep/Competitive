#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> L(m);
  vector<int> R(m);
  rep(i, m) cin >> L[i] >> R[i];

  int left = 0, right = 1001000;
  rep(i, m) {
    left = max(left, L[i]);
    right = min(right, R[i]);
  }

  int ans = max(right - left + 1, 0);
  cout << ans << endl;

  return 0;
}