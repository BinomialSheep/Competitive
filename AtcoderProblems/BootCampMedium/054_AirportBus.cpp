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
  ll N, C, K;
  cin >> N >> C >> K;
  vector<ll> T(N);
  rep(i, N) cin >> T[i];
  /* solve */
  sort(T.begin(), T.end());
  ll ans = 0;
  // ll time = 0;
  int i = 0;
  while (i < N) {
    // 今着目しているバスに乗っている人数（1人目を載せる）
    ll num = 1;
    i++;
    ll thisTime = 0;
    while (true) {
      // 全員乗ったか満員か時刻オーバーならバスは出発する
      if (i == N || num == C || thisTime + T[i] - T[i - 1] > K) {
        // バスは出発しなければならない
        ans++;
        break;
      }
      // 1人乗れる
      num++;
      thisTime += T[i] - T[i - 1];
      i++;
    }
    // cout << ans << " " << i << endl;
  }

  /* output */
  cout << ans << endl;

  return 0;
}