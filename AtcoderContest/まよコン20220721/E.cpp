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
    ll tmp;
    cin >> tmp;
    using bs = bitset<41>;
    bs K = tmp;
    vector<bs> A(N);
    rep(i, N) {
      cin >> tmp;
      A[i] = tmp;
    }

    /* solve */
    debug(K);
    debug(A);

    bs x = 0;
    int flag = 1;
    for (int i = 40; i >= 0; i--) {
      // 最大値を超える値は設定できない
      if (flag && !K[i]) continue;

      int cnt = 0;
      rep(j, N) {
        if (A[j][i]) cnt++;
      }
      // debug(i, cnt);
      if (cnt >= N - cnt) {
        // 1の方が多いので、0を設定した方がいい
        // 0を設定したらフラグが0になる
        flag = 0;
        x[i] = 0;
      } else {
        x[i] = 1;
      }
    }
    debug(x);

    ll ans = 0;
    rep(i, N) { ans += (A[i] ^ x).to_ullong(); }

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