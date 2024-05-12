#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

void solve(int testCase) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  /* input */
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<unordered_map<int, int>> to(N);
  vector<unordered_map<int, ll>> memo(N);
  rep(i, M) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    to[a][b] = c;
    to[b][a] = c;
  }

  /* solve */
  printf("Case #%d: ", testCase);
  rep(qi, Q) {
    int X, Y;
    cin >> X >> Y;
    --X, --Y;
    // 次数が小さい方をXとする
    if (to[X].size() > to[Y].size()) swap(X, Y);
    ll ans = 0;

    if (memo[X].count(Y)) {
      ans = memo[X][Y];
    } else {
      if (to[X].count(Y)) ans += 2 * to[X][Y];

      for (auto &[Z, toXZ] : to[X]) {
        if (to[Z].count(Y)) {
          ans += min(toXZ, to[Z][Y]);
        }
      }
      memo[X][Y] = ans;
    }

    printf("%lld%c", ans, (qi == Q - 1 ? '\n' : ' '));
  }
}

int main() {
  int T;
  cin >> T;
  rep(ti, T) solve(ti + 1);
  return 0;
}