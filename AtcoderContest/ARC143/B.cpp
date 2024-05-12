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

// 二項係数（前処理O(n), クエリ毎O(1))
// facなどのコピペも忘れすに
const int nCkMAX = 260000;
ll fac[nCkMAX], finv[nCkMAX], inv[nCkMAX];
class MynCkMod {
  const int MOD;

 public:
  MynCkMod(int mod) : MOD(mod) { COMinit(); };

  // 前処理
  void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < nCkMAX; i++) {
      fac[i] = fac[i - 1] * i % MOD;
      inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
      finv[i] = finv[i - 1] * inv[i] % MOD;
    }
  }

  // 二項係数計算
  ll COM(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
  }
};

struct Solver {
  void solve() {
    /* input */
    ll MOD = 998244353;
    int N;
    cin >> N;

    /* solve */
    MynCkMod nCk((int)MOD);
    // 列max ∧ 行minがあるとダメ
    // それが1行目か1列目にあるとしても一般性は失われない
    ll ans = fac[N * N];
    // debug(ans);
    rep(i, N * N) {
      // 行minにする組み合わせ
      // i+1より大きいものからN-1個選ぶ
      int n1 = N * N - (i + 1);
      ll c1 = nCk.COM(n1, N - 1);
      // 列maxにする組み合わせ
      // i + 1 より小さい者からN-1個選ぶ
      int n2 = i;
      ll c2 = nCk.COM(n2, N - 1);
      ll cnt = c1 * c2 % MOD;
      // iがある行と列がどうなっているか
      // cnt = cnt * (fac[N] + fac[N] - 1) % MOD;
      cnt = cnt * fac[N] % MOD;
      cnt = cnt * fac[N] % MOD;
      // それ以外がどうなっているか
      cnt = cnt * fac[(N - 1) * (N - 1)] % MOD;
      ans = (ans + MOD - cnt) % MOD;
      // debug(i + 1, c1, c2, cnt, ans);
    }

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