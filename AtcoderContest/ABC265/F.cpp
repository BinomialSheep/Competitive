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

using mint = modint998244353;

struct Solver {
  int N, D;
  vi p, q;
  unordered_map<ll, mint> memo;

  mint rec(int n, int d1, int d2) {
    mint ret = 0;
    ll key = d1 * 10000000 + d2 * 1000 + n;
    if (memo.count(key)) return memo[key];

    for (int i = -d1; i <= d1; i++) {
      int x = p[n] + i;
      if (abs(q[n] - x) <= d2) {
        if (n == N - 1) {
          ret += 1;
        } else {
          ret += rec(n + 1, d1 - abs(i), d2 - abs(q[n] - x));
        }
      }
    }

    memo[key] = ret;
    return ret;
  }

  void solve() {
    /* input */
    cin >> N >> D;
    p.resize(N);
    q.resize(N);
    rep(i, N) cin >> p[i];
    rep(i, N) cin >> q[i];
    mint ans = rec(0, D, D);

    cout << ans.val() << endl;

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