#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, d;
  cin >> n >> d;
  vector<vector<int>> X(n, vector<int>(d));

  rep(i, n) rep(j, d) cin >> X[i][j];

  int ans = 0;

  rep(i, n) {
    for (int j = i + 1; j < n; j++) {
      double temp = 0;
      rep(k, d) { temp += (X[i][k] - X[j][k]) * (X[i][k] - X[j][k]); }
      temp = sqrt(temp);
      if (floor(temp) == temp) ans++;
    }
  }

  cout << ans << endl;

  return 0;
}