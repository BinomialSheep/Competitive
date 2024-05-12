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
  for (auto p : mp) {
    ll a = p.first;
    for (ll j = 1; j * j <= a; j++) {
      if (a % j != 0) continue;
      if (j == a / j) {
        if (mp.find(j) != mp.end()) {
          ans += p.second * mp[j] * mp[a / j];
        }
      } else {
        if (mp.find(j) != mp.end() && mp.find(a / j) != mp.end()) {
          ans += p.second * mp[j] * mp[a / j] * 2;
        }
      }
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}