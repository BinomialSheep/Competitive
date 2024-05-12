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
  int N, M;
  cin >> N >> M;
  vector<int> X(M);
  rep(i, M) cin >> X[i];

  if (N >= M) {
    cout << 0 << endl;
    return 0;
  }

  sort(X.begin(), X.end());

  vector<int> dist(M - 1);
  rep(i, M - 1) { dist[i] = X[i + 1] - X[i]; }
  sort(dist.begin(), dist.end());

  ll ans = 0;
  rep(i, M - N) { ans += dist[i]; }

  /* output */
  cout << ans << endl;

  return 0;
}