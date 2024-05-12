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

// 連鎖消滅パズル
struct Solver {
  void solve() {
    /* input */
    while (true) {
      int H;
      cin >> H;
      if (H == 0) return;
      vvi board(H, vi(5));
      rep(i, H) rep(j, 5) cin >> board[i][j];

      /* solve */
      int score = 0;
      while (true) {
        bool endFlag = true;
        //
        rep(i, H) rep(j, 3) {
          if (board[i][j] == -1) continue;

          if (board[i][j] == board[i][j + 1] &&
              board[i][j] == board[i][j + 2]) {
            score += board[i][j] * 3;
            if (j < 2 && board[i][j] == board[i][j + 3]) {
              score += board[i][j];
              if (j < 1 && board[i][j] == board[i][j + 4]) {
                score += board[i][j];
                board[i][j + 4] = -1;
              }
              board[i][j + 3] = -1;
            }
            board[i][j + 2] = -1;
            board[i][j + 1] = -1;
            board[i][j] = -1;
            endFlag = false;
          }
        }
        // 判定
        if (endFlag) break;
        // boardの更新
        // 下から更新すればよい
        rep(j, 5) for (int i = H - 1; i > 0; i--) {
          if (board[i][j] != -1) continue;
          for (int k = 1; i - k >= 0; k++) {
            if (board[i - k][j] != -1) {
              swap(board[i][j], board[i - k][j]);
              break;
            }
          }
        }
        debug(board);
      }
      cout << score << endl;

      /* output */
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