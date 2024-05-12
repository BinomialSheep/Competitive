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
  int n;
  cin >> n;
  string t;
  cin >> t;

  /* solve */
  // 向いている方向を表す
  int d = 'E';
  // 現在の座標
  pair<int, int> point(0, 0);

  rep(i, n) {
    if (t[i] == 'S') {
      if (d == 'E') point.first++;
      if (d == 'W') point.first--;
      if (d == 'N') point.second++;
      if (d == 'S') point.second--;
    } else {
      if (d == 'E')
        d = 'S';
      else if (d == 'W')
        d = 'N';
      else if (d == 'N')
        d = 'E';
      else if (d == 'S')
        d = 'W';
    }
  }

  /* output */
  cout << point.first << " " << point.second << endl;

  return 0;
}