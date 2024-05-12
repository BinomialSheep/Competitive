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
  ll A, B, C, D;
  cin >> A >> B >> C >> D;

  /* solve */
  ll numC = B / C - (A - 1) / C;
  ll numD = B / D - (A - 1) / D;
  ll numCD = B / lcm(C, D) - (A - 1) / lcm(C, D);

  /* output */
  cout << B - A + 1 - (numC + numD - numCD) << endl;

  return 0;
}