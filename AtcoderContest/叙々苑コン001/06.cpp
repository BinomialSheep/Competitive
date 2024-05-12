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
  vpii cd;
  // α
  const int A = 5;
  const int MAP_SIZE = 1000;

  // ワーシャルフロイドで求めた各惑星間の最短コスト
  vvl G;

  // 解説の「貪欲による解法2」を採用
  // https://yukicoder.me/problems/no/5007/editorial
  vi terryInit() {
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
    ret.emplace_back(300, 300);
    ret.emplace_back(300, 500);
    ret.emplace_back(300, 700);
    ret.emplace_back(500, 300);
    ret.emplace_back(500, 700);
    ret.emplace_back(700, 300);
    ret.emplace_back(700, 500);
    ret.emplace_back(700, 700);
    return ret;
  }

  ll calcDist(int prev, int next) {
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

  ll annealing(double endTime, vi &tr, ll currentScore) {
    /* 焼きなまし法 */
    auto startClock = system_clock::now();
    const static double START_TEMP = 1e4;    // 開始時の温度
    const static double END_TEMP = 10;       // 終了時の温度
    const static double END_TIME = endTime;  // 終了時間（秒）
    double time = 0.0;                       // 経過時間（秒）

    // ループ回数のデバッグ用
    ll cnt = 0;
    do {
      // デバッグ用
      cnt++;
      // if (cnt == 30) break;
      //    進捗。開始時が0.0で、終了時が1.0
      const double progressRatio = time / END_TIME;
      const double temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;

      // 近傍の割合
      int neighType = randXor() % 10;

      if (neighType < 2) {
        /* 近傍1：ステーションを適当な位置に挿入 */
        int stationId = N + randXor() % M + 1;
        // 最初と最後は1固定なので最初や最後には入れない
        int idx = 1 + randXor() % ((int)tr.size() - 1);
        int prev = tr[idx - 1];
        int next = tr[idx];
        ll oldScore = calcDist(prev, next);
        ll newScore = calcDist(prev, stationId) + calcDist(stationId, next);
        // 解の更新
        ll deltaScore = oldScore - newScore;
        const double probability = exp((double)deltaScore / temp);
        if (probability >= rand01()) {
          currentScore -= deltaScore;
          // 挿入する
          tr.insert(tr.begin() + idx, stationId);
        }
      } else if (neighType < 4) {
        /* 近傍2：適当な位置のステーションを削除 */
        int len = (int)tr.size();
        // ステーションを探す（適当に上限を10としている）
        int idx = 0;
        int trial = 0;
        while (tr[idx] <= N && trial < 10) {
          idx = randXor() % len;
          trial++;
        }
        if (tr[idx] <= N) continue;
        // ステーションを指すidxが見つかった場合
        int stationId = tr[idx];
        int prev = tr[idx - 1];
        int next = tr[idx + 1];
        ll oldScore = calcDist(prev, stationId) + calcDist(stationId, next);
        ll newScore = calcDist(prev, next);
        // 解の更新
        ll deltaScore = oldScore - newScore;
        const double probability = exp((double)deltaScore / temp);
        if (probability >= rand01()) {
          currentScore -= deltaScore;
          // 挿入する
          tr.erase(tr.begin() + idx);
        }
      } else if (neighType < 5) {
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
        int d = (int)(MAX_DELTA * (endTime - time) + MIN_DELTA * time);
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
          ll oldDist = calcDist(tmpTr[i], tmpTr[i + 1]);
          ll newDist =
              calcDist(tmpTr[i], stationId) + calcDist(stationId, tmpTr[i + 1]);
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
        const double probability = exp((double)deltaScore / temp);
        if (probability >= rand01()) {
          currentScore = newScore;
          tr.resize(newTr.size());
          tr = newTr;
        } else {
          cd[stationId - N - 1] = oldP;
        }
      } else {
        /* 近傍4：2-opt */
        // 最初と最後は1固定なので入れ替えない
        int l = (int)tr.size();
        int from = 1 + randXor() % (l - 2);
        int to = 1 + randXor() % (l - 2);
        if (from == to) {
          to += 1;
          if (to == l - 1) to = 2;
        }
        if (from > to) swap(from, to);
        int i0 = tr[from - 1];
        int i1 = tr[from];
        int i2 = tr[to - 1];
        int i3 = tr[to];
        ll d0123 = calcDist(i0, i1) + calcDist(i2, i3);
        ll d0213 = calcDist(i0, i2) + calcDist(i3, i1);
        ll newScore = currentScore + d0213 - d0123;
        // 解の更新
        ll deltaScore = currentScore - newScore;
        const double probability = exp((double)deltaScore / temp);
        if (probability >= rand01()) {
          currentScore = newScore;
          // 繋ぎ直す
          reverse(tr.begin() + from, tr.begin() + to);
        }
      }

      // trを綺麗にする
      // if (cnt % 1000) {
      //   vi cleanTr;
      //   cleanTr.push_back(tr[0]);
      //   rep(i, (int)tr.size() - 1) {
      //     if (tr[i + 1] != cleanTr.back()) cleanTr.push_back(tr[i + 1]);
      //   }
      //   tr.resize((int)cleanTr.size());
      //   tr = cleanTr;
      // }

      // 時間更新
      time =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);
    } while (time < END_TIME);

    // 戻り値
    return currentScore;
  }

  void solve() {
    /* input */
    cin >> N >> M;
    a.resize(N);
    b.resize(N);
    rep(i, N) cin >> a[i] >> b[i];

    /* solve */
    // 解説の「貪欲法による解法（その2）」を再現
    // ワーフロして経路復元ダイクストラ
    vi initTr = terryInit();

    // debug(calcScore(tr));
    // auto maxScore = calcScore(tr);
    ll currentScore = 0;
    rep(i, (int)initTr.size() - 1) currentScore +=
        calcDist(initTr[i], initTr[i + 1]);

    ll bestScore = currentScore;
    vi bestTr;
    vpii bestCd;
    // 3回焼きなます
    cd = initStation();
    rep(i, 4) {
      vi thisTr = initTr;
      ll thisScore = annealing(0.24, thisTr, currentScore);
      if (chmin(bestScore, thisScore)) {
        bestTr = thisTr;
        bestCd = cd;
      }
    }

    /* output */
    int V = (int)bestTr.size();
    assert(bestTr[0] == 1);
    assert(bestTr[V - 1] == 1);

    rep(i, M) cout << bestCd[i].first << " " << bestCd[i].second << "\n";

    cout << V << endl;
    rep(i, V) {
      if (bestTr[i] <= N) {
        cout << "1 " << bestTr[i] << "\n";
      } else {
        cout << "2 " << bestTr[i] - N << "\n";
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