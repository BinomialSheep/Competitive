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
  vector<int> P(n);
  rep(i, n) cin >> P[i];

  vector<int> leftMin(n);
  leftMin[0] = P[0];
  for (int i = 1; i < n; i++) leftMin[i] = min(leftMin[i - 1], P[i]);

  int ans = 0;
  rep(i, n) {
    if (P[i] == leftMin[i]) ans++;
  }

  cout << ans << endl;

  return 0;
}