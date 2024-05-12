#include <bits/stdc++.h>
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
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

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
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vector<pii>> G(N);
    rep(i, M) {
      int a, b, c;
      cin >> a >> b >> c;
      --a;
      --b;
      G[a].emplace_back(b, c);
      G[b].emplace_back(a, c);
    }

    rep(qi, Q) {
      int u, v, w;
      cin >> u >> v >> w;
      --u;
      --v;

      int wid = w;
      for (auto e : G[u]) chmin(wid, e.second);
      // for (auto e : G[u])
      //   cout << u << " " << e.first << " " << e.second << endl;
      if (wid == w) {
        cout << "Yes" << endl;
        continue;
      }
      wid = w;
      for (auto e : G[v]) chmin(wid, e.second);

      // for (auto e : G[v])
      //   cout << v << " " << e.first << " " << e.second << endl;

      cout << (w == wid ? "Yes" : "No") << endl;
    }

    /* solve */

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