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
  ll N, M;
  cin >> N >> M;

  /* solve */
  // 隅は4回、辺は8回、中は9回ひっくり返る
  // つまり、枠の数を数えればいい
  ll ans;
  if (N == 1) {
    if (M == 1)
      ans = 1;
    else
      ans = M - 2;
  } else if (M == 1) {
    ans = N - 2;
  } else {
    ans = N * M - (2 * N + 2 * M - 4);
  }

  /* output */
  cout << ans << endl;

  return 0;
}