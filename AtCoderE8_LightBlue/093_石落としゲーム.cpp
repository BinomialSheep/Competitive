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
    int H, W, K;
    cin >> H >> W >> K;
    vvi c(H, vi(W));
    rep(i, H) {
      string s;
      cin >> s;
      rep(j, W) c[i][j] = s[j] - '0';
    }
    debug(c);

    /* solve */
    int ans = 0;
    rep(di, H) rep(dj, W) {
      // i, jを消す
      vvi board = c;
      board[di][dj] = -1;
      int score = 0;
      for (int turn = 0;; turn++) {
        bool endFlag = true;
        // 地図の更新
        rep(j, W) {
          deque<int> q;
          rep(i, H) {
            if (board[H - 1 - i][j] != -1) {
              q.push_back(board[H - 1 - i][j]);
              board[H - 1 - i][j] = -1;
            }
          }
          rep(i, (int)q.size()) board[H - 1 - i][j] = q[i];
        }
        // debug(board);
        //  消滅と計算
        rep(i, H) {
          // 隣り合っている個所を見つける
          deque<pii> q;
          rep(j, W) {
            if (q.empty()) {
              q.emplace_back(board[i][j], 1);
              continue;
            }
            if (q.back().first == board[i][j]) {
              q.back().second++;
            } else {
              q.emplace_back(board[i][j], 1);
            }
          }
          rep(j, W) {
            if (q.front().first != -1 && q.front().second >= K) {
              score += (1 << turn) * q.front().first * q.front().second;
              q.front().first = -1;
              endFlag = false;
            }
            board[i][j] = q.front().first;
            q.front().second--;
            if (q.front().second == 0) q.pop_front();
          }
        }
        if (endFlag) break;
      }
      chmax(ans, score);
      // debug(di, dj, score);
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