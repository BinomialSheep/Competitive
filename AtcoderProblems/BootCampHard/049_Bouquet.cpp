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

// nや
// modint
using mint = modint1000000007;
mint nCkMod(mint n, mint k) {
  int ni = n.val();
  int ki = k.val();
  mint ret = 1;
  for (int i = ni; i >= ni - ki + 1; i--) ret *= i;
  for (int i = 1; i <= ki; i++) ret /= i;
  return ret;
}

struct Solver {
  void solve() {
    /* input */
    int n, a, b;
    cin >> n >> a >> b;
    int MOD = 1e9 + 7;

    /* solve */

    mint ans = 0;

    if (n > 2) {
      ans = myPower(2, n, MOD);
      ans -= nCkMod(n, a);
      ans -= nCkMod(n, b);
      --ans;  // 0種類選ぶ分
    }
    /* output */
    cout << ans.val() << endl;
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