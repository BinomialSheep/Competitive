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
    int N, S;
    cin >> N >> S;
    vi A(N), B(N);
    rep(i, N) cin >> A[i] >> B[i];

    /* solve */
    vvi dp(N + 1, vi(S + 1));

    dp[0][0] = 1;
    rep(i, N) {
      rep(j, S) {
        if (dp[i][j]) {
          if (j + A[i] <= S) dp[i + 1][j + A[i]] = 1;
          if (j + B[i] <= S) dp[i + 1][j + B[i]] = 1;
        }
      }
    }
    if (dp[N][S] == 1) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
      return;
    }
    // 復元
    int now = S;
    string ans = "";
    for (int i = N - 1; i >= 0; i--) {
      if (now - A[i] >= 0 && dp[i][now - A[i]] == 1) {
        now -= A[i];
        ans.push_back('H');
      } else if (now - B[i] >= 0 && dp[i][now - B[i]] == 1) {
        now -= B[i];
        ans.push_back('T');
      } else {
        assert(false);
      }
    }
    reverse(all(ans));
    cout << ans << endl;

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