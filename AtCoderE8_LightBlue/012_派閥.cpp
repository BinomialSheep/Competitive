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

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  set<pair<int, int>> xy;
  rep(i, M) {
    int x, y;
    cin >> x >> y;
    xy.insert(make_pair(x - 1, y - 1));
    xy.insert(make_pair(y - 1, x - 1));
  }
  /* solve */
  int ans = 0;
  // ありうる全グループをビット全探索で列挙
  rep(bit, 1 << N) {
    bool flag = true;
    rep(i, N - 1) {
      for (int j = i + 1; j < N; j++) {
        // cout << bit << ":" << i << ":" << j << endl;
        if ((bit & (1 << i)) && (bit & (1 << j))) {
          // 2人が知り合いじゃないければfalse
          if (xy.find(make_pair(i, j)) == xy.end()) {
            flag = false;
            break;
          }
        }
      }
      if (!flag) break;
    }
    // 派閥として成立していれば数える
    if (flag) {
      ans = max(ans, __builtin_popcount(bit));
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}