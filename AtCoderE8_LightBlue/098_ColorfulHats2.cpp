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

struct Solver {
  void solve() {
    /* input */
    int N;
    cin >> N;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    using mint = modint1000000007;
    vector<map<tuple<int, int, int>, mint>> dp(N);
    if (A[0] != 0) {
      cout << 0 << endl;
      return;
    }
    dp[0][tuple(0, 0, 1)] = 1;
    dp[0][tuple(0, 1, 0)] = 1;
    dp[0][tuple(1, 0, 0)] = 1;

    rep(i, N - 1) {
      for (auto p : dp[i]) {
        int r, b, g;
        tie(r, b, g) = p.first;
        // i+1人目がr
        if (r == A[i + 1]) dp[i + 1][tuple(r + 1, b, g)] += p.second;
        // i+1人目がb
        if (b == A[i + 1]) dp[i + 1][tuple(r, b + 1, g)] += p.second;
        // i+1人目がg
        if (g == A[i + 1]) dp[i + 1][tuple(r, b, g + 1)] += p.second;
      }
    }

    mint ans = 0;
    for (auto p : dp[N - 1]) ans += p.second;

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