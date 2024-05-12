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
    int N, M;
    cin >> N >> M;

    vvi G(N);

    rep(i, M) {
      int A, B;
      cin >> A >> B;
      --A;
      --B;
      if (A > B) swap(A, B);
      G[A].push_back(B);
      G[B].push_back(A);
    }

    /* solve */
    if (M == 0) {
      cout << "Yes" << endl;
      return;
    }

    vi start;
    rep(i, N) {
      if (G[i].size() >= 3) {
        cout << "No" << endl;
        return;
      }
      if (G[i].size() == 1) start.push_back(i);
    }

    vi color(N);

    debug(G);
    debug(start);
    for (auto v : start) {
      if (color[v]) continue;

      color[v] = 1;

      int last = v;
      int next = G[v][0];
      while (true) {
        color[next] = 1;
        if (G[next].size() == 1) break;
        for (auto u : G[next]) {
          if (u == last) continue;
          if (color[u]) {
            cout << "No" << endl;
            return;
          }
          last = next;
          next = u;
          break;
        }
      }
    }
    debug(color);

    rep(i, N) {
      if (G[i].size() == 2 && !color[i]) {
        cout << "No" << endl;
        return;
      }
    }

    /* solve */

    /* output */
    cout << "Yes" << endl;
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