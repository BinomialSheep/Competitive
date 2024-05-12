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
    int K;
    cin >> K;

    /* solve */

    vl ans;

    auto rec = [&](auto f, ll now, int nowD, int maxD) {
      if (nowD == maxD) {
        ans.push_back(now);
        return;
      }
      ll tmp = now % 10;
      now = now * 10 + tmp;
      if (tmp != 0) f(f, now - 1, nowD + 1, maxD);
      f(f, now, nowD + 1, maxD);
      if (tmp != 9) f(f, now + 1, nowD + 1, maxD);
    };

    rep(digit, 100) {
      rep(i, 9) {
        // 最上位桁をiとする
        rec(rec, i + 1, 1, digit + 1);
      }
      if ((int)ans.size() >= K) break;
    }

    /* output */
    cout << ans[K - 1] << endl;
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