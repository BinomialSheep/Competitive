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
    ll B, C;
    cin >> B >> C;

    /* solve */
    // 0以上B以下の数：ずっとマイナスする
    // -B以上0未満の数：ずっとマイナスしてどこかで-1掛ける
    // -B以下の数：最初に-1掛けてずっとマイナスする
    // B以上の数：最初に-1掛けてずっとマイナスして最後にプラスする
    auto llMin = [](ll a, ll b) { return (a < b) ? a : b; };
    auto llMax = [](ll a, ll b) { return (a < b) ? b : a; };
    ll ans = 0;
    if (B > 0) {
      // 0以上B以下の数
      ll to = B - C / 2;
      ans += B + 1 - llMax(to, 0);
      debug(ans);
      // -Bより大きく0未満の数
      to = B - (C - 1) / 2;
      ans += B - llMax(to, 1);
      // -B
      ans++;
      debug(ans);
      // -B未満の数
      ans += (C - 1) / 2;
      debug(ans);
      // B以上の数
      if (C >= 2) ans += (C - 2) / 2;
      debug(ans);
    } else {
      // B以下の数
      ans += 1 + C / 2;
      // -B以上の数
      // 最後に-1倍する
      ans += (C + 1) / 2;
      // -B未満でBより大きい数
      // 最初に-1倍してBまで下げていく
      ll to = -B - (C - 1) / 2;
      ans += llMin(-B - to, -B - B - 1);
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