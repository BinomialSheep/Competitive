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

struct Solver {
  int N;
  vector<int> dy = {-1, 0, 0, 1};
  vector<int> dx = {0, 1, -1, 0};
  ll recursiveGirl(int y, int x, set<pair<int, int>> &visited) {
    if (y == N && x == N) return 1;

    ll ret = 0;
    rep(i, 4) {
      int y2 = y + dy[i];
      int x2 = x + dx[i];
      if (y2 < 0 || N < y2 || x2 < 0 || N < x2) continue;
      pair<int, int> p = make_pair(y2, x2);
      if (visited.count(p)) continue;
      visited.insert(p);
      ret += recursiveGirl(y2, x2, visited);
      visited.erase(p);
    }
    return ret;
  }

  ll recursiveGirl2(int y, int x, unordered_set<int> &visited) {
    if (y == N && x == N) return 1;

    ll ret = 0;
    rep(i, 4) {
      int y2 = y + dy[i];
      int x2 = x + dx[i];
      if (y2 < 0 || N < y2 || x2 < 0 || N < x2) continue;
      int key = y2 * 100 + x2;
      if (visited.count(key)) continue;
      visited.insert(key);
      ret += recursiveGirl2(y2, x2, visited);
      visited.erase(key);
    }
    return ret;
  }

  using bset = bitset<300>;
  ll memoRecursiveGirl(int y, int x, map<pair<int, string>, ll> &memo,
                       bset &visited) {
    if (y == N && x == N) return 1;

    ll ret = 0;
    rep(i, 4) {
      int y2 = y + dy[i];
      int x2 = x + dx[i];
      if (y2 < 0 || N < y2 || x2 < 0 || N < x2) continue;
      int key = y2 * (N * N) + x2;
      if (visited[key]) continue;
      visited[key] = 1;
      auto pair = make_pair(key, visited.to_string());
      if (memo.count(pair)) {
        ret += memo[pair];
        visited[key] = 0;
        continue;
      }
      ll cnt = memoRecursiveGirl(y2, x2, memo, visited);
      memo[pair] = cnt;
      ret += cnt;
      visited[key] = 0;
    }
    return ret;
  }

  ll bitDPGirl() {
    // DP[bit][now]
    ll SIZE = (N + 1) * (N + 1);
    ll maxBit = 1LL << SIZE;

    vvl dp(maxBit, vl(SIZE));

    dp[1][0] = 1;
    rep(bit, maxBit) {
      // iから左右上下に配る
      rep(i, SIZE - 1) {
        if (dp[bit][i] == 0) continue;
        // 訪問済みにiが入っていないのは違反
        if (~bit >> i & 1) continue;
        rep(j, 4) {
          int y = i / (N + 1) + dy[j];
          int x = i % (N + 1) + dx[j];
          if (y < 0 || N < y || x < 0 || N < x) continue;
          int next = y * (N + 1) + x;
          // 訪問済みなら違反
          if (bit >> next & 1) continue;
          ll nextBit = bit | 1 << next;
          dp[nextBit][next] += dp[bit][i];
        }
      }
    }
    ll ret = 0;
    rep(i, maxBit) ret += dp[i][SIZE - 1];
    return ret;
  }

  void solve() {
    // printf("愚直再帰お姉さん\n");
    // rep(i, 5) {
    //   auto before = system_clock::now();
    //   N = i + 1;
    //   set<pair<int, int>> st;
    //   st.insert(make_pair(0, 0));
    //   ll res = recursiveGirl(0, 0, st);
    //   double t =
    //       ((double)duration_cast<microseconds>(system_clock::now() - before)
    //            .count() *
    //        1e-6);
    //   printf("格子%d×%dのとき：%lld通り %.5f\n", N, N, res, t);
    // }
    // printf("愚直再帰お姉さん改\n");
    // rep(i, 5) {
    //   auto before = system_clock::now();
    //   N = i + 1;
    //   unordered_set<int> st;
    //   st.insert(0);
    //   ll res = recursiveGirl2(0, 0, st);
    //   double t =
    //       ((double)duration_cast<microseconds>(system_clock::now() - before)
    //            .count() *
    //        1e-6);
    //   printf("格子%d×%dのとき：%lld通り %.5f\n", N, N, res, t);
    // }
    /*
    愚直再帰お姉さん
        格子1×1のとき：2通り 0.00010
        格子2×2のとき：12通り 0.00021
        格子3×3のとき：184通り 0.00307
        格子4×4のとき：8512通り 0.22606
        格子5×5のとき：1262816通り 49.11590
    愚直再帰お姉さん改
        格子1×1のとき：2通り 0.00011
        格子2×2のとき：12通り 0.00014
        格子3×3のとき：184通り 0.00205
        格子4×4のとき：8512通り 0.12861
        格子5×5のとき：1262816通り 24.34328
    */
    // printf("メモ化再帰お姉さん\n");
    // rep(i, 5) {
    //   auto before = system_clock::now();
    //   N = i + 1;
    //   map<pair<int, string>, ll> memo;
    //   bset visited;
    //   visited[0] = 1;
    //   ll res = memoRecursiveGirl(0, 0, memo, visited);
    //   double t =
    //       ((double)duration_cast<microseconds>(system_clock::now() - before)
    //            .count() *
    //        1e-6);
    //   printf("格子%d×%dのとき：%lld通り %.5f\n", N, N, res, t);
    // }
    printf("bitDPお姉さん\n");
    rep(i, 5) {
      auto before = system_clock::now();
      N = i + 1;
      ll res = bitDPGirl();
      double t =
          ((double)duration_cast<microseconds>(system_clock::now() - before)
               .count() *
           1e-6);
      printf("格子%d×%dのとき：%lld通り %.5f\n", N, N, res, t);
    }

    /* solve */

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