#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
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
  int L, R;
  cin >> L >> R;

  /* solve */
  ll ans = (1LL << 60);
  if (R - L <= 2020) {
    for (int i = L; i < R; i++) {
      for (int j = i + 1; j <= R; j++) {
        ll num = ((ll)i * j) % 2019;
        if (num <= ans) ans = num;
      }
    }
  } else {
    for (int i = L; i < L + 2020; i++) {
      for (int j = i + 1; j <= L + 2020; j++) {
        ll num = ((ll)i * j) % 2019;
        if (num <= ans) ans = num;
      }
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}