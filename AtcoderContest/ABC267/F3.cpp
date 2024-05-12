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
    /* input */
    int N;
    cin >> N;
    vvi G(N);
    rep(i, N - 1) {
      int A, B;
      cin >> A >> B;
      --A, --B;
      G[A].push_back(B);
      G[B].push_back(A);
    }

    /* solve */

    /* 木の直径を求める */
    auto dfs = [&](auto f, int v, int d = 0, int p = -1) -> pii {
      pii ret = {d, v};
      for (auto u : G[v]) {
        if (u != p) {
          chmax(ret, f(f, u, d + 1, v));
        }
      }
      return ret;
    };
    // 木の直径の端点a, bと直径diameter
    int a = dfs(dfs, 0).second;
    auto [diameter, b] = dfs(dfs, a);
    debug(a, b, diameter);

    /* ダブリングする */
    // どこまでの2^kが必要か
    int logK = 1;
    while ((1LL << logK) <= diameter) logK++;
    debug(diameter, logK);
    // doublingA[k][i] := i番目から2^k個、Aに向かって進んだ地点
    vvi doublingA(logK, vi(N, -1));
    vvi doublingB(logK, vi(N, -1));
    // 1個進んだ地点（つまり親）を入れる
    auto dfs2 = [&](auto f, vvi &doubling, int v, int p = -1) -> void {
      for (auto u : G[v]) {
        if (u == p) {
          doubling[0][v] = u;
        } else {
          f(f, doubling, u, v);
        }
      }
    };
    dfs2(dfs2, doublingA, a);
    dfs2(dfs2, doublingB, b);
    // debug(doublingA);
    // debug(doublingB);
    rep(k, logK - 1) {
      rep(i, N) {
        if (doublingA[k][i] != -1) {
          doublingA[k + 1][i] = doublingA[k][doublingA[k][i]];
        }
        if (doublingB[k][i] != -1) {
          doublingB[k + 1][i] = doublingB[k][doublingB[k][i]];
        }
      }
    }
    // debug(doublingA);
    // debug(doublingB);
    //  クエリに答える
    int Q;
    cin >> Q;
    rep(qi, Q) {
      int U, K;
      cin >> U >> K;
      --U;

      int nowA = U, nowB = U;
      for (int ki = 0, K2 = K; K2 > 0; ki++) {
        // debug(ki, nowA, nowB);
        if (ki >= logK) {
          // そんなに遠くまで行けない
          nowA = nowB = -1;
          break;
        }
        if ((K2 & 1) && nowA != -1) nowA = doublingA[ki][nowA];
        if ((K2 & 1) && nowB != -1) nowB = doublingB[ki][nowB];
        K2 = K2 >> 1;
      }

      if (nowA >= 0) nowA++;
      if (nowB >= 0) nowB++;
      cout << max(nowA, nowB) << "\n";
    }

    /* output */
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