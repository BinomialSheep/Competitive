#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
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
  vector<pair<int, int>> xy(3);
  rep(i, 3) cin >> xy[i].first >> xy[i].second;

  /* solve */
  sort(xy.begin(), xy.end());
  if (xy[0].first == xy[1].first) {
    if (xy[0].second == xy[2].second) {
      cout << xy[2].first << " " << xy[1].second << endl;
      return 0;
    }
    cout << xy[2].first << " " << xy[0].second << endl;
    return 0;
  }

  if (xy[0].second == xy[1].second) {
    cout << xy[0].first << " " << xy[2].second << endl;
  } else {
    cout << xy[0].first << " " << xy[1].second << endl;
  }

  return 0;
}