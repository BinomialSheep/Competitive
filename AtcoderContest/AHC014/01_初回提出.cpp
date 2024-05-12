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
    vi dy = {1, 1, -1, -1};
    vi dx = {1, -1, 1, -1};

    // 各頂点の、縦横、(todo 斜めは別
    set<int> used;
    auto isUsed = [&](int x, int y) { return used.count(x * N + y) != 0; };
    auto use = [&](int x, int y) { used.insert(x * N + y); };

    auto exec = [&](int startX, int startY) {
      rep(j, 4) {
        int x = startX, y = startY;
        if (isUsed(x, y)) continue;
        int flagX = 0, flagY = 0;
        
        
          if (isUsed(x, startY)) break;
          if (G[x][startY] > 0) {
            flagX = 1;
            break;
          }
        }
        if (!flagX) continue;
        for (y += dy[j]; 0 <= y && y < N; y += dy[j]) {
          if (isUsed(startX, y)) break;
          if (G[startX][y] > 0) {
            flagY = 1;
            break;
          }
        }
        if (!flagY) y = startY;
        // debug(startX, startY, x, y);

        bool isNg = false;
        for (int xx = min(x, startX) + 1; xx < max(x, startX); xx++) {
          if (G[xx][y] != 0 || isUsed(xx, y)) {
            isNg = true;
            break;
          }
        }
        if (isNg) continue;
        for (int yy = min(y, startY) + 1; yy < max(y, startY); yy++) {
          if (G[x][yy] != 0 || isUsed(x, yy)) {
            isNg = true;
            break;
          }
        }
        if (isNg) continue;

        assert(G[startX][startY] > 0);
        assert(G[x][startY] > 0);
        assert(G[startX][y] > 0);
        assert(!isUsed(startX, startY));
        assert(!isUsed(x, startY));
        assert(!isUsed(startX, y));

        if (G[x][y] == 0) {
          ansX.push_back({x, startX, startX, x});
          ansY.push_back({y, y, startY, startY});
          G[x][y] = 1;
          // 使った辺の更新
          use(startX, startY);
          use(x, startY);
          use(startX, y);
          use(x, y);
          // debug(startX, startY, x, y);
          break;
        }
      }
    };

    rep(loop, 10) {
      rep(i, M) { exec(inx[i], iny[i]); }
      // 途中でansが増えることによるバグ回避
      // int sz = ansX.size();
      // 斜め実装していないのでやっても無駄
      // rep(i, sz) { exec(ansX[i][0], ansY[i][0]); }
    }
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