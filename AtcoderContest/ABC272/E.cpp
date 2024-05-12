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
    int N, M;
    cin >> N >> M;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    vector<unordered_set<int>> B(N);

    rep(i, N) {
      int init = A[i];
      int start = 0;
      if (init < 0) {
        int tmp = -init / (i + 1);
        if (tmp > M) continue;
        if (tmp >= 2) {
          start = tmp - 1;
          init += (i + 1) * start;
        }
      }
      if (start >= M) continue;
      for (int j = start; j < M; j++) {
        init += i + 1;
        // debug(i, init);
        if (init < 0) continue;
        if (init >= N) break;
        B[init].insert(j + 1);
      }
    }
    // debug(B);

    unordered_set<int> unused;
    rep(i, M) unused.insert(i + 1);
    vi ans(M);
    // debug(unused);

    rep(i, N) {
      vi used;
      for (auto v : unused) {
        if (B[i].count(v) == 0) {
          // debug(i, v);
          used.push_back(v);
          // if (v - 1 >= 0 && v - 1 < M) {
          ans[v - 1] = i;
          //}
        }
      }
      // unusedから消す
      for (auto v : used) {
        unused.erase(v);
      }
      if (unused.empty()) break;
    }
    if (unused.size()) {
      for (auto v : unused) {
        ans[v - 1] = N;
      }
    }
    /* output */
    rep(i, M) cout << ans[i] << "\n";
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