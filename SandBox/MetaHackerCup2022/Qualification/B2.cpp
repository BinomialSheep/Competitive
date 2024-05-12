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
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      int R, C;
      cin >> R >> C;
      vs S(R);
      rep(i, R) cin >> S[i];

      /* solve */
      vi dy = {-1, 0, 0, 1};
      vi dx = {0, -1, 1, 0};
      string ans = "Possible";
      if (R != 1 && C != 1) {
        // 石に挟まれた区間はx
        vvi visited(R, vi(C));
        rep(i, R) rep(j, C) {
          if (S[i][j] == '#') {
            if (visited[i][j]) continue;
            visited[i][j] = 1;
            queue<pii> q;
            rep(k, 4) {
              int y = i + dy[k];
              int x = j + dx[k];
              if (y < 0 || x < 0 || y >= R || x >= C) continue;
              visited[y][x] = 1;
              int cnt = 0;
              rep(k2, 4) {
                int y2 = y + dy[k2];
                int x2 = x + dx[k2];
                if (y2 < 0 || x2 < 0 || y2 >= R || x2 >= C) continue;
                if (S[y2][x2] == '^' || S[y2][x2] == '.') cnt++;
              }
              if (cnt >= 2) continue;
              // フレンドを作れない箇所
              if (S[y][x] == '.') S[y][x] = 'x';
              q.emplace(y, x);
            }
            while (!q.empty()) {
              auto p = q.front();
              q.pop();
              rep(k, 4) {
                int y = p.first + dy[k];
                int x = p.second + dx[k];
                if (y < 0 || x < 0 || y >= R || x >= C) continue;
                int cnt = 0;
                rep(k2, 4) {
                  int y2 = y + dy[k2];
                  int x2 = x + dx[k2];
                  if (y2 < 0 || x2 < 0 || y2 >= R || x2 >= C) continue;
                  if (S[y2][x2] == '^' || S[y2][x2] == '.') cnt++;
                }
                if (cnt >= 2) continue;

                // フレンドを作れない箇所
                if (S[y][x] == '.') S[y][x] = 'x';
                if (visited[y][x]) continue;
                visited[y][x] = 1;
                q.emplace(y, x);
              }
            }
          }
        }
        rep(i, R) rep(j, C) if (S[i][j] == '.') S[i][j] = '^';
        rep(i, R) rep(j, C) if (S[i][j] == 'x') S[i][j] = '.';
        rep(i, R) rep(j, C) {
          if (S[i][j] == '^') {
            int cnt = 0;
            rep(k, 4) {
              int y = i + dy[k];
              int x = j + dx[k];
              if (y < 0 || x < 0 || y >= R || x >= C) continue;
              if (S[y][x] == '^') cnt++;
            }
            if (cnt <= 1) ans = "Impossible";
          }
        }

      } else {
        rep(i, R) rep(j, C) {
          if (S[i][j] == '^') ans = "Impossible";
        }
      }

      /* output */
      printf("Case #%d: %s\n", ti + 1, ans.c_str());
      if (ans == "Possible") {
        rep(i, R) cout << S[i] << "\n";
      }
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