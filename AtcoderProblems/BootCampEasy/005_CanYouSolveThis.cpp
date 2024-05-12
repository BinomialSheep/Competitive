#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, m, c;
  cin >> n >> m >> c;
  vector<vector<int> > A(n, vector<int>(m));
  vector<int> B(m);
  rep(i, m) cin >> B[i];
  rep(i, n) rep(j, m) cin >> A[i][j];

  int ans = 0;
  int score;
  rep(i, n) {
    score = 0;
    rep(j, m) score += A[i][j] * B[j];
    if (score + c > 0) ans++;
  }

  cout << ans << endl;

  return 0;
}