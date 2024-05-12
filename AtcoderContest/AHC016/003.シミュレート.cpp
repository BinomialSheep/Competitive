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

struct Solver {
  void best(int N, int M, double eps) {
    cout << N << endl;
    int sz = N * (N - 1) / 2;

    vi sizeList;
    for (int i = 0; i <= sz; i += sz / (M - 1)) {
      sizeList.push_back(i);
      if ((int)sizeList.size() == M) break;
    }
    while ((int)sizeList.size() < M) sizeList.push_back(0);
    while ((int)sizeList.size() > M) sizeList.pop_back();
    assert((int)sizeList.size() == M);

    vs G(M);
    rep(i, M) {
      int v = sizeList[i];
      rep(j, v) G[i].push_back('1');
      rep(j, sz - v) G[i].push_back('0');
      assert((int)G[i].size() == sz);
      cout << G[i] << "\n";
      // debug(str.size());
    }
    cout << flush;
    /* interactive */
    rep(qi, 100) {
      string S;
      cin >> S;
      int cnt = 0;
      string H = S;
      // 実験の場合
      H = G[stoi(S)];
      rep(i, (int)H.size()) {
        if (randXor() % 100 < eps * 100) {
          H[i] = (H[i] == '0' ? '1' : '0');
        }
      }
      // ここまで
      for (auto c : H)
        if (c == '1') cnt++;
      //
      int ans = 0;
      int diff = INFTY;
      rep(i, sizeList.size()) {
        if (chmin(diff, abs(sizeList[i] - cnt))) ans = i;
      }
      // デバッグ用
      int realCnt = 0;
      for (auto c : G[stoi(S)])
        if (c == '1') realCnt++;
      debug(cnt, ans, realCnt, S);

      cout << ans << endl;
    }
  }

  void solve() {
    /* input */
    int M;
    double eps;
    cin >> M >> eps;

    /* solve */
    int bestN = 10;
    int bestScore = 0;

    rep(ni, 97) {
      int N = 4 + ni;
      int sz = N * (N - 1) / 2;
      vi sizeList;
      for (int i = 0; i <= sz; i += sz / (M - 1)) {
        sizeList.push_back(i);
        if ((int)sizeList.size() == M) break;
      }
      while ((int)sizeList.size() < M) sizeList.push_back(0);
      while ((int)sizeList.size() > M) sizeList.pop_back();
      assert((int)sizeList.size() == M);
      vs G(M);
      rep(i, M) {
        int v = sizeList[i];
        rep(j, v) G[i].push_back('1');
        rep(j, sz - v) G[i].push_back('0');
        assert((int)G[i].size() == sz);
        // cout << G[i] << "\n";
        //  debug(str.size());
      }
      int correct = 0;
      rep(qi, 3000) {
        int cnt = 0;
        int idx = qi % M;
        string H = G[idx];
        rep(i, (int)H.size()) {
          if (randXor() % 100 < eps * 100) {
            H[i] = (H[i] == '0' ? '1' : '0');
          }
        }
        for (auto c : H)
          if (c == '1') cnt++;
        //
        int ans = -1;
        int diff = INFTY;
        rep(i, sizeList.size()) {
          if (chmin(diff, abs(sizeList[i] - cnt))) ans = i;
        }
        // debug(cnt, ans);

        // cout << ans << endl;
        if (ans == idx) correct++;
      }
      double score = 1e9;
      rep(i, 100 - correct) score *= 0.9;
      score /= N;
      debug(N, (int)score, correct);
      if (chmax(bestScore, (int)score)) bestN = N;
    }
    debug(bestN);

    best(bestN, M, eps);

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