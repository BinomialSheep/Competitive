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
  int N, K, S;
  cin >> N >> K >> S;

  /* solve */
  const int M = 1000000000;

  rep(i, K) cout << S << " ";
  rep(i, N - K) cout << (S == M ? 1 : M) << " ";
  cout << endl;

  /* output */

  return 0;
}