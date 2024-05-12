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
  bool flag = false;
  bool isEnd = false;
  int end = -1;
  unordered_set<int> cycle;

  void dfs(vvi &G, int v, unordered_set<int> &visited, int parent) {
    if (isEnd) return;
    for (auto u : G[v]) {
      if (flag) break;
      if (u == parent) continue;
      if (visited.count(u)) {
        flag = true;
        end = u;
      } else {
        visited.insert(u);
        dfs(G, u, visited, v);
      }
    }
    if (isEnd) return;
    if (flag) cycle.insert(v);
    if (v == end) isEnd = true;
  }

  void dfs2(vvi &G, int v, int parent, dsu &uf) {
    for (auto u : G[v]) {
      if (u == parent) continue;
      if (cycle.count(u)) continue;
      uf.merge(v, u);
      dfs2(G, u, v, uf);
    }
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    vvi G(N);
    rep(i, N) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    int Q;
    cin >> Q;
    vi x(Q), y(Q);
    rep(i, Q) cin >> x[i] >> y[i], --x[i], --y[i];

    /* solve */
    unordered_set<int> visited;
    dfs(G, 0, visited, 0);
    debug(cycle);

    dsu uf(N);

    for (auto v : cycle) {
      dfs2(G, v, v, uf);
    }

    //

    rep(i, Q) {
      if (uf.same(x[i], y[i])) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
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