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
  int N;
  cin >> N;
  int Y;
  cin >> Y;

  rep(i, N + 1) {
    rep(j, N + 1) {
      int k = N - i - j;
      if (k < 0) continue;
      if (10000 * i + 5000 * j + 1000 * k == Y) {
        cout << i << " " << j << " " << k << endl;
        return 0;
      }
    }
  }

  cout << "-1 -1 -1" << endl;

  /* solve */

  /* output */

  return 0;
}