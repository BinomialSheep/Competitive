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
    int N, M, Q;
    cin >> N >> M >> Q;
    vi L(M), R(M);
    rep(i, M) cin >> L[i] >> R[i], --L[i], --R[i];
    vi p(Q), q(Q);
    rep(i, Q) cin >> p[i] >> q[i], --p[i], --q[i];

    /* solve */
    vvi prefix(N, vi(N));

    rep(i, M) prefix[L[i]][R[i]]++;
    debug(prefix);
    rep(i, N) rep(j, N - 1) prefix[i][j + 1] += prefix[i][j];
    debug(prefix);
    for (int i = N - 1; i >= 1; i--) {
      rep(j, N) prefix[i - 1][j] += prefix[i][j];
    }
    debug(prefix);

    rep(i, Q) cout << prefix[p[i]][q[i]] << endl;

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