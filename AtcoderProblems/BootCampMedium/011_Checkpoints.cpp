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
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> p(n);
  vector<pair<int, int>> q(m);
  rep(i, n) {
    int a, b;
    cin >> a >> b;
    p[i] = make_pair(a, b);
  }
  rep(j, m) {
    int c, d;
    cin >> c >> d;
    q[j] = make_pair(c, d);
  }

  /* solve */
  rep(i, n) {
    int num;
    int d = INFTY;
    rep(j, m) {
      int e = abs(p[i].first - q[j].first) + abs(p[i].second - q[j].second);
      if (d > e) {
        d = e;
        num = j + 1;
      }
    }
    cout << num << endl;
  }

  /* output */

  return 0;
}