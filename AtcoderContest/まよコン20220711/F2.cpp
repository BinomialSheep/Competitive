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

const int D = 80 * 160 + 10;
const int D2 = D * 2;
typedef bitset<D2> bs;
int a[100][100];
bs dp[90][90];

struct Solver {
  void solve() {
    /* input */
    int h, w;
    cin >> h >> w;
    rep(i, h) rep(j, w) {
      int x;
      cin >> x;
      a[i][j] = x;
    }
    rep(i, h) rep(j, w) {
      int x;
      cin >> x;
      a[i][j] = abs(x - a[i][j]);
    }

    /* solve */

    dp[0][0][D - a[0][0]] = 1;
    dp[0][0][D + a[0][0]] = 1;
    rep(i, h) rep(j, w) {
      if (i) {
        // dp[i-1][j]の地点でできる数字の集合すべてにa[i][j]を足す（引く）のはシフトで表現できる
        // 別方向からきた場合や、a[i][j]を足した場合と引いた場合の両方でできるかもなので、|=
        dp[i][j] |= dp[i - 1][j] << a[i][j];
        dp[i][j] |= dp[i - 1][j] >> a[i][j];
      }
      if (j) {
        dp[i][j] |= dp[i][j - 1] << a[i][j];
        dp[i][j] |= dp[i][j - 1] >> a[i][j];
      }
    }
    int ans = D2;
    // マイナスに下駄を履かせていたので、i - Dで元の数に戻してる
    rep(i, D2) if (dp[h - 1][w - 1][i]) chmin(ans, abs(i - D));

    /* output */
    cout << ans << endl;
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