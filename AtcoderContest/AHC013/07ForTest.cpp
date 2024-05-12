#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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
#include <atcoder/all>
using namespace atcoder;
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

struct PairUnionFind {
  map<pair<int, int>, pair<int, int>> parent;
  PairUnionFind() : parent() {}

  pair<int, int> find(pair<int, int> x) {
    if (parent.find(x) == parent.end()) {
      parent[x] = x;
      return x;
    } else if (parent[x] == x) {
      return x;
    } else {
      parent[x] = find(parent[x]);
      return parent[x];
    }
  }

  void unite(pair<int, int> x, pair<int, int> y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      parent[x] = y;
    }
  }
};

int N, K;
vs originC;
ll sumScore;  // 手元でのデバッグ用

int calcScore(vs &c, vvi &cons) {
  PairUnionFind uf;

  rep(i, (int)cons.size()) {
    pii p1(cons[i][0], cons[i][1]);
    pii p2(cons[i][2], cons[i][3]);
    uf.unite(p1, p2);
  }

  // コンピュータが存在する座標を全部入れて全探索
  vpii coms;
  rep(i, N) rep(j, N) if (c[i][j] != '0' && c[i][j] != 'x')
      coms.emplace_back(i, j);

  int ret = 0;
  rep(i, (int)coms.size()) rep(j, i) {
    auto c1 = coms[i];
    auto c2 = coms[j];
    if (uf.find(c1) == uf.find(c2)) {
      ret += (c[c1.first][c1.second] == c[c2.first][c2.second]) ? 1 : -1;
    }
  }
  return max(ret, 0);
}

vi xs = {-1, 0, 0, 1};
vi ys = {0, -1, 1, 0};
vpii decideMove(dsu &uf, char ck, map<pii, int> &invP, pii start, vs &c,
                int pidx, int maxD, int &maxChange, pii &changeP) {
  vpii changePiis;
  int dist = -1;

  queue<pair<pii, vpii>> q;
  vpii emp;
  q.emplace(start, emp);

  set<pii> visited;

  while (!q.empty()) {
    auto piis = q.front().second;
    auto p = q.front().first;
    q.pop();
    piis.emplace_back(p);
    visited.insert(p);

    rep(di, 4) {
      for (int i = 1; i < N; i++) {
        int y = p.first + ys[di] * i;
        int x = p.second + xs[di] * i;
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] == '0') continue;
        if (c[y][x] == 'x') break;
        if (c[y][x] != ck) break;
        auto p2 = make_pair(y, x);
        if (uf.same(invP[p2], pidx)) break;
        if (chmax(maxChange, uf.size(invP[p2]))) {
          changePiis = piis, changeP = p2;
          dist = i;
        } else if (i < dist && maxChange == uf.size(invP[p2])) {
          changePiis = piis, changeP = p2;
          dist = i;
        }
        break;
      }
    }
    dist = -1;
    if ((int)piis.size() < maxD) {
      // 本当はxを超えて移動してもいいが複雑なので一旦これで
      rep(di, 4) {
        int y = p.first + ys[di];
        int x = p.second + xs[di];
        if (y < 0 || y == N || x < 0 || x == N) continue;
        if (c[y][x] != '0') continue;
        auto yx = make_pair(y, x);
        if (!visited.count(yx)) q.emplace(yx, piis);
      }
    }
  }
  return changePiis;
}

void annealing(double endTime, vvi &nowMoves, vvi &nowCons, vs &nowC,
               map<pii, int> invP, int nowMaxD, vector<vpii> points, vi &ks) {
  // 時間管理用
  auto startClock = system_clock::now();
  double time = 0.0;
  // デバッグ用
  vector<int> cntY(K);  // 数字ごとの接続本数
  int cnt = 0;
  // efficient用
  // vector<vector<double>> effifientDbg(K, vector<double>(100));
  int falthCount = 0;

  dsu uf(K * 100);
  int X = 0;
  int Y = 0;

  while (true) {
    for (int ki : ks) {
      rep(_pi, 100) {
        // int pi = randXor() % 100;
        int pi = _pi;
        cnt++;
        // 時間更新
        time = ((double)duration_cast<microseconds>(system_clock::now() -
                                                    startClock)
                    .count() *
                1e-6);
        // tmp：5本分余裕を持たせておく
        if (time > endTime || X + Y >= K * 100) {
          // debug(nowMaxD, time, cnt);
          // debug(effifientDbg);
          // debug(falthCount);

          return;
        }

        char ck = (char)('0' + ki + 1);
        // points[ki][pi]を動かす
        int pidx = ki * 100 + pi;
        // 幅優先探索して、動かすか決める
        int maxD = min(nowMaxD, K * 100 - X - Y);
        if (uf.size(pidx) != 1) {
          // どこかと繋がっているので動かしてはいけない（動かさずに繋ぐのはOK）
          maxD = 0;
        }

        int maxChange = 0;
        pii changeP;
        vpii changePiis = decideMove(uf, ck, invP, points[ki][pi], nowC, pidx,
                                     maxD, maxChange, changeP);

        if (maxChange == 0) continue;
        // アドホック：どうせ余るので、効率の悪い接続はしないでおく
        {
          falthCount++;
          int plus = uf.size(pidx) + uf.size(invP[changeP]);
          plus = plus * (plus - 1) / 2;
          double efficiency = (double)plus / (int)changePiis.size();
          if (falthCount <= 1000) {
            if (cntY[ki] <= 10 || K * 100 - X - Y <= 5) {
              if (efficiency < 1) continue;
            } else if (cntY[ki] <= 20) {
              if (efficiency < 3) continue;
            } else if (cntY[ki] <= 40) {
              if (efficiency < 5) continue;
            } else if (cntY[ki] <= 50) {
              if (efficiency < 30) continue;
            } else {
              if (efficiency < 100) continue;
            }
          }
          // effifientDbg[ki][cntY[ki]] = efficiency;
        }

        // debug(pidx, maxChange, changePiis);
        //  1番いいところに移動して繋ぐ
        if (changePiis.size() > 1) {
          rep(i, (int)changePiis.size() - 1) {
            nowMoves.push_back(vi(4));
            nowMoves.back()[0] = changePiis[i].first;
            nowMoves.back()[1] = changePiis[i].second;
            nowMoves.back()[2] = changePiis[i + 1].first;
            nowMoves.back()[3] = changePiis[i + 1].second;
          }
          X += (int)changePiis.size() - 1;

          // 座標の移動
          invP.erase(points[ki][pi]);
          nowC[points[ki][pi].first][points[ki][pi].second] = '0';
          points[ki][pi].first = nowMoves.back()[2];
          points[ki][pi].second = nowMoves.back()[3];
          invP[points[ki][pi]] = pidx;
          nowC[points[ki][pi].first][points[ki][pi].second] = ck;
        }

        Y++;
        cntY[ki]++;
        nowCons.push_back(vi(4));
        nowCons.back()[0] = points[ki][pi].first;
        nowCons.back()[1] = points[ki][pi].second;
        nowCons.back()[2] = changeP.first;
        nowCons.back()[3] = changeP.second;
        uf.merge(pidx, invP[changeP]);
        // debug(pidx, invP[changeP]);
        //  接続した線をxで埋める
        if (points[ki][pi].first == changeP.first) {
          int from = points[ki][pi].second;
          int to = changeP.second;
          if (to < from) swap(to, from);
          if (from - to == 1) break;  // 隣り合っていれば消すところはない
          int y = points[ki][pi].first;
          for (int i = from + 1; i < to; i++) {
            nowC[y][i] = 'x';
          }
        } else {
          int from = points[ki][pi].first;
          int to = changeP.first;
          if (to < from) swap(to, from);
          if (from - to == 1) break;  // 隣り合っていれば消すところはない
          int x = points[ki][pi].second;
          for (int i = from + 1; i < to; i++) {
            nowC[i][x] = 'x';
          }
        }
      }
    }
    if (nowMaxD < 9) nowMaxD++;
  }
}

// x埋めとconsへの追加を行う（※unionFindやYのインクリメントは行わない）
void connect(int y1, int x1, int y2, int x2, vvi &cons, vs &c) {
  // 間を'x'で埋める
  if (y1 == y2) {
    int from = x1;
    int to = x2;
    if (to < from) swap(to, from);
    if (from - to == 1) return;  // 隣り合っていれば消すところはない
    for (int xi = from + 1; xi < to; xi++) {
      c[y1][xi] = 'x';
    }
  } else {
    int from = y1;
    int to = y2;
    if (to < from) swap(to, from);
    if (from - to == 1) return;  // 隣り合っていれば消すところはない
    for (int yi = from + 1; yi < to; yi++) {
      c[yi][x1] = 'x';
    }
  }
  // consに加える
  cons.push_back(vi(4));
  cons.back()[0] = y1;
  cons.back()[1] = x1;
  cons.back()[2] = y2;
  cons.back()[3] = x2;
  // debug用
  // debug(y1, x1, y2, x2);
}

void tryhub(vvi &cons, vs &c, int X, vvb &isHub) {
  dsu uf(N * N);

  int Y = (int)cons.size();

  rep(i, (int)cons.size()) {
    int p1 = cons[i][0] * N + cons[i][1];
    int p2 = cons[i][2] * N + cons[i][3];
    uf.merge(p1, p2);
  }

  //
  rep(i, N) rep(j, N) {
    if (X + Y >= K * 100 - 1) return;
    if (c[i][j] == '0' || c[i][j] == 'x') continue;
    // とりあえず他とくっついてるやつは入れない
    if (uf.size(i * N + j) != 1) continue;

    // 隣接しているコンピュータを列挙
    map<char, vpii> mp;
    char ck = c[i][j];
    rep(di, 4) {
      for (int k = 1; k < N; k++) {
        int y = i + ys[di] * k;
        int x = j + xs[di] * k;
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] == '0') continue;
        if (c[y][x] == ck || c[y][x] == 'x') break;
        if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
        mp[c[y][x]].emplace_back(y, x);
        break;
      }
    }
    //
    int mp1 = -1, mp2 = -1;
    // どの座標のハブになるのが最善か
    for (auto p : mp) {
      int sz = (int)p.second.size();
      if (sz <= 1) continue;
      int mx = 2;
      pii pairP1, pairP2;

      rep(a, sz) rep(b, a) {
        int p1 = p.second[a].first * N + p.second[a].second;
        int p2 = p.second[b].first * N + p.second[b].second;
        if (uf.same(p1, p2)) continue;  // 既に同じ島なら繋げる意味ない
        // ここでサイズが欲しいので、ufを改良するかACL ufを使うことを検討
        if (chmax(mx, uf.size(p1) + uf.size(p2))) {
          pairP1 = p.second[a];
          pairP2 = p.second[b];
        }
      }
      // どの座標のハブにもしない
      if (mx <= 5) break;
      mp1 = pairP1.first * N + pairP1.second;
      mp2 = pairP2.first * N + pairP2.second;
    }
    if (mp1 == -1) continue;
    // (i, j)をp1とp2のハブにする
    isHub[i][j] = true;
    uf.merge(i * N + j, mp1);
    uf.merge(mp1, mp2);
    Y++;
    connect(i, j, mp1 / N, mp1 % N, cons, c);
    connect(i, j, mp2 / N, mp2 % N, cons, c);
  }
}

vvi deletePair(vvi &cons) {
  vvi ret;
  dsu uf(N * N);
  int Y = (int)cons.size();
  rep(i, Y) {
    int p1 = cons[i][0] * N + cons[i][1];
    int p2 = cons[i][2] * N + cons[i][3];
    uf.merge(p1, p2);
  }
  rep(i, Y) {
    int p1 = cons[i][0] * N + cons[i][1];
    if (uf.size(p1) >= 3) ret.push_back(cons[i]);
  }
  return ret;
}

void finishingPair(vvi &cons, vs &c, int X, vvb &isHub) {
  dsu uf(N * N);
  int Y = (int)cons.size();
  rep(i, Y) {
    int p1 = cons[i][0] * N + cons[i][1];
    int p2 = cons[i][2] * N + cons[i][3];
    uf.merge(p1, p2);
  }
  rep(i, N) rep(j, N) {
    if (c[i][j] == '0' || c[i][j] == 'x') continue;
    if (isHub[i][j]) continue;
    char ck = c[i][j];

    rep(di, 4) {
      if (X + Y >= K * 100) return;
      for (int k = 1; k < N; k++) {
        int y = i + ys[di] * k;
        int x = j + xs[di] * k;
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] == '0') continue;
        if (c[y][x] != ck || c[y][x] == 'x') break;
        if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
        if (uf.same(i * N + j, y * N + x)) break;  // 既に繋がってるなら繋げない
        uf.merge(i * N + j, y * N + x);
        Y++;
        connect(i, j, y, x, cons, c);
        break;
      }
    }
    //
  }
}

void printOutput(vvi &moves, vvi &cons) {
  int X = (int)moves.size();
  int Y = (int)cons.size();
  cout << X << "\n";
  rep(i, X) printf("%d %d %d %d\n", moves[i][0], moves[i][1], moves[i][2],
                   moves[i][3]);
  cout << Y << "\n";
  rep(i, Y)
      printf("%d %d %d %d\n", cons[i][0], cons[i][1], cons[i][2], cons[i][3]);
}

struct Solver {
  void solve() {
    /* input */
    cin >> N >> K;
    originC.resize(N);
    rep(i, N) cin >> originC[i];

    /* solve */
    vector<vpii> points(K);
    map<pii, int> invP;

    rep(i, N) rep(j, N) {
      if (originC[i][j] != '0') {
        auto p = make_pair(i, j);
        points[originC[i][j] - '0' - 1].push_back(p);
        int v = (originC[i][j] - '0' - 1) * 100 +
                (int)points[originC[i][j] - '0' - 1].size() - 1;
        invP[p] = v;
      }
    }

    auto startClock = system_clock::now();
    double nowTime;
    vvi bestMoves;
    vvi bestCons;
    int bestScore = 0;
    vi ds;

    vi bestScores(4, -1);

    int num = 2;
    double time = 0.5;
    if (K == 2) {
      num = 10;
      time = 0.12;
      rep(i, 10) { ds.push_back(i); }
    } else if (K == 3) {
      num = 5;
      time = 0.25;
      ds.push_back(0);
      ds.push_back(2);
      ds.push_back(4);
      ds.push_back(6);
      ds.push_back(8);
    } else if (K == 4) {
      num = 4;
      time = 0.3;
      ds.push_back(5);
      ds.push_back(7);
      ds.push_back(8);
      ds.push_back(10);
    } else {
      ds.push_back(8);
      ds.push_back(10);
    }

    rep(i, num) {
      vvi moves;
      vvi cons;
      int nowMaxD = ds[i];
      vs c = originC;

      auto before = system_clock::now();

      auto nowT = [&] {
        double now =
            ((double)duration_cast<microseconds>(system_clock::now() - before)
                 .count() *
             1e-6);

        return now;
      };

      vi ks(K);
      rep(j, K) ks[j] = (j + i) % K;
      annealing(time, moves, cons, c, invP, nowMaxD, points, ks);

      int X = (int)moves.size();
      vi score(4, -1);
      score[0] = calcScore(c, cons);
      // ペア削除
      if (X + (int)cons.size() >= K * 90) {
        cons = deletePair(cons);
        score[1] = calcScore(c, cons);
      }
      // 繋げ直し
      vvb isHub(N, vb(N));
      tryhub(cons, c, X, isHub);
      score[2] = calcScore(c, cons);
      // 仕上げ
      finishingPair(cons, c, X, isHub);
      score[3] = calcScore(c, cons);

      // printOutput(moves, cons);
      // return;

      int nowScore = calcScore(c, cons);
      debug(i, nowScore);
      if (chmax(bestScore, nowScore)) {
        bestMoves = moves;
        bestCons = cons;
        bestScores = score;
      }
    }

    // debug("探索終了", calcScore(c, cons), nowT());
    // // ペアを削除する
    // if (X + (int)cons.size() >= K * 90) {
    //   cons = deletePair(cons);
    //   debug("ペア削除", calcScore(c, cons), nowT());
    // }
    // // 繋げ直しを試みる
    // vvb isHub(N, vb(N));
    // tryhub(cons, c, X, isHub);
    // debug("繋げ直し", calcScore(c, cons), nowT());
    // // ギリギリまでペアにする
    // finishingPair(cons, c, X, isHub);
    // debug("仕上げ", calcScore(c, cons), nowT());

    // デバッグ用のスコア計算

    nowTime =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);
    debug(nowTime);
    printf("%d %d %d %d %d %d %.4f\n", K, N, bestScores[0], bestScores[1],
           bestScores[2], bestScores[3], nowTime);
    sumScore += bestScore;

    /* output */
    // printOutput(bestMoves, bestCons);
  }
};

int main() {
  int ts = 100;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
    debug(ti);
  }

  cout << sumScore << endl;
  return 0;
}