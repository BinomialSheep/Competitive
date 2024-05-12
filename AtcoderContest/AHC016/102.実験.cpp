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

int M;
double eps;
int N;
vs Ss(100);

struct Solver {
  void solve() {
    /* input */

    /* solve */
    int sz = N * (N - 1) / 2;
    if (sz / (M - 1) == 0) return;
    // cout << N << endl;

    vi sizeList;
    for (int i = 0; i <= sz; i += sz / (M - 1)) {
      sizeList.push_back(i);
    }
    while ((int)sizeList.size() < M) sizeList.push_back(0);
    while ((int)sizeList.size() > M) sizeList.pop_back();
    assert((int)sizeList.size() == M);
    debug(sizeList);

    vs G(M);
    rep(i, M) {
      int v = sizeList[i];
      rep(j, v) G[i].push_back('1');
      rep(j, sz - v) G[i].push_back('0');
      assert((int)G[i].size() == sz);
      // cout << G[i] << "\n";
      //  debug(str.size());
    }
    // cout << flush;
    /* interactive */
    int correct = 0;
    rep(qi, 100) {
      string S = Ss[qi];
      // cin >> S;
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
      int ans = -1;
      int diff = INFTY;
      rep(i, sizeList.size()) {
        if (chmin(diff, abs(sizeList[i] - cnt))) ans = i;
      }
      // debug(cnt, ans);

      // cout << ans << endl;
      if (ans == stoi(S)) correct++;
    }
    double score = 1e9;
    rep(i, correct) score *= 0.9;
    score /= N;
    /* output */
    printf("%d %d %d\n", N, correct, (int)score);
  }
};

int main() {
  cin >> M >> eps;
  int ts = 97;
  rep(i, 100) cin >> Ss[i];
  rep(ti, ts) {
    N = ti + 4;
    Solver solver;
    solver.solve();
  }
  return 0;
}