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
    // using bset = bitset<31>;
    // vector<vector<bset>> A(N, vector<bset>(N));
    vvl A(N, vl(N));
    rep(i, N) rep(j, N) {
      ll a;
      cin >> a;
      A[i][j] = a;
    }
    /* solve */
    vector<vector<unordered_map<ll, ll>>> dp(N,
                                             vector<unordered_map<ll, ll>>(N));
    dp[0][0][A[0][0]] = 1;
    rep(i, N) {
      rep(j, N / 2 + 2) {
        if (j >= N) break;
        for (auto p : dp[i][j]) {
          if (i + 1 < N) {
            dp[i + 1][j][p.first ^ A[i + 1][j]] += p.second;
          }
          if (j + 1 < N) {
            dp[i][j + 1][p.first ^ A[i][j + 1]] += p.second;
          }
        }
      }
    }
    vector<vector<unordered_map<ll, ll>>> dp2(N,
                                              vector<unordered_map<ll, ll>>(N));
    dp2[N - 1][N - 1][A[N - 1][N - 1]] = 1;

    for (int i = N - 1; i >= 0; i--) {
      for (int j = N - 1; j >= N / 2 + 1; j--) {
        for (auto p : dp2[i][j]) {
          if (i - 1 >= 0) {
            dp2[i - 1][j][p.first ^ A[i - 1][j]] += p.second;
          }
          if (j - 1 >= N / 2 + 1) {
            dp2[i][j - 1][p.first ^ A[i][j - 1]] += p.second;
          }
        }
      }
    }
    ll ans = 0;
    rep(i, N) {
      for (auto p : dp[i][N / 2 + 1]) {
        if (dp2[i][N / 2 + 1].count(p.first)) {
          debug(i, N / 2 + 1, p);
          ans += p.second * dp2[i][N / 2 + 1][p.first];
        }
      }
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