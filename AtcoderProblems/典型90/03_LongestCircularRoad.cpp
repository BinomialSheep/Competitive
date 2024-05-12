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

    /* solve */
    auto bfs = [&](int start) -> vi {
      vi dist(N, INFTY);
      dist[start] = 0;

      queue<int> q;
      q.push(start);
      while (!q.empty()) {
        auto from = q.front();
        q.pop();
        int d = dist[from] + 1;
        for (auto to : G[from]) {
          if (dist[to] <= d) continue;
          dist[to] = d;
          q.push(to);
        }
      }
      return dist;
    };

    vi dist1 = bfs(0);
    int d1Max = 0;
    int a = 0;
    rep(i, N) {
      if (chmax(d1Max, dist1[i])) a = i;
    }
    vi dist2 = bfs(a);
    int ans = 0;
    rep(i, N) chmax(ans, dist2[i]);

    /* output */
    cout << ans + 1 << endl;
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