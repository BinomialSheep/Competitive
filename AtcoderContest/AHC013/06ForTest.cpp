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
  // cは現局面なので実はmovesはいらない？

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

    int highestScore = 0;
    rep(Di, 11) {
      auto startClock = system_clock::now();
      vvi bestMoves;
      vvi bestCons;
      int bestScore = 0;

      int num = 1;
      double time = 2.0;
      if (K == 2) {
        num = 10;
        time = 0.20;
      } else if (K == 3) {
        num = 5;
        time = 0.4;
      } else if (K == 4) {
        num = 2;
        time = 1.0;
      }

      rep(i, num) {
        vvi moves;
        vvi cons;
        int nowMaxD = Di;
        vs c = originC;

        vi ks(K);
        rep(j, K) ks[j] = (j + i) % K;
        mt19937 get_rand_mt(0);
        annealing(time, moves, cons, c, invP, nowMaxD, points, ks);
        int nowScore = calcScore(c, cons);
        debug(i, nowScore);
        if (chmax(bestScore, nowScore)) {
          bestMoves = moves;
          bestCons = cons;
        }
      }

      // デバッグ用のスコア計算

      double nowTime =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);
      cout << Di << " ";
      cout << K << " " << N << " " << bestScore << " " << nowTime << "\n";
      chmax(highestScore, bestScore);
    }
    sumScore += highestScore;

    /* output */
    // int X = (int)bestMoves.size();
    // int Y = (int)bestCons.size();
    // cout << X << "\n";
    // rep(i, X) printf("%d %d %d %d\n", bestMoves[i][0], bestMoves[i][1],
    //                  bestMoves[i][2], bestMoves[i][3]);
    // cout << Y << "\n";
    // rep(i, Y) printf("%d %d %d %d\n", bestCons[i][0], bestCons[i][1],
    //                  bestCons[i][2], bestCons[i][3]);
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