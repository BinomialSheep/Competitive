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
    vector<vpii> T(N);
    rep(i, N - 1) {
      int a, b, c;
      cin >> a >> b >> c;
      --a;
      --b;
      T[a].emplace_back(b, c);
      T[b].emplace_back(a, c);
    }

    int Q, K;
    cin >> Q >> K;
    --K;
    vi X(Q), Y(Q);
    rep(i, Q) {
      cin >> X[i] >> Y[i];
      --X[i];
      --Y[i];
    }

    /* solve */
    vl dist(N, -1);
    queue<int> q;

    dist[K] = 0;
    q.push(K);

    while (!q.empty()) {
      auto v = q.front();
      q.pop();

      for (auto p : T[v]) {
        if (dist[p.first] != -1) continue;
        q.push(p.first);
        dist[p.first] = dist[v] + p.second;
      }
    }
    debug(dist);

    rep(qi, Q) { cout << dist[X[qi]] + dist[Y[qi]] << endl; }

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