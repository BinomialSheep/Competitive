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
    int N, M, E;
    cin >> N >> M >> E;
    vpii UV;
    rep(i, E) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      UV.emplace_back(u, v);
    }
    int Q;
    cin >> Q;
    vi X(Q);
    rep(i, Q) {
      cin >> X[i];
      X[i] = X[i] - 1;
    }

    /* solve */
    vi ans(Q);
    vi broken(E);
    rep(i, Q) broken[X[i]] = 1;

    dsu uf(N);
    vi lighted(N);
    int nowAns = 0;

    // 初期状態
    rep(i, E) {
      // 今は渡れない
      if (broken[i] == 1) continue;
      //
      int u = UV[i].first;
      int v = UV[i].second;

      // 両方都市
      if (v < N) {
        if (lighted[u] && lighted[v]) {
          // 増えない
          uf.merge(u, v);
          lighted[uf.leader(v)] = true;
        } else if (lighted[u]) {
          nowAns += uf.size(v);
          uf.merge(u, v);
          lighted[uf.leader(v)] = true;
        } else if (lighted[v]) {
          nowAns += uf.size(u);
          uf.merge(u, v);
          lighted[uf.leader(u)] = true;
        } else {
          uf.merge(u, v);
        }
      } else if (N <= u) {
        // 両方発電所なら何も起こらない
      } else {
        // uだけ都市
        if (!lighted[uf.leader(u)]) {
          nowAns += uf.size(u);
        }
        lighted[uf.leader(u)] = true;
      }
    }

    rep(i, Q) {
      ans[Q - i - 1] = nowAns;
      int u = UV[X[Q - 1 - i]].first;
      int v = UV[X[Q - 1 - i]].second;

      // 両方都市
      if (v < N) {
        if (lighted[u] && lighted[v]) {
          // 増えない
          uf.merge(u, v);
          lighted[uf.leader(v)] = true;
        } else if (lighted[u]) {
          nowAns += uf.size(v);
          uf.merge(u, v);
          lighted[uf.leader(v)] = true;
        } else if (lighted[v]) {
          nowAns += uf.size(u);
          uf.merge(u, v);
          lighted[uf.leader(u)] = true;
        } else {
          uf.merge(u, v);
        }
      } else if (N <= u) {
        // 両方発電所なら何も起こらない
      } else {
        // uだけ都市
        if (!lighted[uf.leader(u)]) {
          nowAns += uf.size(u);
        }
        lighted[uf.leader(u)] = true;
      }
    }

    /* output */
    rep(i, Q) cout << ans[i] << "\n";
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