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
  vector<int> B(N);
  vector<int> C(N);
  rep(i, N) cin >> A[i];
  rep(i, N) cin >> B[i];
  rep(i, N) cin >> C[i];

  /* solve */
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  sort(C.begin(), C.end());

  // Bを選んだ時の累積Cは予め計算しておく
  vector<ll> BC(N + 1, 0);
  for (int i = N - 1; i >= 0; i--) {
    auto it = upper_bound(C.begin(), C.end(), B[i]);
    if (it == C.end()) {
      BC[i] = BC[i + 1];
    } else {
      BC[i] = (ll)(C.end() - it) + BC[i + 1];
    }
  }

  ll ans = 0;
  rep(i, N) {
    // A[i]より大きい最初のB[j]の求める
    auto it = upper_bound(B.begin(), B.end(), A[i]);
    if (it == B.end()) continue;
    ans += BC[it - B.begin()];
  }

  /* output */
  cout << ans << endl;

  return 0;
}