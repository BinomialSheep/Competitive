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
    vvi G(N);
    rep(i, N - 1) {
      int A, B;
      cin >> A >> B;
      --A, --B;
      G[A].push_back(B);
      G[B].push_back(A);
    }

    int Q;
    cin >> Q;
    vi ans(Q, -1);
    vector<vpii> qs(N);
    rep(i, Q) {
      int v, k;
      cin >> v >> k;
      --v;
      qs[v].emplace_back(i, k);
    }

    auto dfs = [&](auto f, int v, int d = 0, int p = -1) -> pii {
      pii res(d, v);
      for (auto u : G[v]) {
        if (u == p) continue;
        chmax(res, f(f, u, d + 1, v));
      }
      return res;
    };
    int a = dfs(dfs, 0).second;
    int b = dfs(dfs, a).second;
    debug(a, b);

    /* solve */
    deque<int> dq;
    auto dfs2 = [&](auto f, int v, int p = -1) -> void {
      for (auto [qi, k] : qs[v]) {
        if ((int)dq.size() >= k) {
          // debug(qi, k, dq[k - 1] + 1, v);
          // debug(dq);
          ans[qi] = dq[k - 1] + 1;
        }
      }
      debug(dq.size());
      dq.push_front(v);
      for (auto u : G[v]) {
        if (u == p) continue;
        f(f, u, v);
      }
      dq.pop_front();
    };

    dfs2(dfs2, a);
    dfs2(dfs2, b);
    /* output */
    rep(i, Q) cout << ans[i] << "\n";
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