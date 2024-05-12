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
    
    int N, X, Y;
    cin >> N >> X >> Y;
    vvi G(N + 1);
    rep(i, N - 1) {
      int U, V;
      cin >> U >> V;
      G[U].push_back(V);
      G[V].push_back(U);
    }
    /* solve */
    deque<int> ans;
    

    auto dfs = [&](auto f, int p, int v) -> int {
      debug(p, v);
      if (v == Y) {
        ans.push_front(v);
        return 1;
      }

      for (auto u : G[v]) {
        if (u == p) continue;
        if (f(f, v, u)) {
          ans.push_front(v);
          return 1;
        }
      }
      return 0;
    };

    dfs(dfs, -1, X);

    /* output */
    rep(i, ans.size()) cout << ans[i] << "\n";
    cout << endl;
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