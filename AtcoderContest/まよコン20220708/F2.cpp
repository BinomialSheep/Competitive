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
  vector<set<int>> cs;

  // 結合
  void uni(int v, int u) {
    for (auto uu : cs[u]) {
      cs[v].insert(uu);
    }
  }

  void dfs(int v, int depth, vvi &G, vi &dist) {
    // debug(v, depth);
    for (auto u : G[v]) {
      dist[u] = depth + 1;
      dfs(u, depth + 1, G, dist);
      uni(v, u);
      cs[v].insert(u);
    }
    cs[v].insert(v);
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    vi P(N - 1);
    rep(i, N - 1) {
      cin >> P[i];
      P[i]--;
    }
    int Q;
    cin >> Q;
    vi U(Q), D(Q);
    rep(i, Q) {
      cin >> U[i] >> D[i];
      U[i]--;
      D[i];
    }

    /* solve */
    vvi G(N);
    rep(i, N - 1) G[P[i]].push_back(i + 1);
    // debug(G);
    //  0からNへのやつ
    vi dist(N);
    cs.resize(N);
    dfs(0, 0, G, dist);
    // debug(dist);
    // debug(cs);

    map<int, vector<int>> mp;
    rep(i, N) { mp[dist[i]].push_back(i); }

    // debug(mp);

    // クエリを先読みする
    map<int, vi> qs;
    rep(i, Q) { qs[D[i]].push_back(i); }
    vi ans(Q);

    for (auto p : qs) {
      auto dvec = mp[p.first];
      vi vec = p.second;

      set<int> st;
      for (auto a : p.second) {
        auto st2 = cs[a];
        for (auto b : st2)
          if ()
            std::set_union(dvec.begin(), dvec.end(), vec2.begin(), vec2.end(),
                           back_inserter(st));
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