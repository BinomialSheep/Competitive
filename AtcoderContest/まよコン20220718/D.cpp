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
    vvi G(N);
    rep(i, M) {
      int x, y;
      cin >> x >> y;
      --x;
      --y;
      G[x].push_back(y);
    }
    /* solve */

    // そこまでで買える値段のミニマム
    int INFTY2 = 2e9;
    vi minBuy(N, INFTY2);

    rep(i, N) {
      queue<int> q;
      q.push(i);
      while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto u : G[v]) {
          if (chmin(minBuy[u], min(minBuy[v], A[v]))) {
            q.push(u);
          }
        }
      }
    }

    int ans = -INFTY2;
    rep(i, N) chmax(ans, A[i] - minBuy[i]);
    // debug(minBuy);

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