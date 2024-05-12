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
#include <atcoder/all>
using namespace atcoder;
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

using mint = modint1000000007;

struct Solver {
  int N;
  vvi G;
  mint ans;

  int dfs(int v, int p = -1) {
    int ret = 1;
    vi ts;
    // 子方向の部分木のサイズを足す
    for (auto u : G[v]) {
      // 親方向にはdfsしない
      if (u == p) continue;
      int t = dfs(u, v);
      ret += t;
      ts.push_back(t);
    }
    // 親方向の部分木のサイズは、全頂点 - （子方向部分木）
    if (p != -1) {
      ts.push_back(N - ret);
    }
    //
    // 自分を白に塗る全事象2^-1から引いていく
    mint now = mint(2).pow(N - 1);
    // 全頂点を白に塗る
    now -= 1;
    for (auto t : ts) {
      // 1つの部分木のみ黒、それ以外は白
      // 前者は2^t-1(全白以外)、後者は1（全白）
      now -= mint(2).pow(t) - 1;
    }
    ans += now;

    return ret;
  }

  void solve() {
    /* input */
    cin >> N;
    G.resize(N);
    rep(i, N - 1) {
      int A, B;
      cin >> A >> B;
      --A;
      --B;
      G[A].push_back(B);
      G[B].push_back(A);
    }

    ans = 0;

    /* solve */
    dfs(0);
    // ansは場合の数なので、全事象2^Nで割る
    ans /= mint(2).pow(N);
    cout << ans.val() << endl;

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