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
    vvi G(N);
    rep(i, N - 1) {
      int A, B;
      cin >> A >> B;
      --A, --B;
      G[A].push_back(B);
      G[B].push_back(A);
    }

    int C = -1;
    queue<int> q;
    q.push(0);
    vi visited(N);
    visited[0] = 1;
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      visited[v] = 1;
      for (auto u : G[v]) {
        if (visited[u]) continue;
        q.push(u);
      }
      if (q.empty()) C = v;
    }
    int D = -1;
    q.push(C);
    vi dist(N, -1);
    dist[C] = 0;
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      for (auto u : G[v]) {
        if (dist[u] != -1) continue;
        dist[u] = dist[v] + 1;
        q.push(u);
      }
      if (q.empty()) D = v;
    }
    debug(dist);

    vi distC(dist[D] + 1);
    distC[dist[D]] = D;
    int now = D;
    for (int d = dist[D] - 1; d >= 0; d--) {
      for (auto u : G[now]) {
        if (dist[u] == d) {
          now = u;
          distC[d] = u;
        }
      }
    }
    debug(distC);

    set<int> st;
    for (auto v : distC) st.insert(v);

    /* solve */

    int Q;
    cin >> Q;
    rep(qi, Q) {
      int U, K;
      cin >> U >> K;
      --U;

      queue<int> q;
      int tmp = dist[U];
      q.push(U);
      while (true) {
        auto v = q.front();
        q.pop();

        if (st.count(v)) {
          K -= dist[U] - dist[v];
          U = v;
          break;
        }
        for (auto u : G[v]) {
          if (dist[u] == tmp - 1) {
            q.push(u);
            tmp--;
          }
        }
      }

      if (dist[U] - K >= 0) {
        cout << distC[dist[U] - K] + 1 << "\n";
      } else if (dist[U] + K <= dist[D]) {
        cout << distC[dist[U] + K] + 1 << "\n";
      } else {
        cout << -1 << "\n";
      }
    }

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