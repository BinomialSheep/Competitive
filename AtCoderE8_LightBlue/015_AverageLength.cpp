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

double distance(int x1, int y1, int x2, int y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int factrial(int n) {
  if (n == 1) return 1;
  return n * factrial(n - 1);
}

int main() {
  /* input */
  int N;
  cin >> N;
  vector<pair<int, int>> XY;
  rep(i, N) {
    int x, y;
    cin >> x >> y;
    XY.emplace_back(x, y);
  }

  /* solve */
  //
  double ans = 0;
  // 順列全探索する
  vector<int> perm(N);
  rep(i, N) perm[i] = i;
  do {
    double pathLength = 0;
    rep(i, N - 1) {
      int x1 = XY[perm[i]].first;
      int y1 = XY[perm[i]].second;
      int x2 = XY[perm[i + 1]].first;
      int y2 = XY[perm[i + 1]].second;
      pathLength += distance(x1, y1, x2, y2);
    }
    ans += pathLength;
  } while (next_permutation(perm.begin(), perm.end()));

  /* output */

  cout.precision(10);
  cout << fixed << ans / factrial(N) << endl;

  return 0;
}