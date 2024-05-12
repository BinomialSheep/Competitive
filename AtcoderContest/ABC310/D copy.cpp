#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int N, T, M;
  scanf("%d %d %d", &N, &T, &M);
  vector<unordered_set<int>> C(N);
  rep(i, M) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a, --b;
    C[a].insert(b);
    C[b].insert(a);
  }

  vector<unordered_set<int>> now(T);
  ll ans = 0;
  auto f = [&](auto rec, int d = 0, int cnt = 0) -> void {
    if (cnt + (N - d) < T) return;
    if (d == N) {
      ans++;
      return;
    }

    rep(i, cnt) {
      int flag = 0;
      for (auto v : now[i]) {
        if (C[d].count(v)) {
          flag = 1;
          break;
        }
      }
      if (flag) continue;
      now[i].insert(d);
      rec(rec, d + 1, cnt);
      now[i].erase(d);
    }
    // 新しいチームを作る
    if (cnt < T) {
      now[cnt].insert(d);
      rec(rec, d + 1, cnt + 1);
      now[cnt].erase(d);
    }
  };
  f(f);
  // rep(i, T) ans /= (i + 1);
  printf("%lld\n", ans);

  return 0;
}
