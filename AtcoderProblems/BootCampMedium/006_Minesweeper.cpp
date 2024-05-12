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
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int h, w;
  cin >> h >> w;
  vector<string> s(h);
  rep(i, h) cin >> s[i];

  /* solve */
  rep(i, h) rep(j, w) {
    if (s[i][j] == '.') {
      // 爆弾の数を数える
      int cnt = 0;
      if (0 <= i - 1) {
        if (0 <= j - 1 && s[i - 1][j - 1] == '#') cnt++;
        if (s[i - 1][j] == '#') cnt++;
        if (j + 1 < w && s[i - 1][j + 1] == '#') cnt++;
      }
      if (0 <= j - 1 && s[i][j - 1] == '#') cnt++;
      if (j + 1 < w && s[i][j + 1] == '#') cnt++;
      if (i + 1 < h) {
        if (0 <= j - 1 && s[i + 1][j - 1] == '#') cnt++;
        if (s[i + 1][j] == '#') cnt++;
        if (j + 1 < w && s[i + 1][j + 1] == '#') cnt++;
      }
      char c = '0' + cnt;
      s[i][j] = c;
    }
  }

  /* output */
  rep(i, h) cout << s[i] << endl;

  return 0;
}