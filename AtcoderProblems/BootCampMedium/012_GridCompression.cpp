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
  vector<vector<char>> a(h, vector<char>(w));
  rep(i, h) rep(j, w) cin >> a[i][j];

  /* solve */
  // 横に見ていく
  queue<int> hi;
  rep(i, h) {
    bool hasB = false;
    rep(j, w) {
      if (a[i][j] == '#') {
        hasB = true;
        break;
      }
    }
    if (!hasB) hi.push(i);
  }
  // 縦に見ていく
  vector<int> hj;
  // 番兵
  rep(j, w) {
    bool hasB = false;
    rep(i, h) {
      if (a[i][j] == '#') {
        hasB = true;
        break;
      }
    }
    if (!hasB) hj.push_back(j);
  }

  /* output */
  // 番兵
  hj.push_back(-1);
  rep(i, h) {
    if (!hi.empty() && i == hi.front()) {
      hi.pop();
      continue;
    }
    int index = 0;
    rep(j, w) {
      if (j == hj[index]) {
        index++;
      } else {
        cout << a[i][j];
      }
    }
    cout << endl;
  }

  return 0;
}
