#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
using namespace std;
using namespace chrono;
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

static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

ll sumScore = 0;  // 手元でのデバッグ用

struct Solver {
  int N, M;
  int c;
  vi inx, iny;

  ll calcDist(int x, int y) {
    return (x - c) * (x - c) + (y - c) * (y - c) + 1;
  }

  double calcScore(vvi &x, vvi &y, int K) {
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
    vi dx = {1, -1, -1, 1};
    vi dy = {1, 1, -1, -1};

    // 各頂点から各方向に辺が貼られているか（右, 上, 左, 下, 右上, 左上, 左下,
    // 右下）
    const int R = 0;
    const int T = 1;
    const int L = 2;
    const int B = 3;
    const int D4 = 4;
    const int D5 = 5;
    const int D6 = 6;
    const int D7 = 7;
    // 1は他線分の中、2は自身から線分が伸びている
    vvvi used(N, vvi(N, vi(8)));
    const int TR = 10;
    const int TL = 12;
    const int BR = 30;
    const int BL = 32;
    const int D45 = 45;
    const int D56 = 56;
    const int D67 = 67;
    const int D74 = 74;
    auto isUsed = [&](int x, int y, int d2) {
      if (d2 == TR) return used[x][y][T] || used[x][y][R];
      if (d2 == TL) return used[x][y][T] || used[x][y][L];
      if (d2 == BR) return used[x][y][B] || used[x][y][R];
      if (d2 == BL) return used[x][y][B] || used[x][y][L];
      if (d2 == D45) return used[x][y][D4] || used[x][y][D5];
      if (d2 == D56) return used[x][y][D5] || used[x][y][D6];
      if (d2 == D67) return used[x][y][D6] || used[x][y][D7];
      return used[x][y][D7] || used[x][y][D4];
    };

    auto isEmpG = [&](int x, int y) {
      return 0 <= x && x < N && 0 <= y && y < N && G[x][y] == 0;
    };

    // 行、列ごとの頂点集合
    vector<set<int>> row(N + 1);  // todo Nで良さそう
    vector<set<int>> column(N + 1);
    rep(i, M) {
      column[inx[i]].insert(iny[i]);
      row[iny[i]].insert(inx[i]);
    }

    // 間に頂点があるか
    auto hasBetweenV = [&](int sx, int sy, int ex, int xi, int yi) {
      for (int x = sx + xi, y = sy + yi; x != ex; x += xi, y += yi) {
        if (G[x][y] > 0) return true;
      }
      return false;
    };

    // 追加された頂点の周りに辺があるか確認（愚直）
    vi dx2 = {-1, 0, 1, 0, -1, 1, 1, -1};
    vi dy2 = {0, -1, 0, 1, -1, -1, 1, 1};
    auto checkEdeg = [&](int sx, int sy) {
      // if (sx == 30 && sy == 27) debug(used[sx][sy]);
      rep(i, 8) {
        int j = i < 4 ? (i + 2) % 4 : (i + 2) % 4 + 4;
        if (used[sx][sy][j]) continue;
        for (int x = sx + dx2[i], y = sy + dy2[i];
             0 <= x && x < N && 0 <= y && y < N; x += dx2[i], y += dy2[i]) {
          // if (sx == 30 && sy == 27) {
          //   debug(x, y, used[x][y]);
          // }
          if (used[x][y][i]) {
            used[sx][sy][j] = 1;
            break;
          }
          if (G[x][y] > 0) break;
        }
      }
      // if (sx == 30 && sy == 27) debug(used[sx][sy]);
    };

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
              d = 0, x = r, y = t;
              mx = calcDist(x, y);
            }
          }
        }
      }
      if (t != -1 && l != -1 && !G[l][t]) {
        ll dist = calcDist(l, t);
        if (mx < dist || randXor() % 4 == 3) {
          if (!isUsed(l, startY, TR) && !isUsed(startX, t, BL)) {
            // lの右がx以上、xの上がt以上
            auto itx = row[t].upper_bound(l);
            if (itx == row[t].end() || *itx >= startX) {
              auto ity = column[l].upper_bound(startY);
              if (ity == column[l].end() || *ity >= t) {
                mx = dist, d = 1, x = l, y = t;
              }
            }
          }
        }
      }
      if (l != -1 && b != -1 && !G[l][b]) {
        ll dist = calcDist(l, b);
        if (mx < dist || randXor() % 4 == 3) {
          if (!isUsed(l, startY, BR) && !isUsed(startX, b, TL)) {
            // lの右がx以上、bの上がy以上
            auto itx = row[b].upper_bound(l);
            if (itx == row[b].end() || *itx >= startX) {
              auto ity = column[l].upper_bound(b);
              if (ity == column[l].end() || *ity >= startY) {
                mx = dist, d = 2, x = l, y = b;
              }
            }
          }
        }
      }
      if (b != -1 && r != -1 && !G[r][b]) {
        ll dist = calcDist(l, b);
        if (mx < dist || randXor() % 4 == 3) {
          if (!isUsed(r, startY, BL) && !isUsed(startX, b, TR)) {
            // xの右がr、bの上がy
            auto itx = row[b].upper_bound(startX);
            if (itx == row[b].end() || *itx >= r) {
              auto ity = column[r].upper_bound(b);
              if (ity == column[r].end() || *ity >= startY) {
                mx = dist, d = 3, x = r, y = b;
              }
            }
          }
        }
      }
      // どの方向にも置けないなら何もしない
      if (d == -1) return;

      // if (startX == 34 && startY == 27) {
      //   debug(used[30][25]);
      //   debug(used[34][25]);
      //   debug(used[34][27]);
      //   debug(used[30][27]);
      // }

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
        used[startX][startY][R] = 2;
        used[startX][startY][T] = 2;
        used[x][startY][T] = 2;
        used[x][startY][L] = 2;
        used[x][y][L] = 2;
        used[x][y][B] = 2;
        used[startX][y][B] = 2;
        used[startX][y][R] = 2;
      } else if (d == 1) {
        used[startX][startY][T] = 2;
        used[startX][startY][L] = 2;
        used[startX][y][L] = 2;
        used[startX][y][B] = 2;
        used[x][y][B] = 2;
        used[x][y][R] = 2;
        used[x][startY][R] = 2;
        used[x][startY][T] = 2;
      } else if (d == 2) {
        used[startX][startY][L] = 2;
        used[startX][startY][B] = 2;
        used[x][startY][B] = 2;
        used[x][startY][R] = 2;
        used[x][y][R] = 2;
        used[x][y][T] = 2;
        used[startX][y][T] = 2;
        used[startX][y][L] = 2;
      } else {
        used[startX][startY][B] = 2;
        used[startX][startY][R] = 2;
        used[startX][y][R] = 2;
        used[startX][y][T] = 2;
        used[x][y][T] = 2;
        used[x][y][L] = 2;
        used[x][startY][L] = 2;
        used[x][startY][B] = 2;
      }
      checkEdeg(x, y);
      // debug("exe", startX, startY, x, y);
    };
    // 斜め方向
    auto execDiagonal = [&](int startX, int startY) {
      int r = -1, t = -1, l = -1, b = -1;
      rep(i, 4) {
        int x = startX, y = startY;
        if (used[startX][startY][4 + i]) continue;
        for (x += dx[i], y += dy[i]; 0 <= x && x < N && 0 <= y && y < N;
             x += dx[i], y += dy[i]) {
          if (G[x][y] > 0) {
            if (i == 0) r = abs(x - startX);
            if (i == 1) t = abs(x - startX);
            if (i == 2) l = abs(x - startX);
            if (i == 3) b = abs(x - startX);
            break;
          }
        }
      }

      int d = -1;
      int mx = 0;
      int mxy, mxx;
      int rx = startX + r, ry = startY + r;
      int tx = startX - t, ty = startY + t;
      int lx = startX - l, ly = startY - l;
      int bx = startX + b, by = startY - b;
      if (r != -1 && t != -1) {
        int x = startX + r - t, y = startY + r + t;
        ll dist = calcDist(x, y);
        if (isEmpG(x, y) && !isUsed(rx, ry, D56) && !isUsed(tx, ty, D74)) {
          bool isNG =
              hasBetweenV(rx, ry, x, -1, 1) || hasBetweenV(tx, ty, x, 1, 1);
          if (!isNG) {
            mx = dist, d = 4, mxx = x, mxy = y;
          }
        }
      }
      if (t != -1 && l != -1) {
        int x = startX - t - l, y = startY + t - l;
        ll dist = calcDist(x, y);
        if (mx < dist || randXor() % 4 == 3) {
          if (isEmpG(x, y) && !isUsed(tx, ty, D67) && !isUsed(lx, ly, D45)) {
            bool isNG =
                hasBetweenV(tx, ty, x, -1, -1) || hasBetweenV(lx, ly, x, -1, 1);
            if (!isNG) {
              mx = dist, d = 5, mxx = x, mxy = y;
            }
          }
        }
      }
      if (l != -1 && b != -1) {
        int x = startX - l + b, y = startY - l - b;
        ll dist = calcDist(x, y);
        if (mx < dist || randXor() % 4 == 3) {
          if (isEmpG(x, y) && !isUsed(lx, ly, D74) && !isUsed(bx, by, D56)) {
            bool isNG =
                hasBetweenV(lx, ly, x, 1, -1) || hasBetweenV(bx, by, x, -1, -1);
            if (!isNG) {
              mx = dist, d = 6, mxx = x, mxy = y;
            }
          }
        }
      }
      if (b != -1 && r != -1) {
        int x = startX + b + r, y = startY - b + r;
        ll dist = calcDist(x, y);
        if (mx < dist || randXor() % 4 == 3) {
          if (isEmpG(x, y) && !isUsed(bx, by, D45) && !isUsed(rx, ry, D67)) {
            bool isNG =
                hasBetweenV(bx, by, x, 1, 1) || hasBetweenV(rx, ry, x, 1, -1);
            if (!isNG) {
              mx = dist, d = 7, mxx = x, mxy = y;
            }
          }
        }
      }
      // // どの方向にも置けないなら何もしない
      if (d == -1) return;

      // 最大の方向に置く
      row[mxy].insert(mxx);
      column[mxx].insert(mxy);
      assert(G[mxx][mxy] == 0);
      G[mxx][mxy] = 1;
      if (d == 4) {
        ansX.push_back({mxx, rx, startX, tx});
        ansY.push_back({mxy, ry, startY, ty});
        used[startX][startY][D4] = 2;
        used[startX][startY][D5] = 2;
        used[rx][ry][D5] = 2;
        used[rx][ry][D6] = 2;
        used[mxx][mxy][D6] = 2;
        used[mxx][mxy][D7] = 2;
        used[tx][ty][D7] = 2;
        used[tx][ty][D4] = 2;
      } else if (d == 5) {
        ansX.push_back({mxx, tx, startX, lx});
        ansY.push_back({mxy, ty, startY, ly});
        used[startX][startY][D5] = 2;
        used[startX][startY][D6] = 2;
        used[tx][ty][D6] = 2;
        used[tx][ty][D7] = 2;
        used[mxx][mxy][D7] = 2;
        used[mxx][mxy][D4] = 2;
        used[lx][ly][D4] = 2;
        used[lx][ly][D5] = 2;
      } else if (d == 6) {
        ansX.push_back({mxx, lx, startX, bx});
        ansY.push_back({mxy, ly, startY, by});
        used[startX][startY][D6] = 2;
        used[startX][startY][D7] = 2;
        used[lx][ly][D7] = 2;
        used[lx][ly][D4] = 2;
        used[mxx][mxy][D4] = 2;
        used[mxx][mxy][D5] = 2;
        used[bx][by][D5] = 2;
        used[bx][by][D6] = 2;
      } else {
        ansX.push_back({mxx, bx, startX, rx});
        ansY.push_back({mxy, by, startY, ry});
        used[startX][startY][D7] = 2;
        used[startX][startY][D4] = 2;
        used[bx][by][D4] = 2;
        used[bx][by][D5] = 2;
        used[mxx][mxy][D5] = 2;
        used[mxx][mxy][D6] = 2;
        used[rx][ry][D6] = 2;
        used[rx][ry][D7] = 2;
      }
      checkEdeg(mxx, mxy);
      // debug("exe2", startX, startY, mxx, mxy);
    };

    auto delAns = [&](int sx, int sy, int idx) {
      rep(i, 8) {
        if (used[sx][sy][i] != 2) {
          used[sx][sy][i] = 0;
          continue;
        }
        used[sx][sy][i] = 0;
        int j = i < 4 ? (i + 2) % 4 : (i + 2) % 4 + 4;
        for (int x = sx + dx2[j], y = sy + dy2[j];
             0 <= x && x < N && 0 <= y && y < N; x += dx2[j], y += dy2[j]) {
          if (G[x][y] > 0) {
            if (used[x][y][j] == 2) {
              used[x][y][j] = 0;
              break;
            }
            used[x][y][j] = 0;
          }
        }
      }
      G[sx][sy] = 0;
      // debug("delete", sx, sy, idx);
      ansX.erase(ansX.begin() + idx);
      ansY.erase(ansY.begin() + idx);
      column[sx].erase(sy);
      row[sy].erase(sx);
    };
    rep(loop, 50000) {
      rep(loop2, 3) {
        int sz = (M + ansX.size()) * 2;
        int num = randXor() % sz;
        if (num < M) {
          exec(inx[num], iny[num]);
        } else if (num < 2 * M) {
          num -= M;
          execDiagonal(inx[num], iny[num]);
        } else if (num < 2 * M + ansX.size()) {
          num -= 2 * M;
          assert(0 <= num && num < ansX.size());
          assert(G[ansX[num][0]][ansY[num][0]] == 1);
          exec(ansX[num][0], ansY[num][0]);
        } else {
          num -= 2 * M + (int)ansX.size();
          assert(0 <= num && num < ansX.size());
          assert(G[ansX[num][0]][ansY[num][0]] == 1);
          execDiagonal(ansX[num][0], ansY[num][0]);
        }

        if (loop % 10000 == 0 && loop2 == 0 && ansX.size()) {
          rep(j, 0) {
            int idx = num % (int)ansX.size();
            int x = ansX[idx][0];
            int y = ansY[idx][0];
            int cnt = 0;
            rep(i, 8) {
              if (used[x][y][i] == 2) cnt++;
            }
            if (cnt > 2) {
              num++;
            } else {
              assert(G[x][y] == 1);
              assert(column[x].count(y) == 1);
              assert(row[y].count(x) == 1);
              delAns(x, y, idx);
              assert(G[x][y] == 0);
              assert(column[x].count(y) == 0);
              assert(row[y].count(x) == 0);
              rep(i, 8) assert(used[x][y][i] != 2);
              break;
            }
          }
        }
      }
    }
    rep(loop, 5) {
      // 仕上げ
      rep(i, M) { exec(inx[i], iny[i]); }
      rep(i, M) { execDiagonal(inx[i], iny[i]); }
      int sz = ansX.size();
      rep(i, sz) { exec(ansX[i][0], ansY[i][0]); }
      sz = ansX.size();
      rep(i, sz) { execDiagonal(ansX[i][0], ansY[i][0]); }
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
    c = (N - 1) / 2;
    /* solve */
    int K = 0;
    vvi x, y;
    ll bestScore = 0;

    rep(i, 100) {
      vvi nowX;
      vvi nowY;
      vvi nowG = G;
      stupid(nowG, nowX, nowY);
      ll nowScore = (ll)calcScore(nowX, nowY, (int)nowX.size());
      if (chmax(bestScore, nowScore)) {
        if (x.size() == nowX.size()) {
          swap(x, nowX), swap(y, nowY);
        } else {
          x.resize(nowX.size());
          y.resize(nowY.size());
          rep(j, nowX.size()) {
            x[j] = nowX[j];
            y[j] = nowY[j];
          }
        }
      }
    }
    sumScore += bestScore;
    // debug(score);

    /* output */
    K = (int)x.size();

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
    debug(ti);
  }
  debug(sumScore);
  return 0;
}