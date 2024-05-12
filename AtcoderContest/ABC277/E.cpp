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
    int N, M, K;
    cin >> N >> M >> K;
    vvvi G(N, vvi(2));
    rep(i, M) {
      int u, v, a;
      cin >> u >> v >> a;
      --u, --v;
      if (a == 1) {
        G[u][0].push_back(v);
        G[v][0].push_back(u);
      } else {
        G[u][1].push_back(v);
        G[v][1].push_back(u);
      }
    }
    vi S(K);
    rep(i, K) cin >> S[i];
    set<int> st;
    rep(i, K) st.insert(S[i] - 1);

    /* solve */
    vi dist(2 * N, INFTY);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int from = q.front();
      q.pop();
      int flag = 0;
      int now = dist[from];
      if (from >= N) {
        flag = 1;
        from -= N;
      }
      for (int to : G[from][flag]) {
        if (flag) to += N;
        if (chmin(dist[to], now + 1)) {
          q.push(to);
        }
      }
      if (st.count(from)) {
        flag = (flag + 1) % 2;
        int from2 = from;
        if (flag) from2 += N;
        chmin(dist[from2], now + 1);
        for (int to : G[from][flag]) {
          if (flag) to += N;
          if (chmin(dist[to], now + 1)) {
            q.push(to);
          }
        }
      }
    }
    // debug(dist);
    int ans = dist[N - 1];
    chmin(ans, dist[2 * N - 1]);
    if (ans == INFTY) ans = -1;
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