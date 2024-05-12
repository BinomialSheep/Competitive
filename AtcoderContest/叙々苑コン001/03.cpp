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

// 焼きなまし法の参考にしたページ
// https://shindannin.hatenadiary.com/entry/2021/03/06/115415

// 0以上UINT_MAX(0xffffffff)以下の整数をとる乱数 xorshift
// https://ja.wikipedia.org/wiki/Xorshift
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

// 0以上1未満の小数をとる乱数
static double rand01() { return (randXor() + 0.5) * (1.0 / UINT_MAX); }

struct Solver {
  int N, M;
  vi a, b;
  // α
  const int A = 5;
  const int MAP_SIZE = 1000;

  // ワーシャルフロイドで求めた各惑星間の最短コスト
  vvl G;

  // 解説の「貪欲による解法2」を採用
  // https://yukicoder.me/problems/no/5007/editorial
  vi terryInit(vpii &cd) {
    const ll INF = 1e18;
    G.resize(N);
    rep(i, N) rep(j, N) G[i].push_back(INF);

    auto calDist = [](int x1, int y1, int x2, int y2) {
      return (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };

    rep(i, N) rep(j, i) {
      G[i][j] = G[j][i] = A * A * calDist(a[i], b[i], a[j], b[j]);
    }
    vvl dirctG = G;

    auto floyd = [&] {
      rep(i, N) G[i][i] = 0;
      rep(k, N) rep(i, N) {
        if (G[i][k] == INF) continue;
        rep(j, N) {
          if (G[k][j] == INF) continue;
          chmin(G[i][j], G[i][k] + G[k][j]);
        }
      }
    };
    floyd();
    vi ret;

    // 経路復元できるダイクストラ
    auto dijkstra = [&](int now, int nexV) {
      vl dist(N, INFTY);
      vi prev(N, -1);
      priority_queue<pii, vpii, greater<pii>> pq;
      pq.emplace(0, now);
      dist[now] = 0;
      while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int from = p.second;
        if (dist[from] < p.first) continue;
        rep(to, N) {
          if (chmin(dist[to], dist[from] + dirctG[from][to])) {
            prev[to] = from;
            pq.emplace(dist[to], to);
          }
        }
      }

      // 経路復元する
      int current = nexV;
      stack<int> nowToNexRev;
      while (current != now) {
        nowToNexRev.push(current + 1);
        current = prev[current];
      }
      while (!nowToNexRev.empty()) {
        ret.push_back(nowToNexRev.top());
        nowToNexRev.pop();
      }
    };

    vi color(N);
    int now = 0;
    color[0] = 1;
    ret.push_back(1);

    rep(i, N - 1) {
      // 未訪問で1番近い頂点を見つける
      ll nexD = INF;
      int nexV = -1;
      rep(j, N) {
        if (color[j]) continue;
        if (chmin(nexD, G[now][j])) nexV = j;
      }
      // ダイクストラして経路復元
      dijkstra(now, nexV);
      //
      now = nexV;
      color[nexV] = 1;
    }
    // 最終地点から1までもダイクストラ
    dijkstra(now, 0);

    return ret;
  }

  // 宇宙ステーションの初期配置
  vpii initStation() {
    vpii ret;
    ret.emplace_back(800, 500);
    ret.emplace_back(200, 500);
    ret.emplace_back(500, 800);
    ret.emplace_back(500, 200);
    ret.emplace_back(600, 600);
    ret.emplace_back(600, 400);
    ret.emplace_back(400, 600);
    ret.emplace_back(400, 400);
    return ret;
  }

  // シンプルなスコア計算
  ll calcScore(vpii &tr) {
    ll ret = 0;
    int len = (int)tr.size();

    auto dist = [](int x1, int y1, int x2, int y2) {
      return (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };

    rep(i, len - 1) {
      if (tr[i].first == 1 && tr[i + 1].first == 1) {
        int x1 = a[tr[i].second - 1];
        int y1 = b[tr[i].second - 1];
        int x2 = a[tr[i + 1].second - 1];
        int y2 = b[tr[i + 1].second - 1];
        ret += A * A * dist(x1, y1, x2, y2);
      } else if (tr[i].first == 2 && tr[i + 1].first == 2) {
        // TODO
      } else {
        // TODO
      }
    }
    return ret;
  }

  //
  ll calcDist(int prev, int next, vpii &cd) {
    --prev, --next;
    if (prev < N && next < N) {
      return G[prev][next];
    }
    auto dist = [](int x1, int y1, int x2, int y2) {
      return (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };
    int x1 = prev < N ? a[prev] : cd[prev - N].first;
    int y1 = prev < N ? b[prev] : cd[prev - N].second;
    int x2 = next < N ? a[next] : cd[next - N].first;
    int y2 = next < N ? b[next] : cd[next - N].second;
    ll ret = dist(x1, y1, x2, y2);
    if (prev < N) ret *= 5;
    if (next < N) ret *= 5;
    return ret;
  }

  void solve() {
    /* 時間計測 */
    auto startClock = system_clock::now();
    /* input */
    cin >> N >> M;
    a.resize(N);
    b.resize(N);
    rep(i, N) cin >> a[i] >> b[i];

    /* solve */
    // 初期設定
    vpii cd = initStation();
    // 解説の「貪欲法による解法（その2）」を再現
    // ワーフロして経路復元ダイクストラ
    vi tr = terryInit(cd);

    // debug(calcScore(tr));
    // auto maxScore = calcScore(tr);

    /* 焼きなまし法 */
    const static double START_TEMP = 1500;  // 開始時の温度
    const static double END_TEMP = 100;     // 終了時の温度
    const static double END_TIME = 0.9;     // 終了時間（秒）
    double time = 0.0;                      // 経過時間（秒）

    // ループ回数のデバッグ用
    ll cnt = 0;
    ll currentScore = 1e18;
    do {
      cnt++;
      // 進捗。開始時が0.0で、終了時が1.0
      const double progressRatio = time / END_TIME;
      const double temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;

      /* 近傍3：ステーションの移動 */
      int stationId = N + randXor() % M + 1;
      // 暫定解からステーションを削除
      vi tmpTr;
      rep(i, (int)tr.size()) if (tr[i] != stationId) tmpTr.push_back(tr[i]);
      // ステーションを移動（移動範囲も徐々に小さくしてる！）
      pii oldP = cd[stationId - N - 1];
      pii newP = oldP;
      const double MAX_DELTA = 400;
      const double MIN_DELTA = 10;
      int d = (MAX_DELTA * (1.0 - time) + MIN_DELTA * time);
      int mx = min(MAP_SIZE, newP.first + d);
      int mn = max(0, newP.first - d);
      newP.first = mn + randXor() % (mx - mn);
      mx = min(MAP_SIZE, newP.second + d);
      mn = max(0, newP.second - d);
      newP.second = mn + randXor() % (mx - mn);
      cd[stationId - N - 1] = newP;
      // 各辺でステーションを使うかgreedyに判定
      vi newTr;
      ll newScore = 0;
      rep(i, (int)tmpTr.size() - 1) {
        newTr.push_back(tmpTr[i]);
        ll oldDist = calcDist(tmpTr[i], tmpTr[i + 1], cd);
        ll newDist = calcDist(tmpTr[i], stationId, cd) +
                     calcDist(stationId, tmpTr[i + 1], cd);
        if (newDist < oldDist) {
          newScore += newDist;
          newTr.push_back(stationId);
        } else {
          newScore += oldDist;
        }
      }
      newTr.push_back(tmpTr.back());

      // 解の更新
      ll deltaScore = currentScore - newScore;
      // const double probability = exp(deltaScore / temp);
      if (deltaScore >= 0) {
        currentScore = newScore;
        tr.resize(newTr.size());
        tr = newTr;
      } else {
        cd[stationId - N - 1] = oldP;
      }

      /* 近傍3ここまで */

      // 時間更新
      time =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);

    } while (time < END_TIME);

    /* output */
    debug(cnt);
    int V = (int)tr.size();
    assert(tr[0] == 1);
    assert(tr[V - 1] == 1);

    rep(i, M) cout << cd[i].first << " " << cd[i].second << "\n";

    cout << V << endl;
    rep(i, V) {
      if (tr[i] <= N) {
        cout << "1 " << tr[i] << "\n";
      } else {
        cout << "2 " << tr[i] - N << "\n";
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