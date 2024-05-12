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
    int M, N, K;
    cin >> M >> N >> K;

    vvc A(M, vc(N));
    rep(i, M) rep(j, N) cin >> A[i][j];

    vvi B(K, vi(4));
    rep(i, K) {
      rep(j, 4) {
        int a;
        cin >> a;
        --a;
        B[i][j] = a;
      }
    }

    /* solve */

    vector<vvl> prefix(M, vvl(N, vl(3)));
    rep(i, M) rep(j, N) {
      if (A[i][j] == 'J') prefix[i][j][0] = 1;
      if (A[i][j] == 'O') prefix[i][j][1] = 1;
      if (A[i][j] == 'I') prefix[i][j][2] = 1;
      if (j == 0) continue;
      rep(k, 3) prefix[i][j][k] += prefix[i][j - 1][k];
    }
    rep(i, M) rep(j, N) rep(k, 3) {
      if (i == 0) continue;
      prefix[i][j][k] += prefix[i - 1][j][k];
    }

    debug(prefix);

    //
    rep(i, K) {
      int a = B[i][0];
      int b = B[i][1];
      int c = B[i][2];
      int d = B[i][3];

      debug(prefix[a][b]);
      debug(prefix[c][d]);

      vl joi(3);
      rep(j, 3) {
        joi[j] = prefix[c][d][j];
        if (a != 0) joi[j] -= prefix[a - 1][d][j];
        if (b != 0) joi[j] -= prefix[c][b - 1][j];
        if (a != 0 && b != 0) joi[j] += prefix[a - 1][b - 1][j];
      }
      // if (A[a][b] == 'J') prefix[a][b][0] += 1;
      // if (A[a][b] == 'O') prefix[a][b][1] += 1;
      // if (A[a][b] == 'I') prefix[a][b][2] += 1;

      cout << joi[0] << " " << joi[1] << " " << joi[2] << endl;
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