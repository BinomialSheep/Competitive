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
  void floyd(int V, vvi &G) {
    rep(i, V) G[i][i] = 0;

    rep(k, V) rep(i, V) {
      if (G[i][k] == INFTY) continue;
      rep(j, V) {
        if (G[k][j] == INFTY) continue;
        chmin(G[i][j], G[i][k] + G[k][j]);
      }
    }
  }

  void solve() {
    /* input */
    int H, W;
    cin >> H >> W;

    vvi cost(10, vi(10, INFTY));
    rep(i, 10) rep(j, 10) cin >> cost[i][j];

    vvi A(H, vi(W));
    rep(i, H) rep(j, W) cin >> A[i][j];

    /* solve */
    // cost[from][to] := fromからtoに変換する時の最小コスト
    // ワーフロる
    floyd(10, cost);
    //
    ll ans = 0;
    rep(i, H) rep(j, W) {
      if (A[i][j] != -1) ans += cost[A[i][j]][1];
    }

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