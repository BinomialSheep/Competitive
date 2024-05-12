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

    vector<vector<pii>> G(N);
    rep(i, N - 1) {
      int u, v, w;
      cin >> u >> v >> w;
      --u, --v;
      G[u].emplace_back(v, w);
      G[v].emplace_back(u, w);
    }

    /* solve */
    vl dist(N);
    rep(i, N) dist[i] = 1e18;
    using pli = pair<ll, int>;
    priority_queue<pli, vector<pli>, greater<pli>> q;
    q.emplace(0, 0);
    dist[0] = 0;
    while (!q.empty()) {
      auto p = q.top();
      q.pop();
      if (dist[p.second] != p.first) continue;
      for (auto up : G[p.second]) {
        int u = up.first;
        int w = up.second;
        if (chmin(dist[u], dist[p.second] + w)) {
          q.emplace(dist[u], u);
        }
      }
    }
    debug(dist);

    /* output */
    rep(i, N) {
      if (dist[i] % 2) {
        cout << "1\n";
      } else {
        cout << "0\n";
      }
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