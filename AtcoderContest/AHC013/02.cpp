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

// class Point {
//  public:
//   int x, y;
//   Point(int x_, int y_) : x(x_), y(y_) {}
// };

struct Solver {
  void solve() {
    /* input */
    int N, K;
    cin >> N >> K;
    vs c(N);
    rep(i, N) cin >> c[i];

    /* solve */
    auto startClock = system_clock::now();
    vector<vpii> points(K);
    map<pii, int> invP;

    rep(i, N) rep(j, N) {
      if (c[i][j] != '0') {
        auto p = make_pair(i, j);
        points[c[i][j] - '0' - 1].push_back(p);
        int v = (c[i][j] - '0' - 1) * 100 +
                (int)points[c[i][j] - '0' - 1].size() - 1;
        invP[p] = v;
      }
    }

    dsu uf(K * 100);
    // 出力変数の宣言
    int X = 0;
    vvi moves;
    int Y = 0;
    vvi cons;
    // 回す
    int cnt = 0;
    const static double END_TIME = 2.0;  // 終了時間（秒）
    double time = 0.0;                   // 経過時間（秒）
    int nowMaxD = 1;
    do {
      // debug("do", X, Y);
      rep(ki, K) {
        rep(pi, 100) {
          char ck = (char)('0' + ki + 1);
          // points[ki][pi]を動かす
          int pidx = ki * 100 + pi;
          // debug(pidx, points[ki][pi], uf.size(pidx));
          if (uf.size(pidx) != 1) {
            // どこかと繋がっているので動かしてはいけない
            continue;
          }
          // 幅優先探索して、動かすか決める
          int maxD = min(nowMaxD, K * 100 - X - Y);
          int maxChange = 0;
          vpii changePiis;
          pii changeP;

          queue<pair<pii, vpii>> q;
          vpii emp;
          q.emplace(points[ki][pi], emp);
          while (!q.empty()) {
            auto piis = q.front().second;
            auto p = q.front().first;
            q.pop();
            piis.emplace_back(p);
            // 下側
            for (int i = 1; i < N; i++) {
              if (p.first + i == N) break;
              if (c[p.first + i][p.second] == '0') continue;
              if (c[p.first + i][p.second] == 'x') break;
              if (c[p.first + i][p.second] != ck) break;
              auto p2 = make_pair(p.first + i, p.second);
              if (p2 == points[ki][pi]) break;
              if (chmax(maxChange, uf.size(invP[p2]))) {
                changePiis = piis, changeP = p2;
              }
              break;
            }
            // 右側
            for (int i = 1; i < N; i++) {
              if (p.second + i == N) break;
              if (c[p.first][p.second + i] == '0') continue;
              if (c[p.first][p.second + i] == 'x') break;
              if (c[p.first][p.second + i] != ck) break;
              auto p2 = make_pair(p.first, p.second + i);
              if (p2 == points[ki][pi]) break;
              if (chmax(maxChange, uf.size(invP[p2]))) {
                changePiis = piis, changeP = p2;
              }
              break;
            }
            // 左側
            for (int i = 1; i < N; i++) {
              if (p.second - i == -1) break;
              if (c[p.first][p.second - i] == '0') continue;
              if (c[p.first][p.second - i] == 'x') break;
              if (c[p.first][p.second - i] != ck) break;
              auto p2 = make_pair(p.first, p.second - i);
              if (p2 == points[ki][pi]) break;
              if (chmax(maxChange, uf.size(invP[p2]))) {
                changePiis = piis, changeP = p2;
              }
              break;
            }
            // 上側
            for (int i = 1; i < N; i++) {
              if (p.first - i == -1) break;
              if (c[p.first - i][p.second] == '0') continue;
              if (c[p.first - i][p.second] == 'x') break;
              if (c[p.first - i][p.second] != ck) break;
              auto p2 = make_pair(p.first - i, p.second);
              if (p2 == points[ki][pi]) break;
              if (chmax(maxChange, uf.size(invP[p2]))) {
                changePiis = piis, changeP = p2;
              }
              break;
            }
            if ((int)piis.size() < maxD) {
              // 本当はxを超えて移動してもいいが複雑なので一旦これで
              if (p.first != 0 && c[p.first - 1][p.second] == '0') {
                q.emplace(make_pair(p.first - 1, p.second), piis);
              }
              if (p.first != N - 1 && c[p.first + 1][p.second] == '0') {
                q.emplace(make_pair(p.first + 1, p.second), piis);
              }
              if (p.second != 0 && c[p.first][p.second - 1] == '0') {
                q.emplace(make_pair(p.first, p.second - 1), piis);
              }
              if (p.second != N - 1 && c[p.first][p.second + 1] == '0') {
                q.emplace(make_pair(p.first, p.second + 1), piis);
              }
            }
          }
          // debug(pidx, maxChange, changePiis);
          //  1番いいところに移動して繋ぐ
          if (maxChange == 0) continue;
          if (changePiis.size() > 1) {
            rep(i, (int)changePiis.size() - 1) {
              moves.push_back(vi(4));
              moves.back()[0] = changePiis[i].first;
              moves.back()[1] = changePiis[i].second;
              moves.back()[2] = changePiis[i + 1].first;
              moves.back()[3] = changePiis[i + 1].second;
            }
            // debug(points[ki][pi], moves.back());
            X += (int)changePiis.size() - 1;

            // 座標の移動
            invP.erase(points[ki][pi]);
            c[points[ki][pi].first][points[ki][pi].second] = '0';
            points[ki][pi].first = moves.back()[2];
            points[ki][pi].second = moves.back()[3];
            invP[points[ki][pi]] = pidx;
            c[points[ki][pi].first][points[ki][pi].second] = ck;
          }

          Y++;
          cons.push_back(vi(4));
          cons.back()[0] = points[ki][pi].first;
          cons.back()[1] = points[ki][pi].second;
          cons.back()[2] = changeP.first;
          cons.back()[3] = changeP.second;
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
              c[y][i] = 'x';
            }
          } else {
            int from = points[ki][pi].first;
            int to = changeP.first;
            if (to < from) swap(to, from);
            if (from - to == 1) break;  // 隣り合っていれば消すところはない
            int x = points[ki][pi].second;
            for (int i = from + 1; i < to; i++) {
              c[i][x] = 'x';
            }
          }

          if (X + Y >= K * 100) break;
        }
        if (X + Y >= K * 100) break;
      }

      cnt++;
      nowMaxD++;
      // 時間更新
      time =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);

      break;
    } while (time < END_TIME);

    /* output */
    cout << X << "\n";
    rep(i, X) printf("%d %d %d %d\n", moves[i][0], moves[i][1], moves[i][2],
                     moves[i][3]);
    cout << Y << "\n";
    rep(i, Y)
        printf("%d %d %d %d\n", cons[i][0], cons[i][1], cons[i][2], cons[i][3]);

    debug(nowMaxD, time);
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