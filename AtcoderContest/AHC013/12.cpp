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

struct dsu {
 public:
  // root node: -1 * component size
  // otherwise: parent
  dsu() : _n(0) {}
  dsu(int n) : _n(n), parent_or_size(n, -1) {}

  int merge(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    int x = leader(a), y = leader(b);
    if (x == y) return x;
    if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
    parent_or_size[x] += parent_or_size[y];
    parent_or_size[y] = x;
    return x;
  }

  bool same(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    return leader(a) == leader(b);
  }

  int leader(int a) {
    assert(0 <= a && a < _n);
    if (parent_or_size[a] < 0) return a;
    return parent_or_size[a] = leader(parent_or_size[a]);
  }

  int size(int a) {
    assert(0 <= a && a < _n);
    return -parent_or_size[leader(a)];
  }

  void divide(int a, int b) {
    // assert(0 <= a && a < _n);
    // assert(0 <= b && b < _n);
    // assert(same(a, b));
    parent_or_size[a] = -1;
    parent_or_size[b] = -1;
  }

  void replace(int a, int b) {
    // aのリーダーをbに付け替える
    parent_or_size[b] = parent_or_size[a];
    parent_or_size[a] = -1;
    if (parent_or_size[b] < -1) {
      // TODO サイズの分付け替えたらreturnすると自明に改善
      rep(i, _n) {
        if (parent_or_size[i] == a) parent_or_size[i] = b;
      }
    }
  }

  std::vector<std::vector<int>> groups() {
    std::vector<int> leader_buf(_n), group_size(_n);
    for (int i = 0; i < _n; i++) {
      leader_buf[i] = leader(i);
      group_size[leader_buf[i]]++;
    }
    std::vector<std::vector<int>> result(_n);
    for (int i = 0; i < _n; i++) {
      result[i].reserve(group_size[i]);
    }
    for (int i = 0; i < _n; i++) {
      result[leader_buf[i]].push_back(i);
    }
    result.erase(
        std::remove_if(result.begin(), result.end(),
                       [&](const std::vector<int> &v) { return v.empty(); }),
        result.end());
    return result;
  }

 private:
  int _n;
  std::vector<int> parent_or_size;
};

int N, K;
vs originC;
ll sumScore;  // 手元でのデバッグ用

int calcScore(vs &c, vvi &cons) {
  dsu uf(N * N);

  rep(i, (int)cons.size()) {
    int p1 = cons[i][0] * N + cons[i][1];
    int p2 = cons[i][2] * N + cons[i][3];
    uf.merge(p1, p2);
  }

  // コンピュータが存在する座標を全部入れて全探索
  vpii coms;
  rep(i, N) rep(j, N) if (c[i][j] != '0' && c[i][j] != 'x')
      coms.emplace_back(i, j);

  int ret = 0;
  rep(i, (int)coms.size()) rep(j, i) {
    auto c1 = coms[i];
    auto c2 = coms[j];
    if (uf.same(c1.first * N + c1.second, c2.first * N + c2.second)) {
      ret += (c[c1.first][c1.second] == c[c2.first][c2.second]) ? 1 : -1;
    }
  }
  return max(ret, 0);
}

vvi deletePair(vvi &cons, dsu &uf, vs &c, int threshold) {
  vvi ret;
  int Y = (int)cons.size();
  rep(i, Y) {
    int p1 = cons[i][0] * N + cons[i][1];
    if (uf.size(p1) >= threshold) {
      ret.push_back(cons[i]);
      continue;
    }
    // 間を'0'で埋める
    if (cons[i][0] == cons[i][2]) {
      int from = cons[i][1];
      int to = cons[i][3];
      if (to < from) swap(to, from);
      if (from - to == 1) continue;
      // 隣り合っていれば消すところはない
      for (int xi = from + 1; xi < to; xi++) {
        c[cons[i][0]][xi] = '0';
      }
    } else {
      int from = cons[i][0];
      int to = cons[i][2];
      if (to < from) swap(to, from);
      if (from - to == 1) continue;  // 隣り合っていれば消すところはない
      for (int yi = from + 1; yi < to; yi++) {
        c[yi][cons[i][1]] = '0';
      }
    }
    // ufから削除
    uf.divide(cons[i][0] * N + cons[i][1], cons[i][2] * N + cons[i][3]);
  }
  // uf = dsu(N * N);
  // rep(ci, (int)ret.size()) {
  //   int p1 = ret[ci][0] * N + ret[ci][1];
  //   int p2 = ret[ci][2] * N + ret[ci][3];
  //   uf.merge(p1, p2);
  // }

  return ret;
}

vi xs = {-1, 0, 0, 1};
vi ys = {0, -1, 1, 0};

// 移動：movesとconsを更新する（※Xのインクリメントは行わない）
void move(int y1, int x1, int y2, int x2, vvi &moves, vs &c) {
  c[y2][x2] = c[y1][x1];
  c[y1][x1] = '0';
  moves.push_back(vi(4));
  moves.back()[0] = y1;
  moves.back()[1] = x1;
  moves.back()[2] = y2;
  moves.back()[3] = x2;
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

vpii decideMove(dsu &uf, char ck, pii start, vs &c, int maxD, int &maxChange) {
  vpii changePiis;

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

    if (c[p.first][p.second] != 'x') {
      vi connects;
      rep(di, 4) {
        for (int i = 1; i < N; i++) {
          int y = p.first + ys[di] * i;
          int x = p.second + xs[di] * i;
          if (y < 0 || y == N || x < 0 || x == N) break;
          if (c[y][x] == '0') continue;
          if (c[y][x] == 'x') break;
          if (c[y][x] != ck) break;
          if (uf.same(y * N + x, start.first * N + start.second)) break;
          connects.push_back(y * N + x);
          break;
        }
      }
      int increaseSize = 0;
      int sumSize = 0;
      rep(i, (int)connects.size()) {
        bool sameFlag = false;
        rep(j, i) if (uf.same(connects[i], connects[j])) sameFlag = true;
        if (!sameFlag) {
          int tmp = uf.size(connects[i]);
          sumSize += tmp;
          increaseSize -= tmp * (tmp - 1);
        }
      }
      increaseSize += (1 + sumSize) * sumSize;

      if (chmax(maxChange, increaseSize)) {
        changePiis = piis;
      }
    }

    if ((int)piis.size() < maxD) {
      rep(di, 4) {
        int y = p.first + ys[di];
        int x = p.second + xs[di];
        if (y < 0 || y == N || x < 0 || x == N) continue;
        if (maxD <= 12) {
          if (c[y][x] != '0') continue;
        } else {
          if (c[y][x] != '0' && c[y][x] != 'x') continue;
        }
        auto yx = make_pair(y, x);
        if (!visited.count(yx)) q.emplace(yx, piis);
      }
    }
  }
  return changePiis;
}

void annealing(double endTime, vvi &nowMoves, vvi &nowCons, vs &nowC,
               int nowMaxD, vector<vpii> points, vi &ks, dsu &uf, vi &pattern) {
  // 時間管理用
  auto startClock = system_clock::now();
  double time = 0.0;

  vector<int> cntY(K);  // 数字ごとの接続本数
  int X = 0;
  int Y = 0;

  bool resetFlag = false;
  bool is1stLap = true;
  bool isChange = false;
  int FOR_CNT_Y = -1;
  if (pattern[1] == 1) FOR_CNT_Y = 5;
  if (pattern[1] == 2) FOR_CNT_Y = 10;

  while (true) {
    isChange = false;

    // 時間更新
    time =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);
    for (int ki : ks) {
      rep(kii, 2) {
        rep(pi, 100) {
          if (time > endTime || X + Y >= K * 100) {
            return;
          }

          // ここまで組が小さいものはあまり寄与してないので削除する
          if (!resetFlag && X + Y >= K * 20) {
            if (pattern[0] == 1) nowCons = deletePair(nowCons, uf, nowC, 3);
            if (pattern[0] == 2) nowCons = deletePair(nowCons, uf, nowC, 4);
            Y = (int)nowCons.size();
            resetFlag = true;
          }

          char ck = (char)('0' + ki + 1);
          // points[ki][pi]を動かす
          // 幅優先探索して、動かすか決める
          int nowD = min(nowMaxD, K * 100 - X - Y);
          if (uf.size(points[ki][pi].first * N + points[ki][pi].second) != 1) {
            // どこかと繋がっているので動かしてはいけない（動かさずに繋ぐのはOK）
            nowD = 0;
          }
          if (is1stLap && cntY[ki] <= FOR_CNT_Y)
            nowD = 0;  // 最初の周は動かさない

          int maxChange = 0;
          vpii changePiis =
              decideMove(uf, ck, points[ki][pi], nowC, nowD, maxChange);

          if (maxChange == 0) continue;
          // アドホック：どうせ余るので、効率の悪い接続はしないでおく

          isChange = true;
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
            nowC[points[ki][pi].first][points[ki][pi].second] = '0';
            points[ki][pi].first = nowMoves.back()[2];
            points[ki][pi].second = nowMoves.back()[3];
            nowC[points[ki][pi].first][points[ki][pi].second] = ck;
          }

          // どこと接続するか思い出す
          rep(di, 4) {
            if (X + Y >= K * 100) break;
            for (int k = 1; k < N; k++) {
              int y1 = points[ki][pi].first;
              int x1 = points[ki][pi].second;
              int y = y1 + ys[di] * k;
              int x = x1 + xs[di] * k;
              if (y < 0 || y == N || x < 0 || x == N) break;
              if (nowC[y][x] == '0') continue;
              if (nowC[y][x] != ck || nowC[y][x] == 'x') break;

              if (uf.same(y1 * N + x1, y * N + x)) {
                break;  // 既に繋がってるなら繋げない
              }
              uf.merge(y1 * N + x1, y * N + x);
              Y++;
              cntY[ki]++;
              connect(y1, x1, y, x, nowCons, nowC);
              break;
            }
          }
        }
      }
    }
    if (!isChange) {
      // debug("no change", nowMaxD, time, cnt, X + Y);
      return;
    }
    if (nowMaxD < 13) nowMaxD++;
    is1stLap = false;
  }
}

void tryhub(vvi &cons, vs &c, vvi &moves, vvb &isHub, dsu &uf, int threshold) {
  int X = (int)moves.size();
  int Y = (int)cons.size();

  rep(ri, 100) {
    if (X + Y >= K * 100 - 1) return;
    int mxScore = 0;
    int mxType = 0;
    int mxi = 0, mxj = 0;
    vi mxMoveCandidate;
    char mxMxChar = 'z';
    map<char, vpii> mxMp;

    rep(i, N) rep(j, N) {
      if (c[i][j] == '0' || c[i][j] == 'x') continue;
      // とりあえず他とくっついてるやつは入れない
      if (uf.size(i * N + j) != 1) continue;

      // 隣接しているコンピュータを列挙
      map<char, vpii> mp;
      vc direct(4, 'z');
      vpii directP(4);
      char ck = c[i][j];
      rep(di, 4) {
        for (int k = 1; k < N; k++) {
          int y = i + ys[di] * k;
          int x = j + xs[di] * k;
          if (y < 0 || y == N || x < 0 || x == N) break;
          if (c[y][x] == '0') continue;
          if (c[y][x] == ck || c[y][x] == 'x') break;
          if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
          pii yx = make_pair(y, x);
          mp[c[y][x]].push_back(yx);
          direct[di] = c[y][x];
          directP[di] = yx;
          break;
        }
      }
      // 移動考慮
      // 伸びるスコアと必要な操作(score, 移動先yx, 繋げる座標1, 繋げる座標2)
      vi moveCandidate(7);

      rep(di, 4) {
        int y = i + ys[di];
        int x = j + xs[di];
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] != '0') continue;
        if (di == 0 || di == 3) {
          if (direct[1] == direct[2] && direct[1] != 'z') {
            // 横方向に移動すると改善
            int p1 = directP[1].first * N + directP[1].second;
            int p2 = directP[2].first * N + directP[2].second;
            if (uf.same(p1, p2)) continue;
            int sz1 = uf.size(p1);
            int sz2 = uf.size(p2);
            int addScore = (sz1 + sz2) * (sz1 + sz2 - 1) - sz1 * (sz1 - 1) -
                           sz2 * (sz2 - 1);

            if (moveCandidate[0] > addScore) continue;
            moveCandidate[0] = addScore;
            moveCandidate[1] = y;
            moveCandidate[2] = x;
            moveCandidate[3] = directP[1].first;
            moveCandidate[4] = directP[1].second;
            moveCandidate[5] = directP[2].first;
            moveCandidate[6] = directP[2].second;
          }
        } else {
          if (direct[0] == direct[3] && direct[0] != 'z') {
            // 縦方向に移動すると改善
            int p1 = directP[0].first * N + directP[0].second;
            int p2 = directP[3].first * N + directP[3].second;
            if (uf.same(p1, p2)) continue;
            int sz1 = uf.size(p1);
            int sz2 = uf.size(p2);
            int addScore = (sz1 + sz2) * (sz1 + sz2 - 1) - sz1 * (sz1 - 1) -
                           sz2 * (sz2 - 1);
            if (moveCandidate[0] > addScore) continue;
            moveCandidate[0] = addScore;
            moveCandidate[1] = y;
            moveCandidate[2] = x;
            moveCandidate[3] = directP[0].first;
            moveCandidate[4] = directP[0].second;
            moveCandidate[5] = directP[3].first;
            moveCandidate[6] = directP[3].second;
          }
        }
      }

      // どの数字のハブになるのが最善か
      int mx = 0;
      char mxChar = 'z';
      for (auto p : mp) {
        int sz = (int)p.second.size();
        if (sz <= 1) continue;

        vi sizes;
        int num = 0;

        rep(a, sz) {
          bool sameFlag = false;
          int p1 = p.second[a].first * N + p.second[a].second;
          rep(b, a) {
            int p2 = p.second[b].first * N + p.second[b].second;
            if (uf.same(p1, p2)) {
              // 既に同じ島なら繋げる意味ない
              sameFlag = true;
              break;
            }
          }
          if (sameFlag) continue;
          sizes.push_back(uf.size(p1));
          num++;
          if (X + Y + num >= K * 100) break;
        }
        if (num <= 1) continue;  // ハブにならない
        int addScore = 0;
        int sum = 0;
        for (auto v : sizes) {
          addScore -= v * (v - 1);
          sum += v;
        }
        addScore += sum * (sum - 1);
        addScore -= sum;  // ハブのペナルティ
        if (chmax(mx, addScore)) mxChar = p.first;
      }

      if (moveCandidate[0] >= mx && moveCandidate[0] > threshold) {
        if (chmax(mxScore, moveCandidate[0])) {
          mxType = 1;
          mxMoveCandidate = moveCandidate;
          mxi = i;
          mxj = j;
        }
      } else if (mx > threshold) {
        if (chmax(mxScore, mx)) {
          mxType = 2;
          mxMxChar = mxChar;
          mxMp = mp;
          mxi = i;
          mxj = j;
        }
      }
    }

    if (mxType == 1) {
      // 移動して繋ぐ
      X++;
      move(mxi, mxj, mxMoveCandidate[1], mxMoveCandidate[2], moves, c);
      Y++;
      uf.merge(mxMoveCandidate[3] * N + mxMoveCandidate[4],
               mxMoveCandidate[5] * N + mxMoveCandidate[6]);
      connect(mxMoveCandidate[3], mxMoveCandidate[4], mxMoveCandidate[5],
              mxMoveCandidate[6], cons, c);

    } else if (mxType == 2) {
      isHub[mxi][mxj] = true;
      // mp[mxChar]のハブにする
      vpii ps = mxMp[mxMxChar];
      // psをsize順にソートする
      vector<pair<int, pii>> ps2;
      rep(psi, (int)ps.size()) ps2.emplace_back(
          uf.size(ps[psi].first * N + ps[psi].second), ps[psi]);
      sort(ps2.rbegin(), ps2.rend());

      rep(psi, (int)ps.size()) {
        if (uf.same(mxi * N + mxj,
                    ps2[psi].second.first * N + ps2[psi].second.second))
          continue;
        Y++;
        uf.merge(mxi * N + mxj,
                 ps2[psi].second.first * N + ps2[psi].second.second);
        connect(mxi, mxj, ps2[psi].second.first, ps2[psi].second.second, cons,
                c);
        if (X + Y >= K * 100) return;
      }
    }
  }
}

void finishingPair(vvi &cons, vs &c, int X, vvb &isHub, dsu &uf) {
  int Y = (int)cons.size();

  while (true) {
    if (X + Y >= K * 100) return;
    int changeScore = 0;
    int mxi = 0, mxj = 0;

    rep(i, N) rep(j, N) {
      if (c[i][j] == '0' || c[i][j] == 'x') continue;
      if (isHub[i][j]) continue;
      char ck = c[i][j];

      int nowChangeScore = 0;
      int nowSize = 0;

      rep(di, 4) {
        for (int k = 1; k < N; k++) {
          int y = i + ys[di] * k;
          int x = j + xs[di] * k;
          if (y < 0 || y == N || x < 0 || x == N) break;
          if (c[y][x] == '0') continue;
          if (c[y][x] != ck || c[y][x] == 'x') break;
          if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
          if (uf.same(i * N + j, y * N + x))
            break;  // 既に繋がってるなら繋げない

          int tmp = uf.size(y * N + x);
          nowChangeScore += tmp * (tmp - 1);
          nowSize += tmp;
          break;
        }
      }
      int tmp = uf.size(i * N + j);
      nowChangeScore -= tmp * (tmp - 1);
      nowChangeScore += (nowSize + tmp) * (nowSize + tmp - 1);
      if (chmax(changeScore, nowChangeScore)) {
        mxi = i, mxj = j;
      }
      //
    }

    if (changeScore == 0) return;

    char ck = c[mxi][mxj];
    rep(di, 4) {
      for (int k = 1; k < N; k++) {
        int y = mxi + ys[di] * k;
        int x = mxj + xs[di] * k;
        if (y < 0 || y == N || x < 0 || x == N) break;
        if (c[y][x] == '0') continue;
        if (c[y][x] != ck || c[y][x] == 'x') break;
        if (isHub[y][x]) break;  // 既にハブになってるやつとは繋げたくない
        if (uf.same(mxi * N + mxj, y * N + x))
          break;  // 既に繋がってるなら繋げない
        uf.merge(mxi * N + mxj, y * N + x);
        Y++;
        connect(mxi, mxj, y, x, cons, c);
        if (X + Y >= K * 100) return;
        break;
      }
    }
  }
}

void tryCompression(vvi &moves, vvi &cons, vs &c, vvb &isHub, dsu &uf) {
  int X = (int)moves.size();
  int Y = (int)cons.size();

  auto compress = [&](int y1, int x1, int y2, int x2, int y3, int x3) {
    move(y1, x1, y2, x2, moves, c);
    connect(y2, x2, y3, x3, cons, c);
    uf.replace(y1 * N + x1, y2 * N + x2);
    uf.merge(y2 * N + x2, y3 * N + x3);
  };

  // 圧縮した方が幸せなら圧縮する
  rep(ci, (int)cons.size()) {
    vi mv = cons[ci];
    if (X + Y >= K * 100 - 1) return;
    char cmv = c[mv[0]][mv[1]];
    if (mv[0] == mv[2]) {
      if (abs(mv[3] - mv[1]) >= 2) {
        // 横方向
        // 右に動かす
        bool changeFlag = false;
        int mv13 = min(mv[1], mv[3]);
        bool possible = true;
        if (isHub[mv[0]][mv13]) possible = false;
        // 既に他と繋がっていたらダメ
        // 左
        if (mv13 != 0) {
          char cl = c[mv[0]][mv13 - 1];
          if (cl == cmv || cl == 'x') possible = false;
        }
        // 上
        if (mv[0] != 0) {
          char ct = c[mv[0] - 1][mv13];
          if (ct == cmv || ct == 'x') possible = false;
        }
        // 下
        if (mv[0] + 1 != N) {
          char cb = c[mv[0] + 1][mv13];
          if (cb == cmv || cb == 'x') possible = false;
        }
        // 動いた先で繋がれるなら動かす
        if (possible) {
          if ((mv[0] != 0 && c[mv[0] - 1][mv13 + 1]) == cmv &&
              !uf.same(mv[0] * N + (mv13 + 1), (mv[0] - 1) * N + (mv13 + 1))) {
            // 上に繋げる
            compress(mv[0], mv13, mv[0], mv13 + 1, mv[0] - 1, mv13 + 1);
            cons[ci][1] = mv13 + 1;
            cons[ci][3] = max(mv[1], mv[3]);
            // 真ん中の'x'埋めは済んでいるのでこれでよい
            changeFlag = true;
          } else if ((mv[0] + 1 != N && c[mv[0] + 1][mv13 + 1]) == cmv &&
                     !uf.same(mv[0] * N + mv13 + 1,
                              (mv[0] + 1) * N + (mv13 + 1))) {
            if (X + Y >= K * 100) return;
            // 下に繋げる
            compress(mv[0], mv13, mv[0], mv13 + 1, mv[0] + 1, mv13 + 1);
            cons[ci][1] = mv13 + 1;
            cons[ci][3] = max(mv[1], mv[3]);
            changeFlag = true;
          }
        }
        // 右に動かさなかった場合、左に動かす検討をする
        if (changeFlag) continue;
        possible = true;
        mv13 = max(mv[1], mv[3]);
        if (isHub[mv[0]][mv13]) possible = false;
        if (mv13 + 1 != N) {
          char cr = c[mv[0]][mv13 + 1];
          if (cr == cmv || cr == 'x') possible = false;
        }
        if (mv[0] != 0) {
          char ct = c[mv[0] - 1][mv13];
          if (ct == cmv || ct == 'x') possible = false;
        }
        if (mv[0] + 1 != N) {
          char cb = c[mv[0] + 1][mv13];
          if (cb == cmv || cb == 'x') possible = false;
        }
        // 動いた先で繋がれるなら動かす
        if (!possible) continue;
        if ((mv[0] != 0 && c[mv[0] - 1][mv13 - 1]) == cmv &&
            !uf.same(mv[0] * N + (mv13 - 1), (mv[0] - 1) * N + (mv13 - 1))) {
          // 上に繋げる
          compress(mv[0], mv13, mv[0], mv13 - 1, mv[0] - 1, mv13 - 1);
          cons[ci][1] = mv13 - 1;
          cons[ci][3] = min(mv[1], mv[3]);
        } else if ((mv[0] + 1 != N && c[mv[0] + 1][mv13 - 1]) == cmv &&
                   !uf.same(mv[0] * N + mv13 - 1,
                            (mv[0] + 1) * N + (mv13 - 1))) {
          if (X + Y >= K * 100) return;
          // 下に繋げる
          compress(mv[0], mv13, mv[0], mv13 - 1, mv[0] + 1, mv13 - 1);
          cons[ci][1] = mv13 - 1;
          cons[ci][3] = min(mv[1], mv[3]);
        }
      }
    } else {
      // 縦方向
      bool changeFlag = false;
      bool possible = true;
      if (abs(mv[0] - mv[2]) >= 2) {
        int mv02 = min(mv[0], mv[2]);
        // mv02を下に動かす
        if (isHub[mv02][mv[1]]) possible = false;
        // 既に他と繋がっていたらダメ
        // 上
        if (mv02 != 0) {
          char ct = c[mv02 - 1][mv[1]];
          if (ct == cmv || ct == 'x') possible = false;
        }
        // 左
        if (mv[1] != 0) {
          char cl = c[mv02][mv[1] - 1];
          if (cl == cmv || cl == 'x') possible = false;
        }
        // 右
        if (mv[1] + 1 != N) {
          char cr = c[mv02][mv[1] + 1];
          if (cr == cmv || cr == 'x') possible = false;
        }
        // 動いた先で繋がれるなら動かす
        if (possible) {
          if (mv[1] != 0 && c[mv02 + 1][mv[1] - 1] == cmv &&
              !uf.same((mv02 + 1) * N + mv[1], (mv02 + 1) * N + mv[1] - 1)) {
            // 左に繋げる
            compress(mv02, mv[1], mv02 + 1, mv[1], mv02 + 1, mv[1] - 1);
            cons[ci][0] = mv02 + 1;
            cons[ci][2] = max(mv[0], mv[2]);
            changeFlag = true;
          } else if (mv[1] + 1 != N && c[mv02 + 1][mv[1] + 1] == cmv &&
                     !uf.same((mv02 + 1) * N + mv[1],
                              (mv02 + 1) * N + mv[1] + 1)) {
            if (X + Y >= K * 100) return;
            // 右に繋げる
            compress(mv02, mv[1], mv02 + 1, mv[1], mv02 + 1, mv[1] + 1);
            cons[ci][0] = mv02 + 1;
            cons[ci][2] = max(mv[0], mv[2]);
            changeFlag = true;
          }
        }
        if (changeFlag) continue;
        // 上に動かす
        possible = true;
        mv02 = max(mv[0], mv[2]);
        if (isHub[mv02][mv[1]]) possible = false;
        if (mv02 + 1 != N) {
          char cb = c[mv02 + 1][mv[1]];
          if (cb == cmv || cb == 'x') possible = false;
        }
        // 左
        if (mv[1] != 0) {
          char cl = c[mv02][mv[1] - 1];
          if (cl == cmv || cl == 'x') possible = false;
        }
        // 右
        if (mv[1] + 1 != N) {
          char cr = c[mv02][mv[1] + 1];
          if (cr == cmv || cr == 'x') possible = false;
        }
        if (!possible) continue;
        // 動いた先で繋がれるなら動かす
        if (mv[1] != 0 && (c[mv02 - 1][mv[1] - 1]) == cmv &&
            !uf.same((mv02 - 1) * N + mv[1], (mv02 - 1) * N + mv[1] - 1)) {
          // 左に繋げる
          compress(mv02, mv[1], mv02 - 1, mv[1], mv02 - 1, mv[1] - 1);
          cons[ci][0] = mv02 - 1;
          cons[ci][2] = min(mv[0], mv[2]);
        } else if (mv[1] + 1 != N && c[mv02 - 1][mv[1] + 1] == cmv &&
                   !uf.same((mv02 - 1) * N + mv[1],
                            (mv02 - 1) * N + mv[1] + 1)) {
          if (X + Y >= K * 100) return;
          // 右に繋げる
          compress(mv02, mv[1], mv02 - 1, mv[1], mv02 - 1, mv[1] + 1);
          cons[ci][0] = mv02 - 1;
          cons[ci][2] = min(mv[0], mv[2]);
        }
      }
    }
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
    // 時間管理用
    auto startClock = system_clock::now();
    double elapsedTime = 0.0;
    /* input */
    cin >> N >> K;
    originC.resize(N);
    rep(i, N) cin >> originC[i];

    /* solve */
    vector<vpii> points(K);

    rep(i, N) rep(j, N) {
      if (originC[i][j] != '0') {
        points[originC[i][j] - '0' - 1].emplace_back(i, j);
      }
    }

    vvi bestMoves;
    vvi bestCons;
    int bestScore = 0;
    double time = 0.19;
    vi ds;
    rep(i, 3 * K) ds.push_back(8);
    rep(i, 3 * K) ds.push_back(10);
    rep(i, 3 * K) ds.push_back(6);
    rep(i, 3 * K) ds.push_back(4);
    rep(i, 3 * K) ds.push_back(12);
    rep(i, 3 * K) ds.push_back(2);
    rep(i, 3 * K) ds.push_back(5);
    int dsSz = (int)ds.size();
    vvi patterns(3 * dsSz, vi(3));
    rep(i, (int)patterns.size()) {
      if (i % 3 == 1) patterns[i][0] = 1;
      if (i % 3 == 2) patterns[i][0] = 2;
      if (i / dsSz == 1) patterns[i][1] = 1;
      if (i / dsSz == 2) patterns[i][1] = 2;
    }

    int cntLoop = 0;
    rep(i, dsSz * 3) {
      vvi moves;
      vvi cons;
      int i2 = i % dsSz;
      int nowMaxD = ds[i2];
      vs c = originC;

      cntLoop++;

      vi ks(K);  // 探索開始の数字のバリエーション
      rep(j, K) ks[j] = (j + i2) % K;
      dsu uf(N * N);
      annealing(time, moves, cons, c, nowMaxD, points, ks, uf, patterns[i]);

      vvb isHub(N, vb(N));
      // ペア削除
      cons = deletePair(cons, uf, c, 4);

      if ((int)moves.size() + (int)cons.size() <= K * 100 * 0.9) {
        tryCompression(moves, cons, c, isHub, uf);
      }

      // 繋げ直し
      tryhub(cons, c, moves, isHub, uf, 6);
      // 仕上げ
      int X = (int)moves.size();
      cons = deletePair(cons, uf, c, 4);
      finishingPair(cons, c, X, isHub, uf);

      int nowScore = calcScore(c, cons);
      if (chmax(bestScore, nowScore)) {
        bestMoves = moves;
        bestCons = cons;
      }

      // 2.8秒を超えたら終わり
      elapsedTime =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);
      if (elapsedTime > 2.90) break;
    }

    assert((int)bestMoves.size() + (int)bestCons.size() <= K * 100);

    // デバッグ用のスコア計算
    // printf("%d\n", bestScore);
    // debug(K, N, cntLoop);

    /* output */
    printOutput(bestMoves, bestCons);
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
    debug(ti);
  }

  // cout << sumScore << endl;
  return 0;
}