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
  int N, X;
  cin >> N >> X;
  vector<int> x(N);
  rep(i, N) cin >> x[i];

  /* solve */

  int num = abs(x[N - 1] - X);

  rep(i, N - 1) { num = gcd(num, abs(x[i] - X)); }

  /* output */
  cout << num << endl;

  return 0;
}