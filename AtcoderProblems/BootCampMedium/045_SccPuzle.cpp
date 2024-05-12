#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
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
  ll N, M;
  cin >> N >> M;

  /* solve */
  if (N >= M / 2) {
    cout << M / 2 << endl;
    return 0;
  }

  // まずSを使い切る
  ll ans = N;
  M -= 2 * N;
  // 余ったC4個で作る
  ans += M / 4;

  /* output */
  cout << ans << endl;

  return 0;
}