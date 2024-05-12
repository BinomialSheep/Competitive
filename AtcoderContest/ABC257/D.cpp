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
  bool isOk(ll power, vvl &G, int N, vl &P) {
    rep(start, N) {
      vi color(N);
      queue<int> q;
      q.push(start);
      color[start] = 1;

      while (!q.empty()) {
        int v = q.front();
        q.pop();
        rep(i, N) {
          if (color[i]) continue;
          if ((ll)P[v] * power >= G[v][i]) {
            color[i] = 1;
            q.push(i);
          }
        }
      }

      int flag = 0;
      rep(i, N) {
        if (color[i] == 0) {
          flag = 1;
          break;
        }
      }
      if (flag) continue;
      debug(power, start);
      return true;
    }
    return false;
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    vl x(N), y(N), P(N);
    rep(i, N) cin >> x[i] >> y[i] >> P[i];

    /* solve */
    vvl G(N, vl(N));

    rep(i, N) {
      rep(j, N) {
        if (i == j) continue;
        G[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
        G[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
      }
    }
    debug(G);

    ll ng = -1;
    ll ok = 4 * 1e9 + 10;

    while (ok - ng > 1) {
      ll mid = (ok + ng) / 2;

      if (isOk(mid, G, N, P)) {
        ok = mid;
      } else {
        ng = mid;
      }
    }

    cout << ok << endl;

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