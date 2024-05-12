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
  int dis, n, m;
  cin >> dis >> n >> m;
  vector<int> d(n + 1);
  rep(i, n - 1) cin >> d[i + 1];
  d[0] = 0;
  d[n] = dis;
  sort(d.begin(), d.end());
  vector<int> k(m);
  rep(i, m) cin >> k[i];

  /* solve */
  int ans = 0;
  rep(i, m) {
    auto it = lower_bound(d.begin(), d.end(), k[i]);
    int index = (int)(it - d.begin());
    // cout << i << " " << index << endl;
    ans += min(d[index] - k[i], k[i] - d[index - 1]);
  }

  /* output */
  cout << ans << endl;

  return 0;
}