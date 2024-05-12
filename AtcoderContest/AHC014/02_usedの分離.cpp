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
  int N, M;
  vi inx, iny;
  double calcScore(vvi &x, vvi &y, int K) {
    int c = (N - 1) / 2;
    double ret = 0;

    ll wSum = 0;
    rep(i, K) {
      wSum += (x[i][0] - c) * (x[i][0] - c) + (y[i][0] - c) * (y[i][0] - c) + 1;
    }
    rep(i, M) {
      wSum += (inx[i] - c) * (inx[i] - c) + (iny[i] - c) * (iny[i] - c) + 1;
    }

    // これ埋め込めるね
    ll S = 0;
    rep(i, N) rep(j, N) S += (i - c) * (i - c) + (j - c) * (j - c) + 1;

    ret += 1e6 * N * N * wSum / M / S;
    return ret;
  }

  void stupid(vvi &G, vvi &ansX, vvi &ansY) {
    // TODO 時間入れる
    // vi dy = {1, 1, -1, -1};
    // vi dx = {1, -1, 1, -1};

    // 各頂点から各方向に辺が貼られているか（右, 上, 左, 下, 右上, 左上, 左下,
    // 右下）
    const int R = 0;
    const int T = 1;
    const int L = 2;
    const int B = 3;
    vector<vvb> used(N, vvb(N, vb(8)));
    const int TR = 10;
    const int TL = 12;
    const int BR = 30;
    const int BL = 32;
    auto isUsed = [&](int x, int y, int d2) {
      if (d2 == TR) return used[x][y][T] || used[x][y][R];
      if (d2 == TL) return used[x][y][T] || used[x][y][L];
      if (d2 == BR) return used[x][y][B] || used[x][y][R];
      return used[x][y][B] || used[x][y][L];
    };
    // 行、列ごとの頂点集合
    vector<set<int>> row(N + 1);
    vector<set<int>> column(N + 1);
    rep(i, M) {
      column[inx[i]].insert(iny[i]);
      row[iny[i]].insert(inx[i]);
    }

    auto exec = [&](int startX, int startY) {
      // 上下左右方向
      // 右方向
      int r = -1;
      if (!used[startX][startY][R]) {
        auto it = row[startY].upper_bound(startX);
        if (it != row[startY].end()) r = *it;
      }
      // 上方向
      int t = -1;
      if (!used[startX][startY][T]) {
        auto it = column[startX].upper_bound(startY);
        if (it != column[startX].end()) t = *it;
      }
      // 左方向
      int l = -1;
      if (!used[startX][startY][L]) {
        auto it = row[startY].lower_bound(startX);
        if (it != row[startY].begin()) l = *(--it);
      }
      // 下方向
      int b = -1;
      if (!used[startX][startY][B]) {
        auto it = column[startX].lower_bound(startY);
        if (it != column[startX].begin()) b = *(--it);
      }

      // debug(startX, startY, r, t, l, b);

      int d = -1;
      int mx = 0;
      int y, x;
      if (r != -1 && t != -1 && !G[r][t]) {
        if (!isUsed(r, startY, TL) && !isUsed(startX, t, BR)) {
          // xの右がr以上, yの上がt以上
          auto itx = row[t].upper_bound(startX);
          if (itx == row[t].end() || *itx >= r) {
            auto ity = column[r].upper_bound(startY);
            if (ity == column[r].end() || *ity >= t) {
              mx = r + t, d = 0, x = r, y = t;
            }
          }
        }
      }
      if (t != -1 && l != -1 && !G[l][t] &&
          mx < abs(t - startY) + abs(l - startX)) {
        if (!isUsed(l, startY, TR) && !isUsed(startX, t, BL)) {
          // lの右がx以上、xの上がt以上
          auto itx = row[t].upper_bound(l);
          if (itx == row[t].end() || *itx >= startX) {
            auto ity = column[l].upper_bound(startY);
            if (ity == column[l].end() || *ity >= t) {
              mx = t + l, d = 1, x = l, y = t;
            }
          }
        }
      }
      if (l != -1 && b != -1 && !G[l][b] &&
          mx < abs(l - startX) + abs(b - startY)) {
        if (!isUsed(l, startY, BR) && !isUsed(startX, b, TL)) {
          // lの右がx以上、bの上がy以上
          auto itx = row[b].upper_bound(l);
          if (itx == row[b].end() || *itx >= startX) {
            auto ity = column[l].upper_bound(b);
            if (ity == column[l].end() || *ity >= startY) {
              mx = l + b, d = 2, x = l, y = b;
            }
          }
        }
      }
      if (b != -1 && r != -1 && !G[r][b] &&
          mx < abs(b - startY) + abs(r - startX)) {
        if (!isUsed(r, startY, BL) && !isUsed(startX, b, TR)) {
          // xの右がr、bの上がy
          auto itx = row[b].upper_bound(startX);
          if (itx == row[b].end() || *itx >= r) {
            auto ity = column[r].upper_bound(b);
            if (ity == column[r].end() || *ity >= startY) {
              mx = b + r, d = 3, x = r, y = b;
            }
          }
        }
      }
      // どの方向にも置けないなら何もしない
      if (d == -1) return;

      //最大の方向に置く
      // debug(x, y);
      assert(G[x][y] == 0);
      ansX.push_back({x, startX, startX, x});
      ansY.push_back({y, y, startY, startY});
      G[x][y] = 1;
      row[y].insert(x);
      column[x].insert(y);
      // 使った辺の更新
      if (d == 0) {
        used[startX][startY][R] = true;
        used[startX][startY][T] = true;
        used[x][startY][T] = true;
        used[x][startY][L] = true;
        used[x][y][L] = true;
        used[x][y][B] = true;
        used[startX][y][B] = true;
        used[startX][y][R] = true;
      } else if (d == 1) {
        used[startX][startY][T] = true;
        used[startX][startY][L] = true;
        used[startX][y][L] = true;
        used[startX][y][B] = true;
        used[x][y][B] = true;
        used[x][y][R] = true;
        used[x][startY][R] = true;
        used[x][startY][T] = true;
      } else if (d == 2) {
        used[startX][startY][L] = true;
        used[startX][startY][B] = true;
        used[x][startY][B] = true;
        used[x][startY][R] = true;
        used[x][y][R] = true;
        used[x][y][T] = true;
        used[startX][y][T] = true;
        used[startX][y][L] = true;
      } else {
        used[startX][startY][B] = true;
        used[startX][startY][R] = true;
        used[startX][y][R] = true;
        used[startX][y][T] = true;
        used[x][y][T] = true;
        used[x][y][L] = true;
        used[x][startY][L] = true;
        used[x][startY][B] = true;
      }

      // debug("exe", startX, startY, x, y);
    };

    // auto exec = [&](int startX, int startY) {
    //   rep(j, 4) {
    //     int x = startX, y = startY;
    //     if (isUsed(x, y, j)) continue;
    //     int flagX = 0, flagY = 0;
    //     for (x += dx[j]; 0 <= x && x < N; x += dx[j]) {
    //       if (isUsed(x, startY)) break;
    //       if (G[x][startY] > 0) {
    //         flagX = 1;
    //         break;
    //       }
    //     }
    //     if (!flagX) continue;
    //     for (y += dy[j]; 0 <= y && y < N; y += dy[j]) {
    //       if (isUsed(startX, y)) break;
    //       if (G[startX][y] > 0) {
    //         flagY = 1;
    //         break;
    //       }
    //     }
    //     if (!flagY) y = startY;
    //     // debug(startX, startY, x, y);

    //     bool isNg = false;
    //     for (int xx = min(x, startX) + 1; xx < max(x, startX); xx++) {
    //       if (G[xx][y] != 0 || isUsed(xx, y)) {
    //         isNg = true;
    //         break;
    //       }
    //     }
    //     if (isNg) continue;
    //     for (int yy = min(y, startY) + 1; yy < max(y, startY); yy++) {
    //       if (G[x][yy] != 0 || isUsed(x, yy)) {
    //         isNg = true;
    //         break;
    //       }
    //     }
    //     if (isNg) continue;

    //     assert(G[startX][startY] > 0);
    //     assert(G[x][startY] > 0);
    //     assert(G[startX][y] > 0);
    //     assert(!isUsed(startX, startY));
    //     assert(!isUsed(x, startY));
    //     assert(!isUsed(startX, y));

    //     if (G[x][y] == 0) {
    //       ansX.push_back({x, startX, startX, x});
    //       ansY.push_back({y, y, startY, startY});
    //       G[x][y] = 1;
    //       // 使った辺の更新
    //       use(startX, startY);
    //       use(x, startY);
    //       use(startX, y);
    //       use(x, y);
    //       // debug(startX, startY, x, y);
    //       break;
    //     }
    //   }
    // };

    rep(loop, 30) {
      rep(i, M) { exec(inx[i], iny[i]); }
      //   // 途中でansが増えることによるバグ回避
      int sz = ansX.size();
      rep(i, sz) { exec(ansX[i][0], ansY[i][0]); }
    }
    // 実装時の出力
    // rep(i, N) rep(j, N) {
    //   if (G[i][j] == 1) debug(i, j, used[i][j]);
    // }
  }

  void solve() {
    /* input */
    cin >> N >> M;
    inx.resize(M);
    iny.resize(M);
    rep(i, M) cin >> inx[i] >> iny[i];

    /* init */

    vvi G(N, vi(N));
    rep(i, M) G[inx[i]][iny[i]] = 1;

    /* solve */
    int K = 0;
    vvi x, y;

    stupid(G, x, y);
    K = x.size();

    double score = calcScore(x, y, K);
    debug(score);
    /* output */

    printf("%d\n", K);
    rep(i, K) printf("%d %d %d %d %d %d %d %d\n", x[i][0], y[i][0], x[i][1],
                     y[i][1], x[i][2], y[i][2], x[i][3], y[i][3]);
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