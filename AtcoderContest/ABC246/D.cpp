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
  ll n;
  cin >> n;

  /* solve */
  ll ans = (1LL << 62);
  for (int a = 0; a <= 1000000; a++) {
    // 二分探索をする
    int left = -1;
    int right = 1000000;
    ll x;
    int mid;
    while (right - left > 1) {
      mid = left + (right - left) / 2;

      ll aa = (ll)a * a;
      ll bb = (ll)mid * mid;
      x = a * aa + aa * mid + a * bb + mid * bb;
      if (x == n) {
        break;
      }
      if (x < n) {
        left = mid;
      } else {
        right = mid;
      }
    }
    if (x < n) {
      mid++;
      ll aa = (ll)a * a;
      ll bb = (ll)mid * mid;
      x = a * aa + aa * mid + a * bb + mid * bb;
    }
    ans = llMin(ans, x);
  }

  /* output */
  cout << ans << endl;

  return 0;
}