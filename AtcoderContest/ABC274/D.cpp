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
    int N, x, y;
    cin >> N >> x >> y;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    vector<set<pair<int, int>>> dp(N);
    dp[0].emplace(A[0], 0);
    rep(i, N - 1) {
      if (i % 2 == 0) {
        for (auto p : dp[i]) {
          dp[i + 1].emplace(p.first, p.second + A[i + 1]);
          dp[i + 1].emplace(p.first, p.second - A[i + 1]);
        }
      } else {
        for (auto p : dp[i]) {
          dp[i + 1].emplace(p.first + A[i + 1], p.second);
          dp[i + 1].emplace(p.first - A[i + 1], p.second);
        }
      }
    }
    // debug(dp);
    /* output */
    cout << (dp[N - 1].count(make_pair(x, y)) ? "Yes" : "No") << endl;
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