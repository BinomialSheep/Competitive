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
    int N, M, E;
    cin >> N >> M >> E;
    vi U(E), V(E);
    rep(i, E) cin >> U[i] >> V[i], --U[i], --V[i];
    int Q;
    cin >> Q;
    vi X(Q);
    rep(i, Q) cin >> X[i], --X[i];

    /* solve */
    vb broken(E);
    rep(i, Q) broken[X[i]] = true;
    rep(i, E) {
      if (U[i] >= N) U[i] = N;
      if (V[i] >= N) V[i] = N;
    }

    dsu uf(N + 1);
    vi ans(Q);

    // 最後の状態
    rep(i, E) {
      if (broken[i]) continue;
      uf.merge(U[i], V[i]);
    }

    auto getAns = [&]() {
      // Nと繋がっている数を数えるだけ
      return uf.size(N) - 1;
    };
    ans[Q - 1] = getAns();

    // 逆順に更新
    for (int i = Q - 1; i > 0; i--) {
      uf.merge(U[X[i]], V[X[i]]);
      ans[i - 1] = getAns();
    }

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