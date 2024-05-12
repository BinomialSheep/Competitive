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
  vi L, R, P, I;
  int N;
  bool fail;

  void dfs(int v, int left, int right, int v2, int left2, int rigth2) {
    if (fail) return;

    // P[v+1]が左の親になる

    // IからP[v]と等しいidx探す
    int idx = -1;
    // for (int i = v; i < N; i++) {
    for (int i = 0; i < N; i++) {
      if (I[i] == P[v]) {
        idx = i;
        break;
      }
    }
    // 見つからなければ構築不可能
    if (idx == -1) {
      debug("idx failed");
      fail = true;
      return;
    }

    // P[]  [idx-1]までは左
    int idx2 = -1;
    if (idx == left2) {
      idx2 = -2;
    } else {
      for (int i = v; i < right; i++) {
        if (P[i] == I[idx - 1]) {
          idx2 = i;
          break;
        }
      }
      if (idx2 == -1) {
        debug("idx2 failed");
        fail = true;
        return;
      }
    }
    debug(v, idx, idx2);

    // 左側は、P[v+1]が親
    if (v + 1 < idx) {
      // dfs(v + 1, v + 1, idx2 + 1);
      L[v] = P[v + 1];
    } else {
      L[v] = -1;
    }
    // 右側は、P[idx2+1]が親
    if (idx < idx2 + 1 && idx2 + 1 < right && idx2 != -2) {
      // dfs(idx2 + 1, idx2 + 1, right);
      R[v] = P[idx2 + 1];
    } else if (idx < v + 1) {
      L[v] = P[v + 1];
    } else {
      R[v] = -1;
    }
    if (v + 1 < right) {
      dfs(v + 1, v + 1, idx2 + 1, idx, left, idx2 - 1);
    }
    if (idx2 + 1 < right && idx2 != -2) {
      dfs(idx2 + 1, idx2 + 1, right, idx, idx2 + 1, right);
    }
  }

  void solve() {
    /* input */
    cin >> N;
    L.resize(N);
    R.resize(N);
    P.resize(N);
    I.resize(N);
    fail = false;

    rep(i, N) cin >> P[i], --P[i];
    rep(i, N) cin >> I[i], --I[i];

    /* solve */
    if (P[0] != 0) {
      cout << -1 << endl;
      return;
    }

    dfs(0, 0, N, -1, 0, N);
    debug(L, R);

    if (fail) {
      cout << -1 << endl;
      return;
    }
    rep(i, N) { printf("%d %d\n", L[i] + 1, R[i] + 1); }

    /* output */
  }
};

int main() {
  int ts = 2;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}