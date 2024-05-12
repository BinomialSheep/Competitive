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
  vector<int> foods(m, 0);
  int k, kj;
  rep(i, n) {
    cin >> k;
    rep(j, k) {
      cin >> kj;
      foods[--kj]++;
    }
  }

  int ans = 0;
  rep(i, m) {
    if (foods[i] == n) ans++;
  }
  cout << ans << endl;

  return 0;
}