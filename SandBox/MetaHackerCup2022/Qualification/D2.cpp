#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

struct Solver {
  void solve() {
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      int N, M, Q;
      cin >> N >> M >> Q;
      vvi to(N);
      rep(i, M) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        to[a].push_back(b);
        to[b].push_back(a);
      }

      vvvi dp(N, vvi(N, vi(2)));

      rep(i, N) {
        for (auto u : to[i]) {
          dp[i][u][0] = 
        }
      }

      /* solve */
      printf("Case #%d: ", ti + 1);
      rep(qi, Q) {
        int X, Y;
        cin >> X >> Y;
        --X, --Y;
        ll ans = 0;
        if (to[X].size() >= to[Y].size()) {
          for (auto p : to[Y]) {
            if (p.first == X) {
              ans += p.second * 2;
            } else if (to[X].count(p.first)) {
              ans += min(p.second, to[X][p.first]);
            }
          }
        } else {
          for (auto p : to[X]) {
            if (p.first == Y) {
              ans += p.second * 2;
            } else if (to[Y].count(p.first)) {
              ans += min(p.second, to[Y][p.first]);
            }
          }
        }
        printf("%lld%c", ans, (qi == Q - 1 ? '\n' : ' '));
      }
      /* output */
    }
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}