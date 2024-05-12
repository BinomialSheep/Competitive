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
    int N, K;
    cin >> N >> K;
    vi x(N);
    rep(i, N) { cin >> x[i]; }

    /* solve */
    vl plus;
    vl minus;

    // 分解
    bool flag = false;
    rep(i, N) {
      if (x[i] < 0) {
        minus.push_back(-x[i]);
      } else if (x[i] > 0) {
        plus.push_back(x[i]);
      } else {
        flag = true;
      }
    }
    reverse(all(minus));
    if (flag) --K;

    if (K == 0) {
      cout << 0 << endl;
      return;
    }

    ll ans = 1e18;
    // プラスを0個取る～プラスをK個取るでずらす
    rep(i, K + 1) {
      // プラスをi個取れないならダメ
      if ((int)plus.size() < i) continue;
      // マイナスをK-i個取れないならダメ
      if ((int)minus.size() < K - i) continue;

      if (i == 0) {
        chmin(ans, minus[K - 1]);
        continue;
      }
      if (i == K) {
        chmin(ans, plus[K - 1]);
        continue;
      }

      // 短い方を往復が発生する
      auto f = [](ll a, ll b) {
        if (a >= b) return b;
        return a;
      };
      ll now =
          plus[i - 1] + minus[K - i - 1] + f(plus[i - 1], minus[K - i - 1]);
      debug(i, plus[i - 1], minus[K - i - 1], now);

      chmin(ans, now);
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