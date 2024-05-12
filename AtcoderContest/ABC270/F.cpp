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
  void solve() {
    /* input */
    int N, M;
    cin >> N >> M;
    deque<pii> X;
    rep(i, N) {
      int x;
      cin >> x;
      X.emplace_front(x, i);
    }
    deque<pii> Y;
    rep(i, N) {
      int y;
      cin >> y;
      Y.emplace_front(y, i);
    }
    deque<Edge> edges;
    rep(i, M) {
      int A, B, Z;
      cin >> A >> B >> Z;
      --A, --B;
      edges.emplace_back(A, B, Z);
    }
    sort(all(X));
    sort(all(Y));
    sort(edges.begin(), edges.end());

    /* solve */

    dsu uf(N);
    ll ans = 0;
    int idx = 0;
    debug(X);
    debug(Y);
    rep(i, M) debug(edges[i].source, edges[idx].target);

    while (uf.size(0) < N) {
      while (X.size() > 2 && uf.same(X[0].second, X[1].second)) {
        auto tmp = X[0];
        X.pop_front();
        X.pop_front();
        X.push_front(tmp);
      }
      while (Y.size() > 2 && uf.same(Y[0].second, Y[1].second)) {
        auto tmp = Y[0];
        Y.pop_front();
        Y.pop_front();
        Y.push_front(tmp);
      }
      while (idx < M && uf.same(edges[idx].source, edges[idx].target)) idx++;
      int c1 = X.size() > 2 ? X[0].first + X[1].first : INFTY;
      int c2 = Y.size() > 2 ? Y[0].first + Y[1].first : INFTY;
      int c3 = idx < M ? edges[idx].cost : INFTY;
      if (c1 == min(c1, min(c2, c3))) {
        ans += c1;
        uf.merge(X[0].second, X[1].second);
        X.pop_front();
      } else if (c2 == min(c1, min(c2, c3))) {
        ans += c2;
        uf.merge(Y[0].second, Y[1].second);
        Y.pop_front();
      } else {
        ans += c3;
        uf.merge(edges[idx].source, edges[idx].target);
        idx++;
      }
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