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
  vector<int> s(n);
  rep(i, n) cin >> s[i];

  /* solve */
  sort(s.begin(), s.end());
  int sum = 0;
  rep(i, n) sum += s[i];
  if (sum % 10 == 0) {
    rep(i, n) {
      if (s[i] % 10 != 0) {
        sum -= s[i];
        break;
      }
    }
  }

  cout << (sum % 10 == 0 ? 0 : sum) << endl;

  /* output */

  return 0;
}