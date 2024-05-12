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
    int N, M;
    cin >> N >> M;
    vi A(M), B(M), X(M);
    rep(i, M) cin >> A[i] >> B[i] >> X[i], --A[i], --B[i];

    /* solve */
    vvi imos(N + 2, vi(N + 2));
    rep(i, M) {
      imos[A[i]][B[i]]++;
      imos[A[i]][B[i] + 1]--;
      imos[A[i] + X[i] + 1][B[i]]--;
      imos[A[i] + X[i] + 1][B[i] + X[i] + 2]++;
      imos[A[i] + X[i] + 2][B[i] + 1]++;
      imos[A[i] + X[i] + 2][B[i] + X[i] + 2]--;
    }
    debug(imos);

    // 右へ
    rep(i, N + 1) rep(j, N) imos[i][j + 1] += imos[i][j];
    debug(imos);

    // 下へ
    rep(j, N + 1) rep(i, N) imos[i + 1][j] += imos[i][j];
    debug(imos);

    // 右下へ
    rep(i, N + 1) {
      rep(j, N + 10) {
        if (i + j + 1 > N || j + 1 > N) break;
        imos[i + j + 1][j + 1] += imos[i + j][j];
      }
    }
    debug(imos);

    ll ans = 0;
    rep(i, N) rep(j, N) {
      if (imos[i][j]) ans++;
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