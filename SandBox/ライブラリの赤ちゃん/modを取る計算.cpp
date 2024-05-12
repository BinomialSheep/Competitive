#include <bits/stdc++.h>
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
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

// 繰り返し自乗法 O(log n)
/* pow(x, n)
   = 1 (n == 0)
   = power(xx, n/2) (nが偶数）
   = power(xx, n/2) * x (nが奇数）
   以下は、power(xx, n/2) == 2 * power(x, n/2) を利用
*/
using ull = unsigned long long;
ull myPower(ull x, ull n, ull MOD) {
  ull res = 1;
  if (n > 0) {
    res = myPower(x, n / 2, MOD);
    res = (res * res) % MOD;
    if (n % 2 == 1) res = (res * x) % MOD;
  }
  return res;
}
// ※ あらかじめ累乗を計算しておけば前処理O(N), クエリ毎O(1)になる
// TODO

// 二項係数
// https://algo-logic.info/combination/#toc_id_1

// 二項係数（前処理O(n), クエリ毎O(1))
// facなどのコピペも忘れすに
const int nCkMAX = 510000;
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

// nは巨大だけどO(k)でいい時
using mint = modint1000000007;
mint nCkMod(mint n, mint k) {
  int ni = n.val();
  int ki = k.val();
  mint ret = 1;
  for (int i = ni; i >= ni - ki + 1; i--) ret *= i;
  for (int i = 1; i <= ki; i++) ret /= i;
  return ret;
}

// nもkも小さい時はDPする
vvl dp(51, vl(51));
rep(i, 51) dp[i][0] = 1;
for (int i = 1; i < 51; i++) {
  for (int j = 1; j < 51; j++) {
    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
  }
}
// 200C11とかもいける
// int N = 201, M = 12;
// vvl dp(N, vl(M));
// rep(i, N) dp[i][0] = 1;
// for (int i = 1; i < N; i++) {
//   for (int j = 1; j < M; j++) {
//     dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
//   }
// }

struct Solver {
  void solve() {
    /* input */
    // MynCkMod nCkMod(1000000007);
    // MynCkMod nCkMod(998244353);
    // cout << nCkMod.COM(5, 2) << endl;
    // cout << nCkMod.COM(200, 100) << endl;
    // cout << nCkMod.COM(100000, 50000) << endl;

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