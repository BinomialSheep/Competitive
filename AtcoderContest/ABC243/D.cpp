#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  //
  int n;
  ll X;
  string S;
  cin >> n >> X;
  cin >> S;
  // 10^18を超えないように整理
  vector<int> normal;
  rep(i, n) {
    if (S[i] == 'L') {
      normal.push_back('L');
    } else if (S[i] == 'R') {
      normal.push_back('R');
    } else {
      // vectorの末尾がUでなければ削除する
      if (!normal.empty() && normal[normal.size() - 1] != 'U') {
        normal.pop_back();
      } else {
        normal.push_back('U');
      }
    }
  }
  // 愚直にシミュレーション
  ll ans = X;
  rep(i, normal.size()) {
    if (normal[i] == 'L') {
      ans *= 2;
    } else if (normal[i] == 'R') {
      ans = 2 * ans + 1;
    } else {
      ans /= 2;
    }
  }

  // output
  cout << ans << endl;

  return 0;
}