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
  int temp = (1 << 30);
  for (int i = K - 1; i >= 0; i--) {
    if (A[i] < temp) {
      toK[A[i]] = i;
      temp = A[i];
    }
  }
  temp = -1;
  for (int i = K; i < N; i++) {
    if (A[i] > temp) {
      fromK[A[i]] = i;
      temp = A[i];
    }
  }
  // 二分探索して、操作回数を更新する
  int ans = N + 10;
  for (auto p : toK) {
    // toKの値と最初に入れ替われる位置
    auto it = fromK.upper_bound(p.first);
    if (it != fromK.end()) {
      ans = min(ans, it->second - p.second);
    }
  }

  assert(ans > 0);
  assert(ans < N + 11);

  /* output */
  if (ans == N + 10) {
    cout << -1 << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}