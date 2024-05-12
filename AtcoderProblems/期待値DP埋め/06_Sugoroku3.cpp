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

modint998244353 op(modint998244353 a, modint998244353 b) { return a + b; }
modint998244353 e() { return 0; }

struct Solver {
  void solve() {
    /* input */
    int N;
    cin >> N;
    vi A(N - 1);
    rep(i, N - 1) cin >> A[i], A[i];

    /* solve */
    using mint = modint998244353;
    segtree<mint, op, e> seg(N + 9);

    // ゴールから期待値DP
    seg.set(N, 0);
    for (int i = N - 2; i >= 0; i--) {
      // 期待値X = 1 + (1～A[i]マス先の和) / (A[i] + 1) + X / (A[i] + 1)
      // ⇔ X = (1 + A[i] + sum) / A[i]
      mint sum = seg.prod(i + 1, i + 1 + A[i]);
      mint child = 1 + A[i] + sum;
      seg.set(i, child / A[i]);
    }
    /* output */
    cout << seg.get(0).val() << endl;
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