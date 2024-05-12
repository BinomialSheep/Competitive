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
  ll prim(int V, int r, vector<vector<pii>> &G) {
    ll ret = 0;

    // 訪問済み頂点
    set<int> visited;
    // 現在の頂点集合から伸びてる辺を優先度付きキューで管理する
    priority_queue<pii, vector<pii>, greater<pii>> q;
    // 始点
    visited.insert(r);
    for (auto p : G[r]) {
      int u = p.first;
      int w = p.second;
      q.emplace(w, u);
    }

    while (!q.empty()) {
      auto edge = q.top();
      q.pop();
      int w = edge.first;
      int u = edge.second;
      // 未訪問頂点に向かう辺なら加える
      if (visited.count(u) == 0) {
        visited.insert(u);
        ret += w;
        if ((int)visited.size() == V) return ret;

        // uから伸びる辺をキューに加える
        for (auto p : G[u]) {
          if (!visited.count(p.first)) {
            q.emplace(p.second, p.first);
          }
        }
        // cout << u << " " << w << endl;
      }
    }

    return ret;
  }

  void solve() {
    /* input */
    int V, E;
    cin >> V >> E;

    vector<vector<pii>> G(V);

    rep(i, E) {
      int s, t, w;
      cin >> s >> t >> w;
      G[s].emplace_back(t, w);
      G[t].emplace_back(s, w);
    }

    /* solve */
    ll ans = prim(V, 0, G);

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