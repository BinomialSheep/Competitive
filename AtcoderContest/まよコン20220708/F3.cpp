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
  vvi G;
  vi in;
  vi out;
  vi depth;
  int cnt;

  // オイラーツアー
  void dfs(int v, int d) {
    in[v] = cnt;
    cnt++;
    depth[v] = d;
    for (auto u : G[v]) {
      dfs(u, d + 1);
    }
    out[v] = cnt;
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    vi P(N - 1);
    rep(i, N - 1) cin >> P[i], --P[i];

    /* solve */
    G.resize(N);
    in.resize(N);
    out.resize(N);
    depth.resize(N);
    rep(i, N - 1) { G[P[i]].push_back(i + 1); }

    // debug(G);
    cnt = 0;
    dfs(0, 0);
    debug(in, out, depth);

    //
    vvi ls(N);
    rep(i, N) ls[depth[i]].push_back(in[i]);
    rep(i, N) sort(ls[i].begin(), ls[i].end());

    // 深さdにおけるr未満の値の個数を取る
    auto f = [&](int d, int r) {
      auto it = lower_bound(ls[d].begin(), ls[d].end(), r);
      int dst = (int)(it - ls[d].begin());
      return dst;
    };

    // 答えるパート
    int Q;
    cin >> Q;
    rep(qi, Q) {
      int U, D;
      cin >> U >> D;
      --U;
      // 深さdかつuの部分木の個数がこれで求まる
      int ans = f(D, out[U]) - f(D, in[U]);
      cout << ans << "\n";
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