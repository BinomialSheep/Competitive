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
  int N, K;
  cin >> N;
  cin >> K;
  vector<int> A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  // 0からk-1までと、kからn-1までについて、昇順に圧縮して、二分探索
  map<int, int> toK;
  map<int, int> fromK;
  int minToK = (1 << 30);
  rep(i, K) {
    //
    toK[A[i]] = i;
    minToK = min(A[i], minToK);
  }

  int maxFromK = -1;
  for (int i = N - 1; i >= K; i--) {
    maxFromK = max(maxFromK, A[i]);
    fromK[A[i]] = i;
  }
  if (minToK >= maxFromK) {
    // コーナーケース除外
    cout << -1 << endl;
    return 0;
  }

  // 二分探索して、操作回数を更新する
  int ans = N + 1;
  for (auto p : toK) {
    // toKの値と最初に入れ替われる位置
    auto it = fromK.upper_bound(p.first);
    if (it != fromK.end()) {
      ans = min(ans, (it->second) - p.second);
    }
  }

  assert(ans > 0);
  assert(ans < N + 2);

  /* output */
  if (ans == N + 1) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}