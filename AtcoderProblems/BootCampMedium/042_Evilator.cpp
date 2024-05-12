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

// xからyまでの和を求める
ll sum(ll x, ll y) {
  //
  return abs(y * (y - 1) / 2 - x * (x - 1) / 2);
}

int main() {
  /* input */
  string s;
  cin >> s;

  /* solve */
  int n = (int)s.size();

  ll ans = 0;
  rep(i, n) {
    // i階より下はi個ある
    if (s[i] == 'D') {
      ans += i;
    } else {
      ans += 2 * i;
    }
    // i階より上はn - i - 1個ある
    if (s[i] == 'U') {
      ans += n - i - 1;
    } else {
      ans += 2 * (n - i - 1);
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}