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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      int N, K;
      cin >> N >> K;
      vi A(N);
      rep(i, N) cin >> A[i];
      vi B(2 * N);
      rep(i, N) cin >> B[i];
      rep(i, N) B[i + N] = B[i];

      /* solve */
      string ans = "YES";
      int start = -1;
      rep(i, N) {
        if (A[0] == B[i]) start = i;
      }

      rep(i, N) {
        int idx = start + i;
        if (A[i] != B[idx]) {
          ans = "NO";
          break;
        }
      }
      if (K == 0 && start != 0) ans = "NO";
      if (K == 1 && start == 0) ans = "NO";
      if (N == 2 && start ^ (K & 1)) ans = "NO";

      /* output */
      printf("Case #%d: %s\n", ti + 1, ans.c_str());
    }
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