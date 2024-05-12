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
#define EPS (1e-6)
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
    ll sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    vl x(N), y(N), r(N);
    rep(i, N) cin >> x[i] >> y[i] >> r[i];

    /* solve */
    vvi G(N);

    rep(i, N - 1) for (int j = i + 1; j < N; j++) {
      // 円と円の交差判定
      // 中心間距離
      double d =
          sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      // 外接
      if (equal(d, (double)(r[i] + r[j]))) {
        G[i].push_back(j);
        G[j].push_back(i);
        continue;
      }
      // 内接
      if (equal(d, (double)(abs(r[i] - r[j])))) {
        G[i].push_back(j);
        G[j].push_back(i);
        continue;
      }
      // 内部にある
      if (d < (double)(abs(r[i] - r[j]))) continue;
      // 外部にある
      if (d > (double)(r[i] + r[j])) continue;
      // 2点で交差
      G[i].push_back(j);
      G[j].push_back(i);
      continue;
    }

    // 始点と終点を見つける
    int start = -1, end = -1;
    rep(i, N) {
      ll ds = (x[i] - sx) * (x[i] - sx) + (y[i] - sy) * (y[i] - sy);
      ll dt = (x[i] - tx) * (x[i] - tx) + (y[i] - ty) * (y[i] - ty);
      if (r[i] * r[i] == ds) start = i;
      if (r[i] * r[i] == dt) end = i;
    }
    // debug(G);
    // debug(start, end);

    //

    vi color(N);
    queue<int> q;
    q.push(start);
    color[start] = 1;

    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      for (auto u : G[v]) {
        if (color[u]) continue;
        color[u] = 1;
        q.push(u);
      }
    }

    /* output */
    if (color[end]) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
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