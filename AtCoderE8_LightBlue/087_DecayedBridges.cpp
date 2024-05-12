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
  int a, b;
  Edge(int aa, int bb) : a(aa), b(bb) {}
};

struct Solver {
  void solve() {
    /* input */
    int N, M;
    cin >> N >> M;
    vector<Edge> edges;
    rep(i, M) {
      int A, B;
      cin >> A >> B, --A, --B;
      edges.emplace_back(A, B);
    }

    /* solve */
    vl score(M);

    dsu d(N);

    for (int i = M - 1; i >= 0; i--) {
      int v = edges[i].a;
      int u = edges[i].b;
      if (!d.same(v, u)) {
        score[i] = d.size(v) * d.size(u);
        d.merge(v, u);
      }
    }

    rep(i, M - 1) score[i + 1] += score[i];

    /* output */
    rep(i, M) cout << score[i] << endl;
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