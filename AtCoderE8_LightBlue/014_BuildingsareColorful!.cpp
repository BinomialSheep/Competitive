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
  int N, K;
  cin >> N >> K;
  vector<int> a(N);
  rep(i, N) cin >> a[i];
  /* solve */
  ll ans = (1LL << 62);
  rep(bit, 1 << N) {
    if (__builtin_popcount(bit) < K) continue;
    ll cost = 0;
    int height = -1;
    vector<int> copy(N);
    rep(i, N) copy[i] = a[i];
    rep(i, N) {
      // i個目が見えてほしい
      if (bit & (1 << i)) {
        if (copy[i] > height) {
          height = copy[i];
        } else {
          // 見えるギリギリまで高くする
          height++;
          cost += height - copy[i];
          copy[i] = height;
        }
      } else {
        if (copy[i] > height) {
          height = copy[i];
        }
      }
    }
    // cout << bitset<5>(bit) << ":" << cost << endl;
    ans = llMin(ans, cost);
  }

  /* output */
  cout << ans << endl;

  return 0;
}