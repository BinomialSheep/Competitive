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
  vector<ll> A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  ll ans = 0;
  //
  unordered_map<ll, ll> mp;
  rep(i, N) mp[A[i]]++;
  // A[i]の約数を数える
  rep(i, N) {
    for (ll j = 1; j * j <= A[i]; j++) {
      if (A[i] % j != 0) continue;
      // jとA[i]/jの2倍を足す
      cout << ans << " " << A[i] << " " << mp[j] << " " << mp[A[i] / j] << endl;
      // 1が絡むケースは自分を含まないように気を付ける
      if (j == 1) {
        if (A[i] == 1) {
          if (mp[1] <= 2) continue;
          //ans += 2 * (mp[1] - 1);
          ans += 2 * (mp[1] - 1);
        } else {
          //ans += 2 * mp[j] * (mp[A[i] / j] - 1);
          ans += mp[j] * mp[A[i] / j];
        }
      } else {
        if (j == A[i] / j) {
          if (mp[j]) {
            //ans += 2 * mp[j] * (mp[j] - 1);
            ans += mp[j] * mp[j];
          }
        } else {
          ans += 2 * mp[j] * mp[A[i] / j];
        }
      }
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}