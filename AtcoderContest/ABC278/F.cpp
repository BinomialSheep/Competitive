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
    /* input */
    int N;
    cin >> N;
    vs S(N);
    rep(i, N) cin >> S[i];

    vvi G(N);
    rep(i, N) rep(j, N) {
      if (i == j) continue;
      if (S[i].back() == S[j][0]) G[i].push_back(j);
    }
    debug(G);

    /* solve */
    map<vi, int> memo;
    auto dfs = [&](auto f, int v, int turn, vi used) -> int {
      // debug(v, turn, used);
      if (memo.count(used)) return memo[used];

      int next = (turn + 1) % 2;
      int ret = next;
      for (auto u : G[v]) {
        if (used[u]) continue;
        // debug(u);
        used[u] = 1;
        int winner = f(f, u, next, used);
        used[u] = 0;
        if (ret != winner) {
          ret = winner;
          return ret;
        }
      }
      return ret;
    };

    rep(i, N) {
      vi tmp(N);
      tmp[i] = 1;
      int res = dfs(dfs, i, 1, tmp);
      // debug(res);
      if (res == 0) {
        cout << "First" << endl;
        return;
      }
    }
    cout << "Second" << endl;
    return;

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