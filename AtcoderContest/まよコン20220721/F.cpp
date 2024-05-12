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

int memo[42][409][409];

struct Solver {
  int N, Ma, Mb;
  vi a, b, c;

  int dfs(int aa, int bb, int idx) {
    if (idx == N) {
      if (aa * Mb == bb * Ma && aa != 0) {
        return 0;
      } else {
        return INFTY;
      }
    }

    int ret = INFTY;

    if (memo[idx][aa][bb] != INFTY) return memo[idx][aa][bb];

    // 買う場合
    int aaa = aa + a[idx];
    int bbb = bb + b[idx];

    int tmp = dfs(aaa, bbb, idx + 1);
    chmin(ret, tmp + c[idx]);
    memo[idx + 1][aaa][bbb] = tmp + c[idx];
    // 買わない場合

    tmp = dfs(aa, bb, idx + 1);
    chmin(ret, tmp);
    memo[idx + 1][aa][bb] = tmp;

    return ret;
  }

  void solve() {
    /* input */

    cin >> N >> Ma >> Mb;
    a.resize(N);
    b.resize(N);
    c.resize(N);

    rep(i, N) cin >> a[i] >> b[i] >> c[i];

    /* solve */
    rep(i, 42) rep(j, 409) rep(k, 409) memo[i][j][k] = INFTY;
    int ans = dfs(0, 0, 0);

    /* output */
    if (ans >= INFTY) ans = -1;
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