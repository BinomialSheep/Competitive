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
#include <atcoder/all>
using namespace atcoder;
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
    /* input */
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<vpii> G(N);
    dsu uf(N);

    rep(i, M) {
      int A, B, C;
      cin >> A >> B >> C;
      --A, --B;
      G[A].emplace_back(B, C);
      G[B].emplace_back(A, -C);
      uf.merge(A, B);
    }

    /* solve */
    set<int> infGroup;
    vl dist(N, INFTY);

    auto dfs = [&](auto f, int from, ll d) -> void {
      for (auto [to, c] : G[from]) {
        if (dist[to] == INFTY) {
          dist[to] = d + c;
          f(f, to, d + c);
        } else {
          if (dist[to] == d + c) {
            continue;
          } else {
            infGroup.insert(uf.leader(from));
            return;
          }
        }
      }
    };
    for (auto group : uf.groups()) {
      dist[group[0]] = 0;
      dfs(dfs, group[0], 0);
    }
    // debug(infGroup);
    // debug(dist);

    rep(qi, Q) {
      int X, Y;
      cin >> X >> Y;
      --X, --Y;
      if (uf.same(X, Y)) {
        if (infGroup.count(uf.leader(X))) {
          cout << "inf\n";
        } else {
          cout << dist[Y] - dist[X] << "\n";
        }
      } else {
        cout << "nan\n";
      }
    }

    /* output */
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