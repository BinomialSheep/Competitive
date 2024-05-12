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
    int N;
    cin >> N;
    vs A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    string ans;
    char start = '0';
    rep(i, N) rep(j, N) chmax(start, A[i][j]);

    debug(A, start);

    rep(i, N) rep(j, N) {
      if (A[i][j] == start) {
        for (int ddy = -1; ddy <= 1; ddy++) {
          for (int ddx = -1; ddx <= 1; ddx++) {
            if (ddy == 0 && ddx == 0) continue;
            string tmp;
            tmp += start;
            int y = i;
            int x = j;
            rep(k, N - 1) {
              y += ddy;
              x += ddx;
              if (y == -1) y = N - 1;
              if (y == N) y = 0;
              if (x == -1) x = N - 1;
              if (x == N) x = 0;
              tmp += A[y][x];
            }
            chmax(ans, tmp);
          }
        }
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