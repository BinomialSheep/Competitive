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
    int H, W, N, h, w;
    cin >> H >> W >> N >> h >> w;
    vvi A(H, vi(W));
    rep(i, H) rep(j, W) cin >> A[i][j];

    /* solve */
    vvvi B(H, vvi(W + 1, vi(N)));
    rep(i, H) {
      rep(j, W) {
        rep(k, N) B[i][j + 1][k] = B[i][j][k];
        B[i][j + 1][A[i][j] - 1]++;
      }
    }
    rep(i, H - 1) rep(j, W + 1) rep(k, N) B[i + 1][j][k] += B[i][j][k];
    // debug(B);

    /* output */
    rep(i, H - h + 1) {
      rep(j, W - w + 1) {
        vi C(N);
        rep(k, N) C[k] = B[i + h - 1][j + w][k];
        rep(k, N) C[k] -= B[i + h - 1][j][k];
        if (i != 0) {
          rep(k, N) C[k] -= B[i - 1][j + w][k];
          rep(k, N) C[k] += B[i - 1][j][k];
        }

        int cnt = 0;
        rep(k, N) if (C[k] != B[H - 1][W][k]) cnt++;
        cout << cnt << " ";
      }
      cout << "\n";
    }
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