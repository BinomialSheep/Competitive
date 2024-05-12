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
  int N, X, Y;
  cin >> N >> X >> Y;
  vector<int> A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  set<int> xIndex;
  set<int> yIndex;
  set<int> underIndex;
  set<int> overIndex;
  rep(i, N) {
    if (A[i] == X) xIndex.insert(i);
    if (A[i] == Y) yIndex.insert(i);
    if (A[i] < Y) underIndex.insert(i);
    if (A[i] > X) overIndex.insert(i);
  }
  ll ans = 0;
  rep(i, N) {
    // iをLとした時、Rをいくつ以上にできるか
    auto ltX = xIndex.lower_bound(i);
    auto ltY = yIndex.lower_bound(i);
    if (ltX == xIndex.end() || ltY == yIndex.end()) continue;
    auto ltU = underIndex.lower_bound(i);
    auto ltO = overIndex.lower_bound(i);

    // Rの最小
    int index = max(*ltX, *ltY);
    // 違反になる最小値
    int index2 = N;
    if (ltU != underIndex.end()) index2 = min(index2, *ltU);
    if (ltO != overIndex.end()) index2 = min(index2, *ltO);
    // 先に違反になったらダメ
    if (index > index2) continue;
    // cout << i << " " << *ltX << " " << *ltY << endl;
    ans += index2 - index;
  }

  /* output */
  cout << ans << endl;

  return 0;
}