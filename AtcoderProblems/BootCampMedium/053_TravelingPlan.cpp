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
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  // 元の予定
  ll sum = 0;
  sum += abs(A[0] - 0) + abs(0 - A[N - 1]);
  rep(i, N - 1) sum += abs(A[i + 1] - A[i]);

  rep(i, N) {
    ll ans = sum;
    // A[i]に行かない場合
    if (i == 0) {
      ans -= abs(A[0] - 0);
      ans -= abs(A[1] - A[0]);
      ans += abs(A[1] - 0);
    } else if (i == N - 1) {
      ans -= abs(0 - A[N - 1]);
      ans -= abs(A[N - 1] - A[N - 2]);
      ans += abs(0 - A[N - 2]);
    } else {
      ans -= abs(A[i] - A[i - 1]);
      ans -= abs(A[i + 1] - A[i]);
      ans += abs(A[i + 1] - A[i - 1]);
    }
    cout << ans << endl;
  }

  return 0;
}