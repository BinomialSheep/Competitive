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
  int N;
  cin >> N;
  vector<int> T(N);
  rep(i, N) cin >> T[i];

  /* solve */
  ll ans = (ll)pow(2, T[0]);
  ll keta = T[0] + 1;
  rep(i, N - 1) {
    // cout << ans << " ";
    if (T[i] == T[i + 1]) {
      ans *= 3;
      keta++;
    } else if (T[i] > T[i + 1]) {
      ans += (ll)pow(2, T[i + 1]);
    } else {
      if (keta < T[i + 1] + 1) {
        ans = (ll)pow(2, T[i + 1]);
        keta = T[i + 1] + 1;
      } else {
        ans = (ll)pow(2, keta) + (ll)pow(2, T[i + 1]);
        keta++;
      }
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}