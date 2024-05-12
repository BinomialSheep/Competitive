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

class Edge {
 public:
  int source, target, cost;
  Edge(int s, int t, int c) : source(s), target(t), cost(c) {}
  bool operator<(Edge &e) { return cost < e.cost; }
};

struct Solver {
  int N, M, R;
  ll pm(vi &r, vvi &G) {
    vector<int> perm(R);
    rep(i, R) perm[i] = i;
    ll ans = INFTY;
    do {
      ll now = 0;
      rep(i, R - 1) { now += G[r[perm[i]]][r[perm[i + 1]]]; }
      chmin(ans, now);
    } while (next_permutation(perm.begin(), perm.end()));
    return ans;
  }

  void solve() {
    /* input */

    cin >> N >> M >> R;
    vi r(R);
    rep(i, R) cin >> r[i], --r[i];
    vvi G(N, vi(N, INFTY));
    rep(i, M) {
      int A, B, C;
      cin >> A >> B >> C;
      --A, --B;
      G[A][B] = C;
      G[B][A] = C;
    }

    /* solve */
    rep(i, N) G[i][i] = 0;
    rep(k, N) rep(i, N) {
      if (G[i][k] == INFTY) continue;
      rep(j, N) {
        if (G[k][i] == INFTY) continue;
        chmin(G[i][j], G[i][k] + G[k][j]);
      }
    }
    // debug(G);
    rep(i, N) rep(j, N) if (G[i][j] == INFTY) return;

    // 順列全探索ver
    ll pmAns = pm(r, G);

    // // クラスカル
    vector<Edge> edges;
    rep(i, R) rep(j, i) edges.push_back(Edge(r[i], r[j], G[r[i]][r[j]]));

    sort(edges.begin(), edges.end());

    // for (Edge e : edges) {
    //   debug(e.source, e.target, e.cost);
    // }

    atcoder::dsu d(M);

    ll ans = 0;
    for (Edge e : edges) {
      if (!d.same(e.source, e.target)) {
        ans += e.cost;
        d.merge(e.source, e.target);
      }
    }

    if (pmAns != ans) {
      cout << "順列全探索：" << pmAns << endl;
      cout << "クラスカル：" << ans << endl;
      assert(false);
    }

    /* output */
    cout << ans << endl;
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