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
    int s, t, m;
    cin >> s >> t >> m;
    vvi G(s);
    rep(i, m) {
      int a, b;
      cin >> a >> b;
      --a;
      --b;
      b -= s;
      G[a].push_back(b);
    }

    /* solve */

    vvi id(t, vi(t, -1));
    rep(v, s) {
      int d = (int)G[v].size();
      sort(all(G[v]));
      rep(i, d) rep(j, i) {
        // a < bになっている
        int a = G[v][j], b = G[v][i];
        if (id[a][b] == -1) {
          id[a][b] = v;
        } else {
          int u = id[a][b];
          a += s + 1;
          b += s + 1;
          v++;
          u++;
          printf("%d %d %d %d\n", a, b, v, u);
          return;
        }
      }
    }
    cout << -1 << endl;

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