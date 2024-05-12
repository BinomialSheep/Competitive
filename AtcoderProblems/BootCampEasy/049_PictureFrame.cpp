#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int h, w;
  cin >> h >> w;
  vector<vector<char>> ans(h + 2, vector<char>(w + 2, '#'));
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> ans[i][j];
    }
  }

  rep(i, h + 2) {
    rep(j, w + 2) { cout << ans[i][j]; }
    cout << endl;
  }

  return 0;
}