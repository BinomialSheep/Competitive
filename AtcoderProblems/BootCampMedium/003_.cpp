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
  string s;
  cin >> s;

  /* solve */
  int n = s.size() + 1;
  // 0の位置を確定させる
  vector<int> a(n, INFTY);

  // 「><」となるところは0、端の処理もしておく
  rep(i, s.size() - 1) if (s[i] == '>' && s[i + 1] == '<') a[i + 1] = 0;
  if (s[0] == '<') a[0] = 0;
  if (s.back() == '>') a[n - 1] = 0;

  // 右に向かって数を確定させる
  rep(i, s.size()) {
    if (s[i] == '<' && a[i] != INFTY && a[i + 1] == INFTY) a[i + 1] = a[i] + 1;
  }
  // 左に向かって数を確定させる
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == '>' && a[i + 1] != INFTY) {
      if (a[i] == INFTY)
        a[i] = a[i + 1] + 1;
      else
        a[i] = max(a[i], a[i + 1] + 1);
    }
  }

  // 合計を計算
  ll sum = 0;
  rep(i, n) {
    assert(a[i] != INFTY);
    sum += a[i];
  }

  // debug
  // rep(i, n) { cout << a[i] << " "; }

  /* output */
  cout << sum << endl;

  return 0;
}